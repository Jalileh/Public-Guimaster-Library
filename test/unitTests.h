
#ifdef snippets

noret sample () {


   gmElements gm;

   gm = "visual.text name.xck font.14  <text> COPECHEATS </text>";
}
noret sample3 () {


   gmElements gm;

   gm = "visual.text name.Dick <text> You muts Coomfirm </text>";

   gm = "visual.button name.vagina";
}
noret sample4 () {


   gmElements gm;


   gm = gm.designateFamily(" name.s top.50 gap.1 padx.1 x.100 y.200 font.3");
   gm = "visual.input name.Username ";
}
noret sample2 () {
   gmElements gm;

   gm = gm.designateFamily("top.50 gap.1 x.1 font.3");
}

void xmain () {
   gmm::gmapi popsicle;


   popsicle.load();


   astr winDesc4 =
      "name.builder-Engine  visual.empty  width.1000 height.800   ";


   popsicle.designContainer(winDesc4);
   popsicle.designCanvas("  name.5 width.1000  font.1 flags.notab flags.fixed flags.static  owner.builder-Engine", sample4);
   popsicle.designCanvas("  flags.impostor height.800 font.1  flags.noresize flags.fixed flags.static x.0 y.0 name.penis width.1000  flags.notab owner.builder-Engine", sample);


   popsicle.designCanvas("  name.3 width.1000  font.1 flags.notab  owner.builder-Engine", sample2);
   popsicle.designCanvas("  name.4 width.1000  font.1 flags.notab owner.builder-Engine", sample3);


   volatile int a = 0;
   while (a == 0) {

      popsicle.run("builder-Engine");
   }
}


// second snippet


#endif

namespace utest {
   void libmain_guimaster ();

   void dixi (int b, int a, int c);

}   // namespace utest
