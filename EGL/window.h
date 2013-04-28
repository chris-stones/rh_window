
#pragma once

#include <EGL/egl.h>

#include "../rh_window.h"

typedef enum {
  
  _RH_WINDOW_FULLSCREEN  	= (1<<0),
  
} _rh_window_attr_flags_enum;

struct _rh_window_attr {
  
  int x;
  int y;
  int w;
  int h;
  int flags;
};

struct _rh_window {
  
  struct _rh_window_attr attr;
  
  rh_screen_handle screen;
  
  EGLSurface surface;
};

