#define coregui_impl
#include "../h/coreGui.h"

#include "imgui/imgui.h"

using helper = visuals::Canvas::helper;


_Canvas_DIMENSION_POS _ref visuals::Canvas::m_GetDimensionCoords() {
   return this->encapsulated_imgui_coordinates;
}

noret visuals::Canvas::m_UpdateDimensionCoords() {
   this->encapsulated_imgui_coordinates.Cursor = &getBackendObject()->canvasManager->ImGuiWindowCursor;
   auto &SelfPos = this->encapsulated_imgui_coordinates.object_Position;

   auto curpos = ImGui::GetWindowPos();
   SelfPos.y = curpos.y, SelfPos.x = curpos.x;
}

/*
   Implementation of Canvas system
  @brief Canvas-system and said properties.



*/
// once per canvas [ fusion input is set up ]

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.render code
////
////
////
////

void visuals::Canvas::imgui_Begin() {
   if (localFlags.is_ChildWindow == false) {
      ImGui::Begin(fusion.Name, ref_ localFlags.open, flagAccumilate);
   }
   else {
      ImGui::BeginChild(
         fusion.Name.cstr(),
         {fusion.m_GetBodyMass().width, fusion.m_GetBodyMass().height},
         0,
         flagAccumilate
      );
   }

   // update dimension coords here we can easily get call
   this->m_UpdateDimensionCoords();
}

void visuals::Canvas::imgui_End() {
   if (localFlags.is_ChildWindow == false) {
      ImGui::End();
   }
   else {
      ImGui::EndChild();
   }
}

void visuals::Canvas::ifany_callChildWindows() {

   if (this->localFlags.HasChildWindows and
       localFlags.is_ChildWindow == false) {

      getBackendObject()->canvasManager->refs.for_each_await([ref_] (visuals::Canvas &Canvas) {
         if (Canvas.Owner not this->fusion.Name or
             Canvas.fusion.Metadata.flags.isHidden == true)
            return Code::Unresolved;


         ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 8));
         ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0733, 0.0720, 0.0800, 1.00f));


         Canvas.runInstanceEntry();


         ImGui::PopStyleColor();
         ImGui::PopStyleVar();

         return code::Achieving;
      });
   }
}

void visuals::Canvas::DrawInstances() {

   imgui_Begin();

   this->callBackRenderFn();
   ifany_callChildWindows();

   imgui_End();

   ImGui::PopFont();
}

void visuals::Canvas::runInstanceEntry() {

   updateCalls();   // handles all our necessary calls like positioning width
                    // ect...

   getBackendObject()->canvasManager->currentFontWidth =
      fontWidth;    // compatibility for mmap cross-data

   imgui_setFont(
      fontWidth
   );   // all our canvas have a default font that we can specify

   // execution of our canvas begins..
   DrawInstances();
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.fusion integration
////
////
////
////

void visuals::Canvas::init_Metadata() {
   localFlags.fusionDataSet = true;
   decs::Motion motion = fusion.m_GetMotion();

   // not accepting null win values
   if (fusion.m_GetBodyMass().width > 0 and fusion.m_GetBodyMass().height > 0 or
       localFlags.Impostor) {

      ImGui::SetNextWindowSize(
         {fusion.m_GetBodyMass().width, fusion.m_GetBodyMass().height}
      );
   }

   if (motion.x != 0 or motion.y != 0) {
      ImGui::SetNextWindowPos({motion.x, motion.y});
      localFlags.init_Positioned = true;
   }

   fontWidth = fusion.m_Getdescription().ExtractWord("font.\a");

   if (fontWidth == unset) {
      fontWidth = 5;
   }
}

void visuals::Canvas::setPosition(decs::Motion newPos) {
   fusion.m_SetMotion(newPos);
   localFlags.init_Positioned = false;
}

void visuals::Canvas::updateCalls() {

   decs::Motion motion = fusion.m_GetMotion();

   if (localFlags.fusionDataSet == false) {
      init_Metadata();
   }
   else if (localFlags.init_Positioned == false and
            fusion.Metadata.flags.isFixed == false) {

      if (motion.x > 0 or motion.y > 0) {
         ImGui::SetNextWindowPos({motion.x, motion.y});
         localFlags.init_Positioned = true;
      }
   }
   else if (localFlags.is_ChildWindow == true) {
      ImGui::SetCursorPos({motion.x, motion.y});
   }
}

noret visuals::Canvas::ParseFlags() {
   if (fusion.m_Getdescription().match("notab")) {
      flagAccumilate |= ImGuiWindowFlags_NoTitleBar;
   }

   if (false == fusion.m_Getdescription().match("\bflags.free\b")) {

      if (fusion.m_Getdescription().match("\bflags.fixed\b")) {
         flagAccumilate |= ImGuiWindowFlags_NoMove;
      }

      if (fusion.m_Getdescription().match("\bflags.noresize\b")) {
         flagAccumilate |= ImGuiWindowFlags_NoResize;
      }
      if (fusion.m_Getdescription().match("\bflags.static\b")) {
         flagAccumilate |= ImGuiWindowFlags_NoBringToFrontOnFocus;
      }

      if (fusion.m_Getdescription().match("\bflags.transparent\b")) {
         flagAccumilate |= ImGuiWindowFlags_NoBackground;
      }

      if (fusion.m_Getdescription().match({"\bflags.autowh\b", "\bflags.autosize\b"})) {
         flagAccumilate |= ImGuiWindowFlags_AlwaysAutoResize;
      }

      if (fusion.m_Getdescription().match("\bflags.nonav\b")) {
         flagAccumilate |= ImGuiWindowFlags_NoNavFocus;
      }


      if (fusion.m_Getdescription().match({"\bflags.hide\b", "\bflags.hidden\b"})) {
         this->fusion.Metadata.flags.isHidden = true;
      }
   }

   if (fusion.m_Getdescription().match("\bflags.noscroll\b")) {
      flagAccumilate |= ImGuiWindowFlags_NoScrollbar;
   }

   if (fusion.m_Getdescription().match("\bflags.closed\b")) {
      this->localFlags.open = true;
   }
}

noret helper::LinkWindowflags(visuals::Canvas aptr_ canvas, pContainer Container) {

   astr description = canvas->fusion.m_Getdescription();

   decs::MetaInfo::Attachements aptr_ Attachements =
      Container->fusion.m_GetAttachmentPtr();

   if (Attachements->Canvas_count == null) {
      Attachements->Canvas_primary = canvas->fusion.Name;
   }

   if (description.match("\bflags.impostor\b")) {
      canvas->localFlags.Impostor = true;
   }

   Attachements->Canvas_count++;
}
