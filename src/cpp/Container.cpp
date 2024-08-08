

#include "imgui/imgui.h"


#define WIDTH 0
#define HEIGHT 1

#define coregui_impl
#include "../h/coreGui.h"

#define ecl 1
#include "ecl.h"

using namespace visuals;
// containerClass
using mclass = winContainer;


template < typename style_Type >
gmHandle static winos::createWindow(astr Name, astr className, float width, float height, style_Type style, bool isHidden, createWin_osd aptr_ extra) {
   bool extended = extra != nullset;


   WNDCLASS wc = {0};
   wc.lpfnWndProc = proc::os_callbacks;
   wc.hInstance = GetModuleHandle(NULL);
   wc.lpszClassName = className.pwide_str();

   if (extended) {
   }
   RegisterClass(&wc);
   os::cd_lastError();
   HWND hwnd = CreateWindowExW(0, className.pwide_str(), Name.pwide_str(), style, 0, 0, width, height, NULL, NULL, 0, NULL);

   if (!isHidden)
      ShowWindow(hwnd, SW_SHOWNORMAL);

   return hwnd;
}


namespace win {
   decs::Motion CalcRelative_MiddlePosition (decs::Body body);

   decs::Motion CalcAlign_byMassCenter (decs::Motion Position, const decs::Body ref_ body);

   gmVoid PrepContainerMotions (decs::FusionObject ref_ fusion);

   gmHandle Establish_Container_Platforms (decs::FusionObject ref_ fusion, ulong style);

   HGLRC
   init_pixelFormat_once(HDC hdc);

   namespace utils {
      // get native resolution
      decs::Motion getNativeRes () {
         return {(float)GetSystemMetrics(WIDTH), (float)GetSystemMetrics(HEIGHT)};
      }
      // ask os to change our window position
      bool setContainerPos (mclass *container, int opt_x1 = 0, int opt_y1 = 0);

   }   // namespace utils


}   // namespace win

using namespace Fusion::decs;

bool isCursorInsideWindow (decs::FusionObject &obj) {
   decs::Motion cursorMotion = obj.m_GetCursorOS();
   decs::Body windowBody = obj.m_GetBodyMass();
   decs::Motion position = obj.m_GetMotion();

   return (cursorMotion.x > position.x && cursorMotion.x < (position.x + windowBody.width) && cursorMotion.y > position.y && cursorMotion.y < (position.y + windowBody.height));
}

bool isImguiCursorInsideTabBarWindow (visuals::Canvas &obj, int tabMaxY = 20) {
   ImVec2 imguiCursorPos = ImGui::GetIO().MousePos;
   decs::Motion canvasPos = obj.m_GetDimensionCoords().object_Position;
   decs::Body canvasBody = obj.fusion.m_GetBodyMass();

   return ((float)imguiCursorPos.x > (float)canvasPos.x && imguiCursorPos.x < (float)(canvasPos.x + canvasBody.width) && (float)imguiCursorPos.y > (float)canvasPos.y && imguiCursorPos.y < (float)(canvasPos.y + tabMaxY));
}

void simulateMouseMovement (HWND handle, decs::FusionObject &windowObj, visuals::Canvas &canvasObj, visuals::winContainer &container) {
   if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {


      if (isCursorInsideWindow(windowObj)) {
         decs::Motion canvasPos = canvasObj.m_GetDimensionCoords().object_Position;

         if (isImguiCursorInsideTabBarWindow(canvasObj)) {

            struct {
               decs::Motion canvas;
               decs::Motion Mouse;
               RECT window;
               int InsideArea = 0;
            } pos;

            pos.Mouse = canvasObj.fusion.m_GetCursorOS();
            pos.canvas = canvasObj.fusion.m_GetMotion();
            GetWindowRect(handle, ref_ pos.window);

            while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {

               auto relative = canvasObj.fusion.m_GetCursorOS();

               relative.x += (pos.window.left - (float)pos.Mouse.x);
               relative.y += (pos.window.top - (float)pos.Mouse.y);

               container.fusion.m_SetMotion(relative);
               win::utils::setContainerPos(&container);
               Backend::getBackendObject()->windowManager->OS_RefreshMouse();
            }
         }
      }
   }
}
 

gmVoid mclass::m_doTabMovement(visuals::Canvas &Canvas) {


   simulateMouseMovement(handle, this->fusion, Canvas, deref this);
}

gmVoid mclass::m_Hide() {
   ShowWindow(handle, SW_HIDE);
}

gmVoid mclass::m_Show() {
   ShowWindow(handle, SW_SHOWNORMAL);
}

bool mclass::m_IsFocused() {
   return (GetForegroundWindow() == handle);
}

bool mclass::m_hasCanvas() {
   if (fusion.m_GetAttachmentPtr()->Canvas_count == null) {
      return false;
   }
   return true;
}
// ask OS to change window position
bool win::utils::setContainerPos(mclass *container, int opt_x1, int opt_y1) {
   if (opt_y1)
      container->fusion.orient.Motion.y = opt_y1;

   if (opt_x1)
      container->fusion.orient.Motion.x = opt_x1;

   auto res = SetWindowPos(container->handle, container->handle, container->fusion.orient.Motion.x, (int)container->fusion.orient.Motion.y, container->fusion.bounds.body.width, container->fusion.bounds.body.height, SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);

   return res;
}

// calculate alignment by mass center
decs::Motion win::CalcAlign_byMassCenter(decs::Motion Position, const decs::Body ref_ body) {
   Position.x -= (body.width / 2), Position.y -= (body.height / 2);

   return Position;
}

// organize window positions to middle
decs::Motion win::CalcRelative_MiddlePosition(decs::Body body) {
   decs::Motion adjuster = unsets;
   auto Native = utils::getNativeRes();

   adjuster.x = (Native.x / 2);
   adjuster.y = (Native.y / 2);

   return CalcAlign_byMassCenter(adjuster, body);
}

// metigate flags for positioning
gmVoid win::PrepContainerMotions(decs::FusionObject ref_ fusion) {
   fusion.orient.Cursors.os = ref_ getBackendObject() -> data.os_cursor;

   if (fusion.Metadata.flags.isFixed == false) {
      // we should inc default pos incase double windows.
      auto adjuster = win::CalcRelative_MiddlePosition(fusion.bounds.body);

      fusion.orient.Motion.x += adjuster.x,
         fusion.orient.Motion.y += adjuster.y;
   }
}

// establish styling for the window
gmVoid Establish_Styling (mclass::Handles ref_ handle, decs::FusionObject ref_ fusion) {
   using namespace winStyle;
   static regex2 r;
   struct Contexts {
      ulong style, extended_style = {0};
   };

   Contexts context;

   context.extended_style = winStyle::Context::gwl_EXSTYLE,
   context.style = winStyle::Context::gwl_STYLE;

   if (fusion.Metadata.visual == "transparent") {
      // overlay for the game window
      ulong style = ext_TRANSPARENCY;

      auto mix = 0;
      mix |= context.extended_style;
      mix |= winStyle::Perserve_Current;

      winStyle::set(handle, mix, style);
      winStyle::templates::Overlay(handle, 11000);
   }

   if (fusion.Metadata.visual == "overlay") {
      // overlay for the game window
      auto style =
         winStyle::get< ulong >(handle, context.extended_style) |
         (winStyle::ext_TOPMOST | winStyle::ext_PASSTHROUGH | ext_TRANSPARENCY | WS_EX_TOOLWINDOW);

      winStyle::set(handle, context.extended_style, style);
      winStyle::templates::Overlay(handle);
   }
   else if (fusion.Metadata.visual == "empty") {
      // unimplemented post-styling of the non-dependant OS container.
   }

   // do other necessary calls..
}

// establish container platforms
gmHandle win::Establish_Container_Platforms(decs::FusionObject ref_ fusion, ulong style) {
   astr className = fusion.Name.str + "_d311";

   winos::createWin_osd cw = unsets;

   cw.windproc_callbacker = proc::os_callbacks;

   auto winHandle = winos::createWindow(fusion.Name, className, fusion.bounds.body.width, fusion.bounds.body.height, style, fusion.Metadata.flags.isHidden, ref_ cw);

   if (winHandle) {
      auto wincontainer =
         getBackendObject()->windowManager->find_Container(fusion.Name);

      wincontainer->handle.gm = winHandle;
      wincontainer->handle.hwnd = HWND(winHandle);
      wincontainer->handle.hdc = GetDC(wincontainer->handle.hwnd);
      wincontainer->handle.hrc = win::init_pixelFormat_once(wincontainer->handle);

      winStyle::get(wincontainer->handle, winStyle::Context::gwl_USERDATA);
   }
   else {
      os::cd_lastError();   // follow with exception macro
   }

   return winHandle;
}

pContainer OS_window_init (mclass aptr_ wincontainer, const astr window_description) {
   auto ref_ fusion = wincontainer->fusion;
   using namespace winStyle;

   // preset positions
   win::PrepContainerMotions(fusion);

   ulong pre_style = null;

   WindowStyle decide_base_style = (fusion.Metadata.visual == "overlay" or
                                    fusion.Metadata.visual == "empty" or
                                    fusion.Metadata.visual == "transparent"
                                   )
                                      ? WindowStyle::POPUP   // apparently removes os tab
                                      : WindowStyle::OVERLAPPED;

   pre_style = decide_base_style;

   if (fusion.Metadata.visual == "empty") {
      pre_style = pre_style | WS_BORDER;
   }

   if (fusion.Metadata.visual == "transparent") {
      wincontainer->customTransParent = winContainer::mouseleave::inside;
   }
   gmHandle winHandle = win::Establish_Container_Platforms(fusion, pre_style);


   if (winHandle) {
      Establish_Styling(wincontainer->handle, fusion);
      win::utils::setContainerPos(wincontainer);
      return wincontainer;
   }

   return wincontainer;
}

// initialize pixel format once
HGLRC win::init_pixelFormat_once(HDC hdc) {
   PIXELFORMATDESCRIPTOR pfd = {0};


   pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
   pfd.nVersion = 1;
   pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
   pfd.iPixelType = PFD_TYPE_RGBA;
   pfd.cColorBits = 32;

   int pixelFormat = ChoosePixelFormat(hdc, &pfd);
   SetPixelFormat(hdc, pixelFormat, &pfd);

   HGLRC hrc = wglCreateContext(hdc);

   wglMakeCurrent(hdc, hrc);
   return hrc;
}
