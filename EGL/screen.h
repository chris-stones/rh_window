
#pragma once

#include "../screen_interface.h"

struct _rh_screen {
  
  rh_display_handle display;
  EGLint format;
  EGLConfig config;
  
  EGLNativeWindowType native_window;
};


