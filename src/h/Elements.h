#pragma once
#define ELEMENTS_H
#include "coreGui.h"

namespace coregui::visuals {
   class Elements;

}

// hash value for elements, groupo
class cg::visuals::Elements {
 public:
   astr aptr_ Name;
   ulong HashValue;
   astr Owner;
   void run();


   gmVoid GenerateHash(astr visualType);
   Fusion::decs::FusionObject fusion;
};

cg_define_Pointers {
   using pElements = cg::visuals::Elements aptr_;
}
