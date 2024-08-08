
#include "../src/imgui/imgui.h"
#define CANVAS_H
#include "coreGui.h"


class ImageHandler {
 public:
   void load (astr Path);

   void render ();
};


using CallbackRenderFn = void (*)();

typedef struct _Canvas_IMGUI_Dimension_Coordinates {
   Fusion::decs::Motion object_Position;
   // x.0-y.0 being nearest to the top left corner of the  OS - window
   Fusion::decs::Motion *Cursor;
} _Canvas_DIMENSION_POS;


class visuals::Canvas {
 protected:
   _Canvas_IMGUI_Dimension_Coordinates encapsulated_imgui_coordinates;

 public:
   struct Flags {
      bool Impostor;
      bool HasChildWindows;
      bool is_ChildWindow;
      bool fusionDataSet;
      bool open;
      bool init_Positioned;
   };

   int fontWidth = 0;

   Flags localFlags = unsets;
   astr Owner;

   Fusion::decs::FusionObject fusion;
   CallbackRenderFn callBackRenderFn;
   ImGuiWindowFlags flagAccumilate;

 public:
   void init_Metadata ();
   void ParseFlags ();

   void ifany_callChildWindows ();
   void runInstanceEntry ();
   void DrawInstances ();

   void setPosition (cg::Fusion::decs::Motion Pos);
   void updateCalls ();
   auto m_GetCursorCanvas () {
      return deref this->m_GetDimensionCoords().Cursor;
   }

 public:
   class helper;
   _Canvas_DIMENSION_POS &m_GetDimensionCoords ();

 private:
   noret m_UpdateDimensionCoords ();

 private:
   void imgui_Begin ();
   void imgui_End ();
};

class visuals::Canvas::helper {
 public:
   static noret LinkWindowflags (visuals::Canvas aptr_ CanvasObject, pContainer Container);
};

cg_define_Pointers {
   using pCanvas = visuals::Canvas aptr_;
}


using CanvasCB = void;
