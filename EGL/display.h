
#pragma once

#include <EGL/egl.h>

#include "../screen_interface.h"

struct _rh_display {

  EGLDisplay dpy;
  EGLint version_major;
  EGLint version_minor;
};

