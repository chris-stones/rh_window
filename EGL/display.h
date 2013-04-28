
#pragma once

#include <EGL/egl.h>

#include "../rh_window.h"

struct _rh_display {

  EGLDisplay dpy;
  EGLint version_major;
  EGLint version_minor;
  
  
  /*** RPI ***/
  EGL_DISPMANX_WINDOW_T nativewindow;
  DISPMANX_ELEMENT_HANDLE_T dispman_element;
  DISPMANX_DISPLAY_HANDLE_T dispman_display;
  DISPMANX_UPDATE_HANDLE_T dispman_update;
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;
  int display_width;
  int display_height;
  /*** /RPI ***/
};

