
 
#ifdef pjc_build_exe

#   define GMAPI_LIB
#   include "ecl.h"
 #include "../include/guimaster.h"
#   include "unitTests.h"
#   include <api/epworker.h>

noret sample () {

 
}
noret sample3 () {

   
}
noret sample4 () {
    
 

 
                                                                     
}
noret sample2 () {
  
}

#   include "gl/GL.h"
noret samplex () {
   glBegin(GL_LINES);
   glVertex2f(0.0f, 90.0f);   //??? draws a vertical line upwards...
   glVertex2f(0.0f, 0.0f);    //???


   glEnd();
}
 
void xmain () {
  
 
 
}

ep_winapp("guimaster", xmain, " console con +log  tkey.'  09")
#endif
