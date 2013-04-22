
#pragma once

#include <EGL/egl.h>

#include "../screen_interface.h"

struct _rh_render {
  
  rh_screen_handle screen;
  
  EGLContext egl_ctx;
};

