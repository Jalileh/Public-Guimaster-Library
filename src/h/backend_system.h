#pragma once
#define BACKEND_SYSTEM_H
#include "coreGui.h"
namespace {
   struct backendData {
      cg::Fusion::decs::Motion os_cursor;
   };

}   // namespace


namespace classes {
   class WindowManager;
   class ElementManager;
   class CanvasManager;
}   // namespace classes

// one callback interface for overlays should exist here.
class classes::CanvasManager {
 public:
   nodem< visuals::Canvas > refs;
   int currentFontWidth = unset;

   decs::Motion ImGuiWindowCursor;

   noret UpdateImGuiCurosr ();

   Pointers::pCanvas Request_New_Canvas ();

   Pointers::pCanvas find_Canvas (astr Name);
};

// prioritize usage from here, Container has recursive memory-waste for likewise
// operations
class classes::WindowManager {
 public:
   struct Diagnostics_ {
      int clocks;
      int Speed;
   };

   nodem< coregui::visuals::winContainer > refs;
   Diagnostics_ diagnostics;
   pContainer lastRequestedContainer;
   _threadMaster::Api threadManager;

 public:
   pContainer Request_New_Container ();

   pContainer find_Container (astr Name);

   pContainer findContainerByHwnd (gmHandle handle);

   gmVoid OS_RefreshMouse ();

   gmVoid swapBuffers (HDC handle);

   gmVoid syncInput (cg::visuals::winContainer::Handles ref_ handle);

   gmVoid wglCurContext (cg::visuals::winContainer::Handles ref_ handle);
   // gmvoid waglo( )
};

class classes::ElementManager {
 public:
   nodem< coregui::visuals::Elements > refs;

 public:
   pElements Request_New_Element ();

   pElements find_Element (astr Name);
};

class Core {
 public:
   classes::WindowManager aptr_ windowManager;

   classes::ElementManager aptr_ elementManager;

   classes::CanvasManager aptr_ canvasManager;

 public:
   backendData data = unsets;
   coregui::Backend::Init init;
};

using pCore = Core aptr_;

pCore getBackendObject ();

namespace proc {
   void inline HandleKeyEvent(WPARAM wParam);

   LRESULT CALLBACK os_callbacks (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

}   // namespace proc
    // runs in thread

bool SessionHandler ();

template < typename t >
t _getosCursor () {
   return (decs::Motion aptr_)ref_ getBackendObject() -> data.os_cursor;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  Graphic Initializer Class
////
////  initializes ImGui, Opengl
////
////

#define _font_size_ 16
#define _font_BaseScalar_ 11.f
#define _font_Scalar_multi_ 2.5f

class ImGui_Initializer {
 public:
   ImGuiContext aptr_ Startup ();
   void init_Context (HWND handle);


   static ImFont aptr_ fontData[_font_size_];
   const int fontData_defaultSize = 3;
};
void imgui_setFont (int num);

void imgui_setFont_api (int num);

int imgui_getCurrentFont ();

void imgui_ApplyPadRound (float x, float y, bool RoundInstead);
void imgui_EndPadding ();
