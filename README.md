# Public-Guimaster-Library
A library module and a framework that I wrote to challenge my C++ knowledge last year and to try my attempts at creating a language-
and to rewrite my graphics library.     


The issues it does solve is lessen C++ code involved with drawing a button or an input box for example, 
everything is interpreted and memory is allocated for these individual elements in case they are interactive and need to be handled when they fire,
they are fetched through the gmapi interface e.g

```cpp

 
      gmElements gme;

      gme.designateFamily(" y.10 top.35", {
         "v.checkbox name='SomeCheckBox'", "v.input input.size='500' name='SomeInput'", ...."
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
