
#pragma once

#include "display.h"

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>

struct _rh_screen {
  
  rh_display_handle display;
  
  GLXFBConfig 		 *glxFBConfig;
  int			 glxFBConfigSize;
  XVisualInfo 		 *xVisualInfo;
  XRRScreenConfiguration *screenConfig;
  XRRScreenResources	 *res;
};

