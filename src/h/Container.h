#pragma once
;
namespace winStyle {
   enum WindowStyle : ulong {
      OVERLAPPED = 0x00000000L,
      POPUP = 0x80000000L,
      CHILD = 0x40000000L,
      MINIMIZE = 0x20000000L,
      VISIBLE = 0x10000000L,
      DISABLED = 0x08000000L,
      CLIPSIBLINGS = 0x04000000L,
      CLIPCHILDREN = 0x02000000L,
      MAXIMIZE = 0x01000000L,
      CAPTION = 0x00C00000L, /* BORDER | DLGFRAME */
      BORDER = 0x00800000L,
      DLGFRAME = 0x00400000L,
      VSCROLL = 0x00200000L,
      HSCROLL = 0x00100000L,
      SYSMENU = 0x00080000L,
      THICKFRAME = 0x00040000L,
      GROUP = 0x00020000L,
      TABSTOP = 0x00010000L,
      MINIMIZEBOX = 0x00020000L,
      MAXIMIZEBOX = 0x00010000L,

      ext_DLGMODALFRAME = 0x00000001L,
      ext_NOPARENTNOTIFY = 0x00000004L,
      ext_TOPMOST = 0x00000008L,
      ext_ACCEPTFILES = 0x00000010L,
      ext_PASSTHROUGH = 0x00000020L,
      ext_MDICHILD = 0x00000040L,
      ext_TOOLWINDOW = 0x00000080L,
      ext_WINDOWEDGE = 0x00000100L,
      ext_CLIENTEDGE = 0x00000200L,
      ext_CONTEXTHELP = 0x00000400L,
      ext_RIGHT = 0x00001000L,
      ext_LEFT = 0x00000000L,
      ext_RTLREADING = 0x00002000L,
      ext_LTRREADING = 0x00000000L,
      ext_LEFTSCROLLBAR = 0x00004000L,
      ext_RIGHTSCROLLBAR = 0x00000000L,
      ext_CONTROLPARENT = 0x00010000L,
      ext_STATICEDGE = 0x00020000L,
      ext_APPWINDOW = 0x00040000L,
      ext_TRANSPARENCY = WS_EX_LAYERED,
      ext_OVERLAPPEDWINDOW = (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE),
      ext_PALETTEWINDOW = (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
   };
   enum Context : int {
      gwl_STYLE = (16),
      gwl_WNDPROC = (4),
      gwl_HINSTANCE = (6),
      gwl_HWNDPARENT = (8),
      gwl_EXSTYLE = (20),
      gwl_USERDATA = (21),
      gwl_ID = (12),
      gwl_test = (13),
      Perserve_Current = 0x1000
   };

}   // namespace winStyle

namespace winos {
   struct createWin_osd {
      WNDPROC windproc_callbacker = unset;
   };

   template < typename style_Type >
   gmHandle static createWindow(astr Name_, astr className_, float width, float height, style_Type style, bool isHidden, createWin_osd aptr_ extra);
}   // namespace winos

// abstracted away
namespace {
   void inline set_Transparent(gmHandle handle, BYTE alpha) {
      HWND hwnd = HWND(handle);
      SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), alpha, LWA_COLORKEY | LWA_ALPHA);
      //  I do not know if this is the correct one ? :
      //  SetLayeredWindowAttributes(hwnd, RGB(255, 0, 255), 0, LWA_COLORKEY);
   }

}   // namespace

namespace winStyle {
   template < typename style_Type, typename style_Context >
   StatusCode inline set(pvoid winHandle, style_Context _context, style_Type style);

   template < typename style_cx >
   auto inline get(pvoid winHandle, style_cx context);

   namespace templates {
      void inline Overlay(gmHandle Handle, int frequency = 128);
   }
}   // namespace winStyle

template < typename style_Type, typename style_Context >
StatusCode inline winStyle::set(pvoid winHandle, style_Context _context, style_Type style) {
   using namespace winStyle;

   along Context = along(_context);

   ulong styles = ulong(style);


   // dont screw this one up
   if ((Context & Context::Perserve_Current) > 0) {
      Context &= 0xFF;
      Context = -Context;   // gwl_EXSTYLE


      ulong current_style = GetWindowLongPtr((HWND)winHandle, Context);

      if (current_style)
         styles = styles | current_style;
   }
   else {
      // has to be inverted
      Context = -along(Context);
   }


   auto ret = (SetWindowLongPtr((HWND)winHandle, Context, styles) > null)
                 ? st::Complete
                 : st::Invalid;

   if (ret == code::Invalid) {
      auto error = os::utils::lastError_Str();
   }


   SetWindowPos((HWND)winHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

   return ret;
}

template < typename style_cx = winStyle::Context >
auto inline winStyle::get(pvoid winHandle, style_cx context) {
   return (ULONG)GetWindowLongPtrW((HWND)winHandle, -along(context));
}

void inline winStyle::templates::Overlay(gmHandle Handle, int frequency) {
   set_Transparent(Handle, frequency);
}

namespace coregui {
   namespace visuals {
      class winContainer;

   }

}   // namespace coregui

class cg::visuals::winContainer {
   using CallbackRenderFn = void (*)();

 public:
   struct DynamicFlags {
      bool b_override_swapBuffers;
      bool b_override_gl_calls;
   };
   DynamicFlags dynamicFlags = unsets;

 public:
   class Handles {
    public:
      HWND hwnd = unset;
      gmHandle gm = unset;
      HDC hdc = unset;
      HGLRC hrc = unset;
      HRGN hrgn = unset;
      ImGuiContext aptr_ imGuiContext = unset;

      operator HWND() {
         return hwnd;
      }
      operator gmHandle() const {
         return gm;
      }
      operator HDC() const {
         return hdc;
      }
   };

 public:
   Fusion::decs::FusionObject fusion;
   Handles handle;
   ulong userdata = unsets;

   // this is for the cases where
   // we are transparent and need to work
   // differently because we cannot hide window anymore
   enum class mouseleave { not_custom,
                           inside,
                           wants_outside,
                           is_outside };
   mouseleave customTransParent;


   CallbackRenderFn no_canvas_callBackRenderFn = nullset;

 public:
   bool m_hasCanvas ();

   gmVoid m_doTabMovement(visuals::Canvas & Canvas);

   gmVoid m_Hide ();
   gmVoid m_Show ();
   bool m_IsFocused ();
};

cg_define_Pointers {
   using pContainer = visuals::winContainer aptr_;
}

// entry for Container and OS link Process
Pointers::pContainer OS_window_init (visuals::winContainer aptr_ wincontainer, const astr window_description);
