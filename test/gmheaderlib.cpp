
#include "api/epworker.h"
#include "include/gmapi.h"


noret sample (){


   gmBuilderHere("sample1")

} noret sample3(){


   gmBuilderHere("sample3")

} noret sample4(){


   gmBuilderHere("sample4")


} noret sample2() {


   gmBuilderHere("sample2")
}

auto ovfn () {
   gmGL hey;

   hey.DrawByMode(gmGL::mode::line_linear, [&] {
      gmVertex f;


    
      auto x = 1.0f;
      auto y = 0.5f;

      f.VertexV2(
         0, 0,
         1, 1


      );
   });
}
void gmfn () {
   gma::gmapi popsicle;


   popsicle.load();

   cd("testing with gl also ", "gmGL");

   astr winDesc4 =
      "name.builder-Engine  visual.empty  width.1000 height.800   ";


 
   popsicle.designContainer(winDesc4);

   popsicle.designCanvas("  name.Bex width.1000  font.1 flags.notab   flags.static  owner.builder-Engine", sample4);

   //  popsicle.designCanvas("  flags.impostor height.800 font.1  flags.noresize  flags.static x.0 y.0 name.penis width.1000  flags.notab owner.builder-Engine", sample);

   //  popsicle.designCanvas("  name.Rex width.1000  font.1 flags.notab  owner.builder-Engine", sample2);
   //  popsicle.designCanvas("  name.vex width.1000  font.1 flags.notab owner.builder-Engine", sample3);


   volatile int a = 0;
   while (a == 0) {

      popsicle.run("all");
   }
}


auto entry () {

   gmfn();
}


ep_winapp("rouge", entry, "con");
