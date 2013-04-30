
#include "screen.h"
#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef RH_TARGET_ANDROID
  struct ANativeWindow;
  typedef struct ANativeWindow ANativeWindow;
  int32_t ANativeWindow_setBuffersGeometry(ANativeWindow* window, int32_t width, int32_t height, int32_t format);
#endif /*** RH_TARGET_ANDROID **/

static const EGLint * _get_egl_attribs() {

  static const EGLint attribs[] = {
	  EGL_RENDERABLE_TYPE, 	EGL_OPENGL_ES2_BIT,
	  EGL_SURFACE_TYPE, 	EGL_WINDOW_BIT,
	  EGL_BLUE_SIZE, 	8,
	  EGL_GREEN_SIZE, 	8,
	  EGL_RED_SIZE, 	8,
	  EGL_ALPHA_SIZE,	8, // Strange render bug on raspberry pi if this isnt requested!?
	  EGL_NONE
  };
  return attribs;
}

static int _rh_screen_create( rh_screen_handle * scr, int screen_index, rh_display_handle display ) {
  
  rh_screen_handle out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_screen)) )) {
    
    EGLint numConfigs;
    
    out->display = display;
    
    eglChooseConfig( display->dpy, _get_egl_attribs(), &out->config, 1, &numConfigs );
    
    if(numConfigs > 0) {
      EGLint bufSize,r,g,b,a,z,s = 0;

      eglGetConfigAttrib(display->dpy,&out->config,EGL_BUFFER_SIZE,&bufSize);

      eglGetConfigAttrib(display->dpy,out->config,EGL_RED_SIZE,&r);
      eglGetConfigAttrib(display->dpy,out->config,EGL_GREEN_SIZE,&g);
      eglGetConfigAttrib(display->dpy,out->config,EGL_BLUE_SIZE,&b);
      eglGetConfigAttrib(display->dpy,out->config,EGL_ALPHA_SIZE,&a);

      eglGetConfigAttrib(display->dpy,out->config,EGL_DEPTH_SIZE,&z);
      eglGetConfigAttrib(display->dpy,out->config,EGL_STENCIL_SIZE,&s);

      printf("%d Configs found:\n\tFrame buffer(%d) RGBA(%d %d %d %d)\n\tZBuffer(%d) Z(%d) S(%d)\n\n",numConfigs,bufSize,r,g,b,a,z+s,z,s);
    }
    
    eglGetConfigAttrib(display->dpy, out->config, EGL_NATIVE_VISUAL_ID, &out->format);
    
    *scr = out;
  }
  
  return -1;
}

static int _rh_screen_create_default( rh_screen_handle * scr, rh_display_handle dpy ) {
  
  return _rh_screen_create(scr, 0, dpy);
}

int rh_screen_create( rh_screen_handle * scr, int screen_index, rh_display_handle dpy, ... ) {
  
  int e;
  va_list va;
  va_start(va,dpy);
  
  if( (e = _rh_screen_create( scr, screen_index, dpy ) ) == 0) {
    
#ifdef RH_TARGET_ANDROID
    (*scr)->android_window = va_arg(va, (struct ANativeWindow *) );
    ANativeWindow_setBuffersGeometry((*scr)->native_window, 0, 0, (*scr)->format);
#endif
  }
   
  va_end(va);
  
  return e;
}

int rh_screen_create_default( rh_screen_handle * scr, rh_display_handle dpy, ... ) {
  
  int e;
  va_list va;
  va_start(va,dpy);
  
  if( (e = _rh_screen_create_default( scr, dpy ) ) == 0) {
    
#ifdef RH_TARGET_ANDROID
    (*scr)->android_window = va_arg(va, (struct ANativeWindow *) );
    ANativeWindow_setBuffersGeometry((*scr)->android_window, 0, 0, format);
#endif
  }
   
  va_end(va);
  
  return e;
}

int rh_screen_destroy( rh_screen_handle scr ) {
 
  if(scr) {
   
    free(scr);
  }
  
  return 0;
}

