# Guimaster Library

*A lightweight graphics library, module, and framework. Semi-open source.*

## Cool Features
- **Custom scripting language for C++**
- **Extensive WINAPI configurations** for cool overlays and modern UIs
- **High-level UI design**
- **Minimal bloat** with no dependency on GLFW
- **Runtime scripting editor**
- **Header-only implementation**

 

```cpp
     // INTERPRETER LANGUAGE EXAMPLE
 
      gmElements gme;

      gme.designateFamily(" y.10 top.35", {
         "v.checkbox name='SomeCheckBox'", "v.input input.size='500' name='SomeInput'" 
      });
 

     if (gm.awaitEnabled("SomeCheckBox"))
           .....

  astr widget_input_buffer = gm.awaitInput("SomeInput");
  widget_input_buffer.print();

  // or here youd like to run through a group of buttons and wait for anyone to be interacted with ( requires visuals to be registered with a group )
  if (astr pressed_Button_name = gm.any_pressed_in_group("store"))  
           .....     
   
```                                   
                                        
                                        
                                        
                                        
                                        
                  
                                                                   
> 

![screenshot](lang.png)   
