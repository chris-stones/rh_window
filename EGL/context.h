
#pragma once

#include <EGL/egl.h>

#include "../rh_window.h"

struct _rh_render {
  
  rh_screen_handle screen;
  
  EGLContext egl_ctx;
};

