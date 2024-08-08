#pragma once
#define GM_IMPL inline


#include "..\guimaster.h"

#if GMAPI_BUILDER == true
bool gmbuilder_initial_override (astr ref_ incoming_visual, auto is_canvas);
#   define gmbuilder_override_init(visual, is_canvas)            \
      if (gmbuilder_initial_override(visual, is_canvas) == true) \
         return;
#else

#   define gmbuilder_override_init
#endif


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.GMAPI - high level interface
////
////
////
////

class gma::gmapi {
 public:
   noret hideCanvas (astr canvasName) {
      gmcg::MiddleWare_CG.getCG()
         ->GetCanvasFusion(canvasName)
         ->Metadata.flags.isHidden = true;
   }

   noret ShowCanvas (astr canvasName) {
      gmcg::MiddleWare_CG.getCG()
         ->GetCanvasFusion(canvasName)
         ->Metadata.flags.isHidden = false;
   }

   pguiMaster getCG () {
      return gmcg::MiddleWare_CG.getCG();
   }

   auto getSessionInfo () {
      return gmcg::MiddleWare_CG.getCG()->statusInfo.init;
   }

   auto OnActiveSession () {
      return gmcg::MiddleWare_CG.getCG()->statusInfo.init->Session;
   }

   inline auto runAll (astr TimeDelay) {
      this->run("all");
      sleeper().delay(TimeDelay);
   }

   // providing callback results in a non canavas (imgui) win
   template < typename no_Canvas_fn = CallbackRenderFn >
   noret designContainer (astr Description, no_Canvas_fn callback = 0) {

      gmbuilder_override_init(Description, callback);
      this->getCG()->Design.Container(Description, callback);
   }

   noret designCanvas (astr Description, CallbackRenderFn fnCallback) {
      this->getCG()->Design.Canvas(Description, fnCallback);
   }

   auto enabled (astr ToggleName) {
      if (gmc::globals::MiddleWare_CG.CallbacksDone() == true)
         return gmc::globals::handlerUiMem.Enabled(ToggleName);
      else
         return false;
   }
   // resetIfTrue resets button, should only be used by one
   auto pressed (astr buttonName, bool ResetifTrue = true) {
      if (gmc::globals::MiddleWare_CG.CallbacksDone())
         return gmc::globals::handlerUiMem.clicked(buttonName, ResetifTrue);
      else
         return false;
   }

   auto awaitEnabled (astr ToggleName) {
      return gmc::globals::handlerUiMem.Enabled_await(ToggleName);
   }
   // resetIfTrue resets button, should only be used by one
   auto awaitPressed (astr buttonName, bool ResetifTrue = true) {
      return gmc::globals::handlerUiMem.clicked_await(buttonName);
   }

   // you get back the group member Name that was pressed
   astr any_pressed_in_group (astr groupName, bool ResetifTrue = true) {

      for (auto &group_member : _gmIdentifierList) {
         if (group_member.HasGroup and groupName == group_member.Group and awaitPressed(group_member.Name)) {
            return group_member.Name;
         }
      }

      return "";
   }

   auto Input (astr inputName) {
      if (gmc::globals::MiddleWare_CG.CallbacksDone())
         return gmc::globals::handlerUiMem.input.Find(inputName, false)->uidata.string;
      else
         return pchar(0);
   }

   auto awaitInput (astr inputName) {
      return gmc::globals::handlerUiMem.input.Find_await(inputName)->uidata.string;
   }

   gmVec2 Vector2 (astr inputName) {
      if (gmc::globals::MiddleWare_CG.CallbacksDone())
         return gmc::globals::handlerUiMem.modifiers_vector2.Find(inputName, false)->uidata;
      else
         return {};
   }

   gmVec2 awaitVector2 (astr inputName) {
      return gmc::globals::handlerUiMem.modifiers_vector2.Find_await(inputName)->uidata;
   }

   auto awaitFloat (astr inputName) {
      return gmc::globals::handlerUiMem.modifiers_float.Find_await(inputName)->uidata;
   }

   auto global_hide () {
      getCG()->Live.GlobalHide();
   }

   auto global_show () {
      getCG()->Live.GlobalShow();
   }

   auto ShowContainer (astr name) {
      getCG()->Live.ContainerShow(name);
   }

   auto HideContainer (astr name) {
      getCG()->Live.ContainerHide(name);
   }

   noret run (astr name) {
      getCG()->Live.Execute_Container(name);
   }

   noret load ();
};

tag_global static gma::gmapi gm;
