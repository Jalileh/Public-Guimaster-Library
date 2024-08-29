
#pragma once

#define COREGUI_H

#include "../imgui/imgui.h"

#include "../include/gmmath.h"


#include "api/threadMaster.h"

extern "C" library_api pvoid CG ();

namespace coregui {
   namespace Pointers {}
   namespace Api_types {}
   namespace visuals {}
   namespace Backend {}

}   // namespace coregui

namespace coregui::Backend {
   template < typename t >
   t _getosCursor ();
}

// restriction for using namespaces
#ifndef coregui_impl
namespace {

   using namespace coregui::Pointers;
   using namespace coregui;
   using namespace coregui::visuals;
}   // namespace

#else
using namespace coregui::Pointers;
using namespace coregui;

#endif

#define cg_define_Pointers namespace coregui::Pointers
#define cg_define_Api_types namespace coregui::Api_types

using gmVoid = void;

using gmHandle = pvoid;

namespace cg = coregui;

namespace coregui {

#include "visualFusion.h"

}
#include "..\dllCross.h"

namespace coregui::visuals {
   class Canvas;

}


#include "Container.h"

#include "Elements.h"

#include "Canvas.h"

namespace coregui::Backend {
   // should not be swear-wording here
   struct Init {
      bool pixelForm;
      int Session;
      int callbackDone = unset;
   };

}   // namespace coregui::Backend

#if defined(coregui_impl)
namespace coregui::Backend {

#   include "backend_system.h"

}

#endif

namespace vw = cg::visuals;
namespace v = cg::visuals;


namespace coregui::Api_types {

   using CallbackRenderFn = void (*)();

   namespace Design {
      typedef gmHandle (*family)(astr_DLL family_description);
      typedef void (*widget)(astr_DLL widget_description);
      typedef void (*canvas)(astr_DLL canvas_description, CallbackRenderFn renderSpace);

      typedef gmHandle (*container)(astr_DLL window_description, CallbackRenderFn no_canvas_renderSpace);
   }   // namespace Design
   namespace live {
      typedef void (*Containers)(astr_DLL Name_or_All);

      using fusionData_Canvas = coregui::Fusion::decs::FusionObject
      aptr_ (*)(astr_DLL findbyName);

      using Canvas_localFlags = visuals::Canvas::Flags
      aptr_ (*)(astr_DLL findbyName);

      using Container_ObjectData = visuals::winContainer _ptr (*)(astr_DLL findbyName);
      using Canvas_ObjectData = visuals::Canvas _ptr (*)(astr_DLL findbyName);

   }   // namespace live

   namespace misc {
      typedef void (*imgui_setFont)(int num);
      typedef int (*imgui_getCurrentFont)();

   }   // namespace misc

}   // namespace coregui::Api_types

namespace coregui {

   struct GuiMasterApi {
      struct Design_AP {
         Api_types::Design::widget Widget;
         Api_types::Design::container Container;
         Api_types::Design::canvas Canvas;
         Api_types::Design::family Family;
      };
      Design_AP Design;

      struct RLive {
         using FN_Visbility = noret (*)(astr_DLL Name);
         Api_types::live::Containers Execute_Container;
         noret (*GlobalHide)();
         noret (*GlobalShow)();

         FN_Visbility ContainerHide;
         FN_Visbility ContainerShow;
      };
      RLive Live;

      struct Miscellanious {
         Api_types::misc::imgui_setFont FontSet;

         // this is the current canvas font
         Api_types::misc::imgui_getCurrentFont FontGetCanvas;

         void (*EndPadRound)();
         void (*ApplyPadRound)(float x, float y, bool RoundInstead);

         imgui_fptr aptr_ imfptr;
         OpenGl_fptr aptr_ glfptr;
      };

      Miscellanious Misc = unsets;

      Api_types::live::fusionData_Canvas GetCanvasFusion;

      Api_types::live::Canvas_localFlags GetCanvasLFlags;
      Api_types::live::Container_ObjectData GetContainerObjectData;

      struct Status {
         coregui::Backend::Init aptr_ init;
      };
      Status statusInfo;
   };

   using pguiMaster = GuiMasterApi aptr_;

}   // namespace coregui

namespace coregui {
   cg::pguiMaster getGuiMaster ();
   StatusCode FreeGuiMaster ();
   gmVoid initBackend ();
}   // namespace coregui

#if defined(coregui_impl)
using namespace cg;
using namespace cg::Fusion;
using namespace Backend;

// #include <GL/glew.h>
// #include <GL/GL.h>
#endif
