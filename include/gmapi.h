#pragma once
#define GMAPI_H

#include "guimaster.h"

static pguiMaster __gmloadinit ();


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.gmapi interface
////
////
////
////

#include "extended_gmapi\interface.h"

GM_IMPL noret gma::gmapi::load() {
   pguiMaster receive_coregui = unset;

   if (gmcg::MiddleWare_CG.coreguiLib == nullptr) {

      receive_coregui = __gmloadinit();
      if (!receive_coregui)
         cle_private("LOAD FAILURE, PROBABLY NET RELATED", "GMAPI:CG LOAD FAILURE");

      gmc::globals::MiddleWare_CG.SetCoreGuiPointer(receive_coregui);

      gmGL::gl = receive_coregui->Misc.glfptr;
   }
   else {
      cle_private("GMAPI HAS ALREADY BEEN LOADED", "GMAPI ATTEMPTED MULTIPLE LOAD");
   }
}


#if GMAPI_BUILDER == true
#   include "extended_gmapi\gmbuilder.h"

#else
#   define gmBuilderHere(name)
#endif


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////
////  @s.load cg dll
////
////
////
////

static pguiMaster
__gmloadinit () {


#if defined(GMAPI_LIB)
   return cg::getGuiMaster();

#elif PJC_CONSUMERBUILD == false && defined(GMAPI_DLL)


#   if !defined(PJC_BUILD_DEBUG) and !defined(PJC_BUILD_RELEASE)
   pjc_assert(0, "OLD YCMAKE VERSION FOR GMPAI.");
#   endif

   try {
      return loader::local::exportDllFn< pguiMaster >(
#   if pjc_build_release or GMAPI_FORCE_RELEASE == true
         "REDACTED_PUBLIC_SOURCE",
#   elif PJC_BUILD_DEBUG
         "REDACTED_PUBLIC_SOURCE",
#   endif
         "CG",
         true
      );

   } catch (astr e) {
      // Force an exception to be thrown even if the function call doesn't throw
      // one
      e.sprint("load gm failed locally");
      return nullptr;
   }

#elif GMAPI_SHADOWNET == true
   loader::CoreObject loader(loader::autoconf::COMPONENT, false);
   auto CG_initFn = loader.loadComponent(L"guimaster", "CG");
   if (!CG_initFn)
      return 0;
   return loader.initComponentbyFnCall< pguiMaster >(CG_initFn);


#else
   pjc_assert(0, "GMAPI ERROR DEFINE GMAPI_PLATFORM   : { GMAPI_LIB | "
                 " GMAPI_DLL  }");
   return 0;

#endif
}
