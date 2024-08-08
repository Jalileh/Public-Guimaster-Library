
#define coregui_impl
#include "../h/coreGui.h"

#include "GL/GL.h"

#define ecl 1
#include "ecl.h"

eclid("coregui.cpp");

tag_global cg::pguiMaster guimaster = unset;
tag_global Backend::pCore backend = unset;

// GUI  objects and window object are proxied to backend
//
//    GMAPI dll accesspoints codebase follows
//
//        currently only static renders
//
//            heavily based on strings
//

namespace design {
   gmHandle Family (astr family_description);

   gmVoid Elements (astr_DLL widget_description);

   gmVoid Canvas (astr_DLL canvas_description, cg::Api_types::CallbackRenderFn RenderCallbackFn);

   gmHandle Container (astr_DLL window_description, cg::Api_types::CallbackRenderFn no_canvas_CallBack);
}   // namespace design

namespace liveInstance {
   gmVoid Elements (decs::FusionObject aptr_ inside_canvas);

   gmVoid Canvas_Entry (decs::FusionObject aptr_ vContainer);

   pContainer Container_Entry (pContainer container);

}   // namespace liveInstance

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.api accessories - grow here
////
////
////
////


visuals::winContainer _ptr apiRoute_GetContainerObjectData (astr_DLL _FindByName) {
   astr FindByName = _FindByName;
   return backend->windowManager->find_Container(FindByName);
}


noret test_render () {
}


auto apiRoute_GlobalShow () {
   backend->windowManager->refs.for_each([] (visuals::winContainer _ref containers) {
      containers.m_Show();
   });
}
auto apiRoute_GlobalHide () {
   backend->windowManager->refs.for_each([] (visuals::winContainer _ref containers) {
      containers.m_Hide();
   });
}

auto apiRoute_Show (astr_DLL _Name) {
   astr Name = _Name;
   backend->windowManager->refs.for_each([_ref] (visuals::winContainer _ref containers) {
      if (Name == containers.fusion.Name)
         containers.m_Show();
   });
}
auto apiRoute_Hide (astr_DLL _Name) {
   astr Name = _Name;
   backend->windowManager->refs.for_each([_ref] (visuals::winContainer _ref containers) {
      if (Name == containers.fusion.Name)
         containers.m_Hide();
   });
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.Canvas Live
////
////  - render for gui occurs here. as well as api access
////
////


coregui::Fusion::decs::FusionObject aptr_
apiRoute_canvas_ShareFusion (astr_DLL _Name) {
   astr Name = _Name;
   return ref_ backend->canvasManager->find_Canvas(Name)->fusion;
}

visuals::Canvas::Flags aptr_ apiRoute_canvas_ShareLocalFlags (astr_DLL _Name) {
   astr Name = _Name;
   return ref_ backend->canvasManager->find_Canvas(Name)->localFlags;
}

// implement callbacks here
bool is_not_Canvas_run (pContainer container) {

   if (container->no_canvas_callBackRenderFn) {


      container->no_canvas_callBackRenderFn();
      return true;
   }

   return false;
}

gmVoid ApiRoute_Canvas (pContainer container) {
   if (true == is_not_Canvas_run(container)) {
      return;
   }

   if (container->m_hasCanvas() == false) {
      return;
   }


   ImGui::SetCurrentContext(container->handle.imGuiContext);

   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplWin32_NewFrame();
   ImGui::NewFrame();

   backend->canvasManager->UpdateImGuiCurosr();

   backend->canvasManager->refs.for_each_await([ref_] (visuals::Canvas &Canvas) {
      if (Canvas.Owner != container->fusion.Name)
         return StatusCode::Unresolved;

      if (Canvas.localFlags.is_ChildWindow == false and Canvas.fusion.Metadata.flags.isHidden == false) {

         Canvas.runInstanceEntry();
      }

      return StatusCode::Achieving;
   });


   ImGui::Render();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

   if (getBackendObject()->init.callbackDone == false) {
      getBackendObject()->init.callbackDone = true;
   }
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.Container Live
////
////
////
////

// calls after Container Entry
pContainer Container_PostGPU (pContainer container) {
   using mouseleave = vw::winContainer::mouseleave;
   if (container->m_hasCanvas() == false) {
      return container;
   }

   backend->canvasManager->refs.for_each_await([ref_] (visuals::Canvas &canvas) {
      if (canvas.Owner != container->fusion.Name)
         return StatusCode::Unresolved;


      // process all post calls of container and their associations
      if (container->m_IsFocused()) {
         if (canvas.localFlags.Impostor) {
            container->m_doTabMovement( canvas );
         }

         // we had to implement hide/show for these not intended for overlay.
      }
      else if (container->customTransParent == mouseleave::wants_outside and GetKeyState(VK_LBUTTON) & 0x8000) {
         container->customTransParent = mouseleave::is_outside;
         ShowWindow(container->handle, SW_SHOWMINIMIZED);
      }


      return StatusCode::Achieving;
   });
   return container;
}

//  adheer to gpu code as much as possible
pContainer liveInstance::Container_Entry(pContainer container) {

   if (container->dynamicFlags.b_override_gl_calls == false) {
      glClear(GL_DEPTH_BUFFER_BIT);
      glClear(GL_COLOR_BUFFER_BIT);
   }

   classes::WindowManager aptr_ manager = backend->windowManager;

   manager->wglCurContext(container->handle);
   manager->syncInput(container->handle);

   // enter Canvas System
   ApiRoute_Canvas(container);

   if (container->dynamicFlags.b_override_swapBuffers == false)
      manager->swapBuffers(container->handle);


   return Container_PostGPU(container);
}

gmVoid ApiRoute_Container (astr_DLL _container_name) {
   astr container_name = _container_name;


   if (container_name == "all") {
      backend->windowManager->refs.node_callback(liveInstance::Container_Entry);
      return;
   }

   // explicit container requested
   auto DesiredContainer =
      backend->windowManager->find_Container(container_name);

   if (DesiredContainer) {
      liveInstance::Container_Entry(DesiredContainer);
   }
   else {
      cle_private("Unable to find Container Name!", "visualGroup_Container");
   }

   return;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.Elements - unused
////
////
////

gmVoid design::Elements(astr_DLL _widget_description) {
   astr widget_description = _widget_description;

   pElements elements = backend->elementManager->Request_New_Element();

   elements->fusion.m_initDescription(widget_description, "element");
   elements->fusion.m_mapGenerics();
   auto description = widget_description;

   Fusion::Parse::Positions(description, elements->fusion);
   Fusion::Parse::Bounds(description, elements->fusion);

   elements->Owner = elements->fusion.desc.description.ExtractWord("owner.\a");

   // pCanvas canvas_owner =
   // backend->canvasManager->find_Canvas(elements->Owner);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.Canvas Design
////
////
////
////

// register attachments here
void Canvas_Attachments (pCanvas canvas) {
}

gmVoid design::Canvas(astr_DLL _canvas_description, cg::Api_types::CallbackRenderFn RenderCallbackFn) {
   astr canvas_description = _canvas_description;

   classes::CanvasManager aptr_ Manager = backend->canvasManager;

   pCanvas canvas = Manager->Request_New_Canvas();

   canvas->fusion.m_initDescription(canvas_description, "canvas");
   canvas->fusion.m_mapGenerics();

   Fusion::Parse::Positions(canvas_description, canvas->fusion);
   Fusion::Parse::Bounds(canvas_description, canvas->fusion);

   canvas->ParseFlags();

   canvas->Owner = canvas->fusion.desc.description.ExtractWord("owner.\a");

   pContainer canvas_container =
      backend->windowManager->find_Container(canvas->Owner);

   if (canvas_container == unset) {
      pCanvas motherCanvas = Manager->find_Canvas(canvas->Owner);
       motherCanvas->localFlags.HasChildWindows = true;
      canvas->localFlags.is_ChildWindow = true;

      canvas->callBackRenderFn = RenderCallbackFn;
      return;
   }

   Backend::ImGui_Initializer imgui;

   static bool ImGuiInitialized = false;

   if (ImGuiInitialized == false) {

      canvas_container->handle.imGuiContext = imgui.Startup();
      imgui.init_Context(canvas_container->handle);
   }
   ImGuiInitialized = true;

   visuals::Canvas::helper::LinkWindowflags(canvas, canvas_container);
   canvas->callBackRenderFn = RenderCallbackFn;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.Container Design
////
////
////
////

gmHandle design::Container(astr_DLL _window_description, cg::Api_types::CallbackRenderFn no_canvas_CallBack) {
   astr window_description = _window_description;
   pContainer container = backend->windowManager->Request_New_Container();
   container->fusion.m_initDescription(window_description, "container");
   container->fusion.m_mapGenerics();

   Fusion::Parse::Positions(window_description, container->fusion);

   Fusion::Parse::Bounds(window_description, container->fusion);

   if (container->fusion.Metadata.visual == false) {
      container->fusion.Metadata.visual = "default";
   }

   Fusion::Parse::Primitive_Flags(window_description, ref_ container->fusion);


   container->no_canvas_callBackRenderFn = no_canvas_CallBack;

   return OS_window_init(container, window_description)->handle;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.LIBRARY STARTUP
////
//// - dll and manual map compatible . 
////
////

gmVoid PrepareLibrary (cg::pguiMaster CGM_lib) {
   guimaster = CGM_lib;

   guimaster->Misc.imfptr = init_ImFptr();
   guimaster->Misc.glfptr = init_GLFptr();

   cg::initBackend();

   guimaster->statusInfo.init = _ref backend->init;
}

using t = decltype(&apiRoute_canvas_ShareFusion);

gmVoid SetfunctionPointers (cg::pguiMaster guimaster) {
   fptr(guimaster->Design.Container, design::Container);

   fptr(guimaster->Design.Canvas, design::Canvas);

   fptr(guimaster->Design.Widget, design::Elements);

   // fptr(guimaster->Design.Family, design::Family);

   fptr(guimaster->Live.Execute_Container, ApiRoute_Container);

   fptr(guimaster->Misc.FontSet, imgui_setFont_api);
   fptr(guimaster->Misc.FontGetCanvas, imgui_getCurrentFont);

   fptr(guimaster->Misc.ApplyPadRound, imgui_ApplyPadRound);
   fptr(guimaster->Misc.EndPadRound, imgui_EndPadding);

   // misc and others
   {

      fptr(guimaster->GetContainerObjectData, apiRoute_GetContainerObjectData);

      fptr(guimaster->GetCanvasFusion, apiRoute_canvas_ShareFusion);
      fptr(guimaster->GetCanvasLFlags, apiRoute_canvas_ShareLocalFlags);

      fptr(guimaster->Live.GlobalHide, apiRoute_GlobalHide);
      fptr(guimaster->Live.GlobalShow, apiRoute_GlobalShow);
      fptr(guimaster->Live.ContainerShow, apiRoute_Show);
      fptr(guimaster->Live.ContainerHide, apiRoute_Hide);
   }
}

coregui::pguiMaster initGuiMaster () {
   cg::pguiMaster guimaster = unset;
   allocnull_obj(guimaster, coregui::pguiMaster);
   SetfunctionPointers(guimaster);
   PrepareLibrary(guimaster);
   return guimaster;
}

coregui::pguiMaster cg::getGuiMaster() {
   return (guimaster == unset) ? initGuiMaster() : guimaster;
}

extern "C" library_api pvoid CG () {
   return (pvoid)cg::getGuiMaster();
}
