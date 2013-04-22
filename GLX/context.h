
#pragma once

#include <GL/glx.h>
#include <GL/gl.h>

#include "display.h"
#include "screen.h"

#include "../rh_window.h"

struct _rh_render {
  
  rh_screen_handle screen;
  
  GLXContext glx_ctx;
};

