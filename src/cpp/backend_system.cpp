

//      Backend system implementation
//
//   To Serve coreGui.cpp in a high level manner
//
//      and serve the basis of astr method
//

#define coregui_impl
#include "../h/coreGui.h"
#define ecl 1
#include "ecl.h"

tag_global extern cg::pguiMaster guimaster;
tag_global extern Backend::pCore backend;

// first thread introduced, exits and ins should be managed here.
tag_workerThread bool Backend::SessionHandler() {

   bool post_creation = null;
   classes::WindowManager ref_ manager = *backend->windowManager;

await_restart:

   manager.OS_RefreshMouse();

   volatile auto node_container = backend->windowManager->refs.getEntries();
   if (!node_container) {

      return false;
   }

   int count = null;

   sleep(20ms);
   // quite unnecessary handled in main thread
   while (node_container) {
      if (node_container->pdata->fusion.Metadata.flags.termination) {
         post_creation = trueval;
         count++;
      }
      node_container = node_container->next;
   }

   if (count < backend->windowManager->refs.Length()) {
      return false;
   }
   else if (post_creation) {
      sleeper().delay(("1s"));
      cl(" build dev session-end", "sessionHandler");

      backend->init.Session = 0;
   }

   return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  Graphic Initializer Class
////
////  initializes ImGui, Opengl
////
////

int maximum_fonts = unset;   // 93 : init val
ImFont aptr_ ImGui_Initializer::fontData[_font_size_] = unsets;
static bool fontapi_acknowledged = null;

void Backend::imgui_setFont(int num) {
   if (fontapi_acknowledged == true) {
      ImGui::PopFont();
      fontapi_acknowledged = false;
   }

   if (maximum_fonts <= num)
      num = maximum_fonts - 1;

   auto Font = (ImFont *)(ImGui_Initializer::fontData[num]);

   ImGui::PushFont(Font);
}

void Backend::imgui_setFont_api(int num) {
   fontapi_acknowledged = true;
   Backend::imgui_setFont(num);
}

int Backend::imgui_getCurrentFont() {
   return getBackendObject()->canvasManager->currentFontWidth;
}

void SetDarkOrangeTheme () {
   ImGuiStyle &style = ImGui::GetStyle();

   // Darken background color

   // Dark orange for text
   // style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.50f, 0.20f, 1.00f);

   // Dark orange for buttons
   style.Colors[ImGuiCol_Button] = ImVec4(0.80f, 0.50f, 0.20f, 0.60f);
   style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.90f, 0.60f, 0.30f, 0.70f);
   style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.40f, 0.10f, 1.00f);

   // Dark orange for frame background
   style.Colors[ImGuiCol_FrameBg] = ImVec4(0.30f, 0.20f, 0.10f, 0.54f);

   // Dark orange for header background
   style.Colors[ImGuiCol_Header] = ImVec4(0.80f, 0.50f, 0.20f, 0.55f);
   style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.80f, 0.50f, 0.20f, 0.80f);
   style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.80f, 0.50f, 0.20f, 1.00f);

   // Dark orange for separator
   style.Colors[ImGuiCol_Separator] = ImVec4(0.80f, 0.50f, 0.20f, 0.50f);

   // Dark orange for text selection background
   style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.90f, 0.60f, 0.30f, 0.35f);
}

void Backend::imgui_ApplyPadRound(float x, float y, bool RoundInstead) {
   if (RoundInstead) {
      ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, x);
   }
   else {
      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(x, y));
   }
}

void Backend::imgui_EndPadding() {
   ImGui::PopStyleVar();
}

ImGuiContext aptr_ ImGui_Initializer::Startup() {
   auto CONTEXT = ImGui::CreateContext();


   ImGuiIO &io = ImGui::GetIO();
   (void)io;

   // Enable Keyboard Controls
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

 

 
   auto FindClientDataParent = [] (std::vector< astr > Paths) -> astr {
      for (auto path : Paths) {
         if (dir::os_Pathorfile_exists(path.append("clientdata"))) {
            return path;
         }
      }
      return "";
   };

   astr clientDataDir = FindClientDataParent(
      {dir::GetExeDirectoryOnDisk(),
       "../",


#if PJC_CONSUMERBUILD == false
       "build/debug/"
#endif

      }
   );


   auto imgui_ini_path = new astr(clientDataDir + astr("clientdata/abc/imgui.ini"));

   io.IniFilename = imgui_ini_path->cstr();

   SetDarkOrangeTheme();

   static bool init_fonts = false;

   if (init_fonts == false) {

      maximum_fonts = sizeof(ImGui_Initializer::fontData) / 8;
      float font_BaseScalar = _font_BaseScalar_;

      for (int i = 0; i < maximum_fonts; i++) {

         ImGui_Initializer::fontData[i] =
            io.Fonts->AddFontFromFileTTF(clientDataDir.append("clientdata/abc/tahomabd.ttf"), font_BaseScalar);

         font_BaseScalar += _font_Scalar_multi_;
      }

      init_fonts = true;
   }

   return CONTEXT;
}

void ImGui_Initializer::init_Context(HWND HANDLE) {
   ImGui_ImplWin32_InitForOpenGL(HANDLE);
   ImGui_ImplOpenGL3_Init();
}

// update mouse position globally
gmVoid classes::WindowManager::OS_RefreshMouse() {
   POINT point;
   GetCursorPos(&point);

   backend->data.os_cursor.x = (float)point.x;
   backend->data.os_cursor.y = (float)point.y;
}

gmVoid classes::WindowManager::swapBuffers(HDC handle) {
   SwapBuffers(handle);
}

// sync the stupid winos mouse we cannot even get rid of
gmVoid
classes::WindowManager::syncInput(visuals::winContainer::Handles ref_ handle) {
   tagMSG msg = unsets;
   if (PeekMessageW(&msg, handle, NULL, NULL, PM_REMOVE) > 0) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
}

// opengl is garbage, horrendous
gmVoid classes::WindowManager::wglCurContext(
   cg::visuals::winContainer::Handles ref_ handle
) {
   wglMakeCurrent(handle.hdc, handle.hrc);
}

// Handle key events here
void static Backend::proc::HandleKeyEvent(WPARAM wParam) {
   std::cout << "Key pressed: " << wParam << std::endl;
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// annoying windows 10 callback bs
LRESULT CALLBACK Backend::proc::os_callbacks(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   using mouseleave = vw::winContainer::mouseleave;

   if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
      return true;


   auto manager = Backend::getBackendObject()->windowManager;
   pContainer Container = manager->findContainerByHwnd(hwnd);
   bool foundContainer = (Container) ? true : false;

   if (!foundContainer) {
      goto passWindProc;
   }

   switch (uMsg) {

      case WM_CLOSE: {
         getBackendObject()->init.Session = null;
         return DefWindowProc(hwnd, uMsg, wParam, lParam);
      }
      case WM_MOUSELEAVE: {
         if (Container->customTransParent == mouseleave::not_custom) {
            break;
         }
         else {
            Container->customTransParent = mouseleave::wants_outside;
            break;
         }
      }
      case WM_NCACTIVATE: {
         // Check if the application is being deactivated

         if (wParam == FALSE) {
            // Application is being deactivated, set flag indicating mouse is inside
            if (Container->customTransParent != mouseleave::not_custom)
               Container->customTransParent = mouseleave::inside;
         }
         break;
      }

      case WM_DESTROY: {

         Container->fusion.Metadata.flags.termination = true;


         return DefWindowProc(hwnd, uMsg, wParam, lParam);
      }

      case WM_SETCURSOR:
         // Handle the WM_SETCURSOR message
         SetCursor(LoadCursor(NULL, IDC_ARROW));   // Set the cursor to a hand cursor
         return TRUE;

      default: {
      passWindProc:
         return DefWindowProc(hwnd, uMsg, wParam, lParam);
      }
   }

   return 0;
}

Pointers::pCanvas classes::CanvasManager::find_Canvas(astr Name) {
   auto loopCanvas =
      Backend::getBackendObject()->canvasManager->refs.getlooper();

   while (loopCanvas) {
      if (loopCanvas.source->fusion.Name == Name) {
         return loopCanvas.source;
      }
   }

   return 0;
}

pContainer classes::WindowManager::findContainerByHwnd(gmHandle handle) {
   auto SeekByHwnd = [] (cg::visuals::winContainer *win, HWND handle) {
      if (win->handle.hwnd != handle)
         return (cg::visuals::winContainer *)unset;
      else
         return win;
   };

   return refs.node_callbackEx< cg::visuals::winContainer aptr_, HWND >(
      SeekByHwnd,
      (HWND)handle
   );
};

#include "../include/guimaster.h"

visuals::winContainer aptr_
Backend::classes::WindowManager::find_Container(astr Name) {
   // messy as hell useless bloat
   if (lastRequestedContainer and
       lastRequestedContainer->fusion.Name == Name.cstr()) {
      return lastRequestedContainer;
   }

   visuals::winContainer aptr_ ret_container = unset;

   auto containers = backend->windowManager->refs.getEntries();

   while (containers) {
      if (containers->pdata->fusion.Name == Name.cstr()) {
         ret_container = containers->pdata;
         break;
      }

      containers = containers->next;
   }

   if (ret_container == null) {
      cl("did not find winContainer Error!");
   }
   else {
   }

   return ret_container;
}


noret Backend::classes::CanvasManager::UpdateImGuiCurosr() {
   auto pos = ImGui::GetCursorPos();
   this->ImGuiWindowCursor.x = pos.x, ImGuiWindowCursor.y = pos.y;
}

visuals::Elements aptr_
Backend::classes::ElementManager::Request_New_Element() {
   return refs.getNewObject();
}

Pointers::pCanvas Backend::classes::CanvasManager::Request_New_Canvas() {
   return refs.getNewObject();
}

visuals::winContainer aptr_
Backend::classes::WindowManager::Request_New_Container() {
   backend->init.Session = 1;

   return refs.getNewObject();
}

noret Init_Managers () {
   backend->windowManager = new Backend::classes::WindowManager;
   backend->elementManager = new Backend::classes::ElementManager;
   backend->canvasManager = new Backend::classes::CanvasManager;
}

gmVoid cg::initBackend() {
   allocnull_obj(backend, Backend::pCore);

   Init_Managers();

   backend->windowManager->diagnostics = unsets;
   backend->windowManager->lastRequestedContainer = unset;

   backend->windowManager->OS_RefreshMouse();
   backend->windowManager->threadManager = lib::threadmaster();
   backend->windowManager->threadManager.GlobalSleep("10ms");

   backend->windowManager->threadManager.setup.newEternal(
      _ref Backend::SessionHandler,
      "sH"
   );
}

cg::Backend::pCore Backend::getBackendObject() {
   return backend;
}
