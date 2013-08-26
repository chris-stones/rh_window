
#include "context.h"
#include "screen.h"
#include "display.h"
#include "window.h"

#include<stdlib.h>
#include<GLES2/gl2.h>

int rh_render_create( rh_render_handle * render, rh_window_handle window, int major_version, int minor_version, rh_render_handle share ) {
  
  rh_render_handle out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_render)) )) {
    
    const EGLint attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, major_version, EGL_NONE };
    
    out->screen = window->screen;
    
    out->egl_ctx = eglCreateContext(window->screen->display->dpy, window->screen->config, share ? share->egl_ctx : EGL_NO_CONTEXT, attrib_list);
    
    rh_bind_render_window(out,window);
    
    *render = out;

    return 0;
  }
  
  return -1;
}

int rh_bind_render_window(rh_render_handle render, rh_window_handle window) {
  
  EGLSurface drawable = (window)           ? window->surface : EGL_NO_SURFACE;
  EGLContext context  = (window && render) ? render->egl_ctx : EGL_NO_CONTEXT; // if window is null, bind a null render ctx.
  
  if(render) {
    
    eglMakeCurrent(render->screen->display->dpy, drawable, drawable, context);

//    if(window)
//      glViewport(0,0,window->attr.w,window->attr.h);
  
    return 0;
  }
  return -1;
}

int rh_render_destroy( rh_render_handle render) {
  
  if(render) {
    
   eglMakeCurrent(render->screen->display->dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
   
   eglDestroyContext(render->screen->display->dpy, render->egl_ctx);
    
   free(render);

   return 0;
  }

  return -1;
}

