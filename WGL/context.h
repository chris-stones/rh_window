
#pragma once

#include "display.h"
#include "screen.h"

#include "../rh_window.h"

#include<windows.h>

struct _rh_render {
  
  rh_window_handle window;
 
  HDC dc;
  HGLRC rc;
};

