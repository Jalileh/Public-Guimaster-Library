#pragma once
#define ELEMENTS_H
#include "h\coreGui.h"
#include <GL/GL.h>
struct OpenGl_fptr {

   using fn_begin = noret (*)(GLenum mode);

   using fn_clear = noret (*)(GLenum mode);

   using fn_gl_end = noret (*)();

   using fn_vertex2f = noret (*)(GLfloat x, GLfloat y);
   using fn_vertex3f = noret (*)(GLfloat x, GLfloat y, GLfloat z);
   using fn_vertex4f = noret (*)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);


   using fn_colorx3f = noret (*)(GLfloat red, GLfloat green, GLfloat blue);

   using fn_loadident = void (*)(void);
   using fn_glmatrixmode = void (*)(GLenum mode);
   using fn_glViewPort = void (*)(GLint x, GLint y, GLsizei width, GLsizei height);
   using fn_translatef = void (*)(GLfloat x, GLfloat y, GLfloat z);
   using fn_glortho = void (*)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);

   fn_translatef translatef;
   fn_loadident loadIdentity;
   fn_glmatrixmode glMatrixMode;
   fn_glViewPort glViewPort;
   fn_glortho glOrtho;

   fn_begin glBegin;

   fn_gl_end glEnd;

   fn_clear glClear;

   fn_colorx3f glColor3f;

   fn_vertex2f Vertex2;

   fn_vertex3f Vertex3;

   fn_vertex4f Vertex4;
};

auto inline check() {
}

struct imgui_fptr {
   void (*Text)(const char *fmt, ...);

   bool (*Button)(const char *label, const ImVec2 &size);

   bool (*SmallButton)(const char *label);

   bool (*InvisibleButton)(const char *str_id, const ImVec2 &size, ImGuiButtonFlags flags);

   bool (*ArrowButton)(const char *str_id, ImGuiDir dir);

   bool (*Checkbox)(const char *label, bool *v);

   bool (*CheckboxFlags)(const char *label, int *flags, int flags_value);

   bool (*RadioButton)(const char *label, bool active);

   void (*ProgressBar)(float fraction, const ImVec2 &size_arg, const char *overlay);

   void (*Bullet)();

   bool (*InputText)(const char *label, char *buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void *user_data);

   bool (*InputTextMultiline)(const char *label, char *buf, size_t buf_size, const ImVec2 &size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void *user_data);

   bool (*InputTextWithHint)(const char *label, const char *hint, char *buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void *user_data);

   bool (*InputFloat)(const char *label, float *v, float step, float step_fast, const char *format, ImGuiInputTextFlags flags);

   bool (*InputFloat2)(const char *label, float v[2], const char *format, ImGuiInputTextFlags flags);

   bool (*InputFloat3)(const char *label, float v[3], const char *format, ImGuiInputTextFlags flags);

   bool (*InputFloat4)(const char *label, float v[4], const char *format, ImGuiInputTextFlags flags);

   bool (*InputInt)(const char *label, int *v, int step, int step_fast, ImGuiInputTextFlags flags);

   bool (*InputInt2)(const char *label, int v[2], ImGuiInputTextFlags flags);

   bool (*InputInt3)(const char *label, int v[3], ImGuiInputTextFlags flags);

   bool (*InputInt4)(const char *label, int v[4], ImGuiInputTextFlags flags);

   bool (*InputDouble)(const char *label, double *v, double step, double step_fast, const char *format, ImGuiInputTextFlags flags);

   bool (*InputScalar)(const char *label, ImGuiDataType data_type, void *p_data, const void *p_step, const void *p_step_fast, const char *format, ImGuiInputTextFlags flags);

   bool (*InputScalarN)(const char *label, ImGuiDataType data_type, void *p_data, int components, const void *p_step, const void *p_step_fast, const char *format, ImGuiInputTextFlags flags);

   // Function pointer for ColorEdit3 function
   bool (*ColorEdit3)(const char *label, float col[3], ImGuiColorEditFlags flags);

   // Function pointer for ColorEdit4 function
   bool (*ColorEdit4)(const char *label, float col[4], ImGuiColorEditFlags flags);

   // Function pointer for ColorPicker3 function
   bool (*ColorPicker3)(const char *label, float col[3], ImGuiColorEditFlags flags);

   // Function pointer for ColorPicker4 function
   bool (*ColorPicker4)(const char *label, float col[4], ImGuiColorEditFlags flags, const float *ref_col);

   // Function pointer for ColorButton function
   bool (*ColorButton)(const char *desc_id, const ImVec4 &col, ImGuiColorEditFlags flags, const ImVec2 &size);

   // Function pointer for SetColorEditOptions function
   void (*SetColorEditOptions)(ImGuiColorEditFlags flags);

   // Function pointer for TreeNode function
   bool (*TreeNode)(const char *label);

   // Function pointer for TreeNode with string ID function
   bool (*TreeNodeStrID)(const char *str_id, const char *fmt, ...);

   // Function pointer for TreeNode with pointer ID function
   bool (*TreeNodePtrID)(const void *ptr_id, const char *fmt, ...);

   // Function pointer for TreeNodeV function
   bool (*TreeNodeV)(const char *str_id, const char *fmt, va_list args);

   // Function pointer for TreeNodeV with pointer ID function
   bool (*TreeNodePtrIDV)(const void *ptr_id, const char *fmt, va_list args);

   // Function pointer for TreeNodeEx function
   bool (*TreeNodeEx)(const char *label, ImGuiTreeNodeFlags flags);

   // Function pointer for TreeNodeEx with string ID function
   bool (*TreeNodeExStrID)(const char *str_id, ImGuiTreeNodeFlags flags, const char *fmt, ...);

   // Function pointer for TreeNodeEx with pointer ID function
   bool (*TreeNodeExPtrID)(const void *ptr_id, ImGuiTreeNodeFlags flags, const char *fmt, ...);

   // Function pointer for TreeNodeExV function
   bool (*TreeNodeExV)(const char *str_id, ImGuiTreeNodeFlags flags, const char *fmt, va_list args);

   // Function pointer for TreeNodeExV with pointer ID function
   bool (*TreeNodeExPtrIDV)(const void *ptr_id, ImGuiTreeNodeFlags flags, const char *fmt, va_list args);

   // Function pointer for TreePush function with string ID
   void (*TreePushStrID)(const char *str_id);

   // Function pointer for TreePush function with pointer ID
   void (*TreePushPtrID)(const void *ptr_id);

   // Function pointer for TreePop function
   void (*TreePop)();

   // Function pointer for GetTreeNodeToLabelSpacing function
   float (*GetTreeNodeToLabelSpacing)();

   // Function pointer for CollapsingHeader function
   bool (*CollapsingHeader)(const char *label, ImGuiTreeNodeFlags flags);

   // Function pointer for CollapsingHeader with visibility control function
   bool (*CollapsingHeaderVisible)(const char *label, bool *p_visible, ImGuiTreeNodeFlags flags);

   // Function pointer for SetNextItemOpen function
   void (*SetNextItemOpen)(bool is_open, ImGuiCond cond);

   // Function pointer for Selectable function without selection state pointer
   bool (*SelectableNoPtr)(const char *label, bool selected, ImGuiSelectableFlags flags, const ImVec2 &size);

   // Function pointer for Selectable function with selection state pointer
   bool (*SelectablePtr)(const char *label, bool *p_selected, ImGuiSelectableFlags flags, const ImVec2 &size);

   // Function pointer for BeginListBox function
   bool (*BeginListBox)(const char *label, const ImVec2 &size);

   // Function pointer for EndListBox function
   void (*EndListBox)();

   // Function pointer for ListBox function with array of items
   bool (*ListBoxArray)(const char *label, int *current_item, const char *const items[], int items_count, int height_in_items);

   // Function pointer for ListBox function with getter function
   bool (*ListBoxGetter)(const char *label, int *current_item, const char *(*getter)(void *user_data, int idx), void *user_data, int items_count, int height_in_items);

   // Function pointer for PlotLines function with values array
   void (*PlotLinesArray)(const char *label, const float *values, int values_count, int values_offset, const char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size, int stride);

   // Function pointer for PlotLines function with values getter function
   void (*PlotLinesGetter)(const char *label, float (*values_getter)(void *data, int idx), void *data, int values_count, int values_offset, const char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size);

   // Function pointer for PlotHistogram function with values array
   void (*PlotHistogramArray)(const char *label, const float *values, int values_count, int values_offset, const char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size, int stride);

   // Function pointer for PlotHistogram function with values getter function
   void (*PlotHistogramGetter)(const char *label, float (*values_getter)(void *data, int idx), void *data, int values_count, int values_offset, const char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size);

   // Function pointer for Value function with bool
   void (*ValueBool)(const char *prefix, bool b);

   // Function pointer for Value function with int
   void (*ValueInt)(const char *prefix, int v);

   // Function pointer for Value function with unsigned int
   void (*ValueUInt)(const char *prefix, unsigned int v);

   // Function pointer for Value function with float
   void (*ValueFloat)(const char *prefix, float v, const char *float_format);

   void (*PushStyleVar)(ImGuiStyleVar idx, float val);
   void (*PushStyleColor)(ImGuiCol idx, const ImVec4 &col);

   bool (*SliderFloat)(const char *label, float *v, float v_min, float v_max, const char *format, ImGuiSliderFlags flags);

   bool (*SliderFloat2)(const char *label, float v[2], float v_min, float v_max, const char *format, ImGuiSliderFlags flags);

   void (*SetNextItemWidth)(float item_width);

   using winsize = ImVec2 (*)();
   using winpos = ImVec2 (*)();

   winsize GetWindowSize;
   winpos GetWindowPos;

   void (*SetCursorPos)(const ImVec2 &local_pos);
   ImVec2 (*GetCursorPos)();
};

#define coregui_impl
#ifdef coregui_impl

auto inline init_GLFptr() {

   OpenGl_fptr aptr_ gl_funcs = new OpenGl_fptr;

   deref gl_funcs = unsets;

   // Set gl  function pointers

   {

      fptr(gl_funcs->glBegin, glBegin);

      fptr(gl_funcs->glEnd, glEnd);

      fptr(gl_funcs->glColor3f, glColor3f);

      fptr(gl_funcs->Vertex2, glVertex2f);

      fptr(gl_funcs->Vertex3, glVertex3f);

      fptr(gl_funcs->Vertex4, glVertex4f);

      fptr(gl_funcs->glMatrixMode, glMatrixMode);
      fptr(gl_funcs->translatef, glTranslatef);
      fptr(gl_funcs->loadIdentity, glLoadIdentity);
      fptr(gl_funcs->glViewPort, glViewport);
      fptr(gl_funcs->glOrtho, glOrtho);
      fptr(gl_funcs->glClear, glClear);
   }
   return gl_funcs;
}
auto inline init_ImFptr() {

   imgui_fptr aptr_ imgui_funcs = new imgui_fptr;

   deref imgui_funcs = unsets;


   // Set imgui function pointers

   fptr(imgui_funcs->Text, ImGui::Text);
   fptr(imgui_funcs->Button, ImGui::Button);
   fptr(imgui_funcs->SmallButton, ImGui::SmallButton);
   fptr(imgui_funcs->InvisibleButton, ImGui::InvisibleButton);
   fptr(imgui_funcs->ArrowButton, ImGui::ArrowButton);
   fptr(imgui_funcs->Checkbox, ImGui::Checkbox);
   fptr(imgui_funcs->CheckboxFlags, ImGui::CheckboxFlags);
   fptr(imgui_funcs->RadioButton, ImGui::RadioButton);
   fptr(imgui_funcs->ProgressBar, ImGui::ProgressBar);
   fptr(imgui_funcs->Bullet, ImGui::Bullet);
   fptr(imgui_funcs->InputText, ImGui::InputText);
   fptr(imgui_funcs->InputTextMultiline, ImGui::InputTextMultiline);
   fptr(imgui_funcs->InputTextWithHint, ImGui::InputTextWithHint);
   fptr(imgui_funcs->InputFloat, ImGui::InputFloat);
   fptr(imgui_funcs->InputFloat2, ImGui::InputFloat2);
   fptr(imgui_funcs->InputFloat3, ImGui::InputFloat3);
   fptr(imgui_funcs->InputFloat4, ImGui::InputFloat4);
   fptr(imgui_funcs->InputInt, ImGui::InputInt);
   fptr(imgui_funcs->InputInt2, ImGui::InputInt2);
   fptr(imgui_funcs->InputInt3, ImGui::InputInt3);
   fptr(imgui_funcs->InputInt4, ImGui::InputInt4);
   fptr(imgui_funcs->InputDouble, ImGui::InputDouble);
   fptr(imgui_funcs->InputScalar, ImGui::InputScalar);
   fptr(imgui_funcs->InputScalarN, ImGui::InputScalarN);
   fptr(imgui_funcs->ColorEdit3, ImGui::ColorEdit3);
   fptr(imgui_funcs->ColorEdit4, ImGui::ColorEdit4);
   fptr(imgui_funcs->ColorPicker3, ImGui::ColorPicker3);
   fptr(imgui_funcs->ColorPicker4, ImGui::ColorPicker4);
   fptr(imgui_funcs->ColorButton, ImGui::ColorButton);
   fptr(imgui_funcs->SetColorEditOptions, ImGui::SetColorEditOptions);
   fptr(imgui_funcs->TreeNode, ImGui::TreeNode);
   fptr(imgui_funcs->TreeNodeStrID, ImGui::TreeNode);
   fptr(imgui_funcs->TreeNodePtrID, ImGui::TreeNode);
   fptr(imgui_funcs->TreeNodeV, ImGui::TreeNodeV);
   fptr(imgui_funcs->TreeNodePtrIDV, ImGui::TreeNodeV);
   fptr(imgui_funcs->TreeNodeEx, ImGui::TreeNodeEx);
   fptr(imgui_funcs->TreeNodeExStrID, ImGui::TreeNodeEx);
   fptr(imgui_funcs->TreeNodeExPtrID, ImGui::TreeNodeEx);
   fptr(imgui_funcs->TreeNodeExV, ImGui::TreeNodeExV);
   fptr(imgui_funcs->TreeNodeExPtrIDV, ImGui::TreeNodeExV);
   fptr(imgui_funcs->TreePushStrID, ImGui::TreePush);
   fptr(imgui_funcs->TreePushPtrID, ImGui::TreePush);
   fptr(imgui_funcs->TreePop, ImGui::TreePop);
   fptr(imgui_funcs->GetTreeNodeToLabelSpacing, ImGui::GetTreeNodeToLabelSpacing);
   fptr(imgui_funcs->CollapsingHeader, ImGui::CollapsingHeader);
   fptr(imgui_funcs->CollapsingHeaderVisible, ImGui::CollapsingHeader);
   fptr(imgui_funcs->SetNextItemOpen, ImGui::SetNextItemOpen);
   fptr(imgui_funcs->SelectableNoPtr, ImGui::Selectable);
   fptr(imgui_funcs->SelectablePtr, ImGui::Selectable);
   fptr(imgui_funcs->BeginListBox, ImGui::BeginListBox);
   fptr(imgui_funcs->EndListBox, ImGui::EndListBox);
   fptr(imgui_funcs->ListBoxArray, ImGui::ListBox);
   fptr(imgui_funcs->ListBoxGetter, ImGui::ListBox);
   fptr(imgui_funcs->PlotLinesArray, ImGui::PlotLines);
   fptr(imgui_funcs->PlotLinesGetter, ImGui::PlotLines);
   fptr(imgui_funcs->PlotHistogramArray, ImGui::PlotHistogram);
   fptr(imgui_funcs->PlotHistogramGetter, ImGui::PlotHistogram);
   fptr(imgui_funcs->ValueBool, ImGui::Value);
   fptr(imgui_funcs->ValueInt, ImGui::Value);
   fptr(imgui_funcs->ValueUInt, ImGui::Value);
   fptr(imgui_funcs->ValueFloat, ImGui::Value);
   fptr(imgui_funcs->PushStyleVar, ImGui::PushStyleVar);
   fptr(imgui_funcs->PushStyleColor, ImGui::PushStyleColor);

   fptr(imgui_funcs->SliderFloat, ImGui::SliderFloat);
   fptr(imgui_funcs->SliderFloat2, ImGui::SliderFloat2);

   fptr(imgui_funcs->SetCursorPos, ImGui::SetCursorPos);
   fptr(imgui_funcs->GetCursorPos, ImGui::GetCursorPos);
   fptr(imgui_funcs->SetNextItemWidth, ImGui::SetNextItemWidth);

   fptr(imgui_funcs->GetWindowPos, ImGui::GetWindowPos);
   fptr(imgui_funcs->GetWindowSize, ImGui::GetWindowSize);

   return imgui_funcs;
}

#endif
