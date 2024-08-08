#pragma once
#include "../src/h/coreGui.h"
#define VF_IMPL inline

// i shouldve never written this, this was before i started using c++ 20 and heavily shifted towards templated code, this was an absolute disaster

namespace Fusion {

   namespace decs {
      struct Bounds {
         gmvar< float > upper_left, upper_right, lower_left, lower_right;
      };
      struct Body {
         gmvar< float > width, height, center;
      };
      struct Motion {
         gmvar< float > x, y;
      };
      template < typename t >
      struct Motion_t {
         gmvar< t > x;
         gmvar< t > y;
      };

      namespace classes {
         class Orientation {
          public:
            Orientation()
               : Motion(unsets), Cursors(unsets), relative_Motion(unsets) {};

          public:
            decs::Motion Motion;
            decs::Motion relative_Motion;

            // os mouse and relatives to our instances
            struct mCursors {
               decs::Motion const *os;
               decs::Motion Canvas;
               decs::Motion const *Container;
            };
            mCursors Cursors;
         };

         class Bounds {
          public:
            Bounds() : edges(unsets), body(unsets) {};

          public:
            decs::Bounds edges;
            decs::Body body;
         };
      }   // namespace classes

      struct Flags {
         bool isFixed;
         bool isHidden;
         bool isHovered;
         bool isFamilyMember;
         bool isResizable;
         bool termination;
      };
      struct dcs {
         astr description;
      };

      struct MetaInfo {
         MetaInfo() : Attached(unsets), flags(unsets) {};

         astr objectType;
         astr visual;
         Flags flags;

         struct Attachements {
            astr Canvas_primary;
            ulong Canvas_count;

            bool callbackfn_Render;
         };
         Attachements Attached;
      };

      class FusionObject {
       public:
         astr Family, Name;
         MetaInfo Metadata;
         dcs desc;

         classes::Orientation orient;
         classes::Bounds bounds;

         gmVoid m_initDescription (const astr ref_ desc, astr objectType);

         gmVoid m_mapGenerics ();

         astr m_Getdescription ();

         decs::MetaInfo m_GetMetaData ();

         decs::MetaInfo::Attachements aptr_ m_GetAttachmentPtr ();

         decs::Body m_GetBodyMass ();

         decs::Motion m_GetMotion ();

         decs::Motion m_GetRelativeMotion ();

         decs::Motion m_GetCursorOS ();

         decs::Motion &m_GetCursorCanvas ();

         decs::Motion m_GetCursorContainer ();

         gmVoid m_SetMotion (decs::Motion NewMotion);

         gmVoid m_SetRelativeMotion (decs::Motion NewRelativeMotion);

         gmVoid parse_Bounds (astr desc);
         gmVoid parse_Position (astr desc);
      };

   }   // namespace decs

   namespace Parse {
      gmVoid Primitive_Flags (astr desc_flags, decs::FusionObject aptr_ VisualObject_flags);
      noret Positions (astr desc, decs::FusionObject ref_ fusion);
      noret Bounds (astr desc, decs::FusionObject ref_ fusion);
      noret Bounds (astr &desc, Fusion::decs::Body ref_ body);
   }   // namespace Parse

   using pFusion = Fusion::decs::FusionObject aptr_;

}   // namespace Fusion

namespace {

   using namespace Fusion;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.Fusion helpers
////
////
////
////

VF_IMPL gmVoid Fusion::decs::FusionObject::parse_Bounds(astr desc) {
   Parse::Bounds(desc, *this);
}

VF_IMPL gmVoid Fusion::decs::FusionObject::parse_Position(astr desc) {
   Parse::Positions(desc, *this);
}

namespace {}

VF_IMPL decs::MetaInfo Fusion::decs::FusionObject::m_GetMetaData() {
   return Metadata;
}

VF_IMPL decs::MetaInfo::Attachements aptr_
decs::FusionObject::m_GetAttachmentPtr() {
   return ref_ Metadata.Attached;
}

VF_IMPL decs::Motion Fusion::decs::FusionObject::m_GetCursorOS() {
   return deref orient.Cursors.os;
}


VF_IMPL decs::Motion Fusion::decs::FusionObject::m_GetCursorContainer() {
   return deref orient.Cursors.Container;
}

VF_IMPL decs::Motion Fusion::decs::FusionObject::m_GetMotion() {
   return orient.Motion;
}

VF_IMPL decs::Motion Fusion::decs::FusionObject::m_GetRelativeMotion() {
   return orient.relative_Motion;
}

VF_IMPL decs::Body Fusion::decs::FusionObject::m_GetBodyMass() {
   return bounds.body;
}

VF_IMPL gmVoid Fusion::decs::FusionObject::m_SetMotion(decs::Motion NewMotion) {
   orient.Motion = NewMotion;
}

VF_IMPL gmVoid Fusion::decs::FusionObject::m_SetRelativeMotion(
   decs::Motion NewRelativeMotion
) {
   orient.relative_Motion = NewRelativeMotion;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.Parsing algorithm and initilization
////
////  please #define coregui_impl
////
////

VF_IMPL astr Fusion::decs::FusionObject::m_Getdescription() {
   return desc.description;
}

VF_IMPL gmVoid Fusion::decs::FusionObject::m_mapGenerics() {
   Name = desc.description.ExtractWord("name.\a");
   Metadata.visual = desc.description.ExtractWord("visual.\a");

#if defined(coregui_impl)

   this->orient.Cursors.os = Backend::_getosCursor< decs::Motion aptr_ >();

#endif
}

VF_IMPL gmVoid
Fusion::decs::FusionObject::m_initDescription(const astr ref_ desc, astr objectType) {
   this->desc.description = desc;
   Metadata.objectType = objectType;
}

// will forget about these flags within weeks i bet.
VF_IMPL gmVoid
Fusion::Parse::Primitive_Flags(astr desc_flags, Fusion::decs::FusionObject aptr_ vo_Flags) {
   regex2 r;
   auto Flags = &vo_Flags->Metadata.flags;

   Flags->isFixed = r.filterMatch(desc_flags, "flags.fixed");

   Flags->isResizable = r.filterMatch(desc_flags, "flags.resizeable");

   Flags->isHidden = r.filterMatch(desc_flags, "flags.hidden");

   return;
}

VF_IMPL noret
Fusion::Parse::Positions(astr desc, Fusion::decs::FusionObject ref_ fusion) {

   fusion.orient.Motion.x = desc.ExtractWord("\bx.\a");
   fusion.orient.Motion.y = desc.ExtractWord("\by.\a");

   return;
}

VF_IMPL noret Fusion::Parse::Bounds(astr desc, Fusion::decs::FusionObject ref_ fusion) {

   Bounds(desc, fusion.bounds.body);

   return;
}

VF_IMPL noret Fusion::Parse::Bounds(astr &desc, Fusion::decs::Body ref_ body) {

   body.width = desc.ExtractWord("\bwidth.\a");
   if (body.width == 0)
      body.width = desc.ExtractWord("\bw.\a");

   body.height = desc.ExtractWord("\bheight.\a");
   if (body.height == 0)
      body.height = desc.ExtractWord("\bh.\a");

   return;
}
