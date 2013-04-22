
#include "context.h"
#include "screen.h"
#include "display.h"
#include "window.h"

#include<stdlib.h>

int rh_render_create( rh_render_handle * render, rh_screen_handle screen, int major_version, int minor_version, rh_render_handle share ) {
  
  rh_render_handle out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_render)) )) {
    
    const EGLint attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    
    out->screen = screen;
    
    out->egl_ctx = eglCreateContext(display, screen->config, share ? share->egl_ctx : NULL, attrib_list);
    
    *render = out;
  }
  
  return -1;
}

int rh_bind_render_window(rh_render_handle render, rh_window_handle window) {
  
  EGLSurface drawable = window ? window->surface : EGL_NO_SURFACE;
  EGLContext context  = window ? render->egl_ctx : EGL_NO_CONTEXT; // if window is null, bind a null render ctx.
  
  eglMakeCurrent(render->screen->display->dpy, drawable, drawable, context);
  
  return 0;
}

int rh_render_destroy( rh_render_handle render) {
  
  if(render) {
    
   eglMakeCurrent(render->screen->display->dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
   
   eglDestroyContext(render->screen->display->dpy, render->egl_ctx);
    
   free(render);
  }
}

