
#pragma once

#include "../rh_window.h"

#include<EGL/egl.h>

struct _rh_screen {
  
  rh_display_handle display;
  EGLint format;
  EGLConfig config;
  
//  EGLNativeWindowType native_window;
};


