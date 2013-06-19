
#pragma once

#include <EGL/egl.h>

#include "../rh_window.h"

#ifdef __ANDROID__
	#include <android/log.h>
	#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
	#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
	#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
#else
	#define LOGI(...) ((void)printf(__VA_ARGS__))
	#define LOGW(...) ((void)printf(__VA_ARGS__))
	#define LOGE(...) ((void)printf(__VA_ARGS__))
#endif

struct _rh_display {

  EGLDisplay dpy;
  EGLint version_major;
  EGLint version_minor;

  EGLNativeWindowType nativewindow;
  
#ifdef RH_TARGET_OS_RASPBERRYPI
  EGL_DISPMANX_WINDOW_T nativewindow_obj;
  DISPMANX_ELEMENT_HANDLE_T dispman_element;
  DISPMANX_DISPLAY_HANDLE_T dispman_display;
  DISPMANX_UPDATE_HANDLE_T dispman_update;
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;
  int display_width;
  int display_height;
#endif

};

