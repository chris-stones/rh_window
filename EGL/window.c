
#include <stdlib.h>
#include <string.h>

#include "display.h"
#include "window.h"
#include "screen.h"

static const struct _rh_window_attr _default_attr = 
{ 
  0, 0, 
  800, 600,
  0
};

static void _set_attr( rh_window_handle h, const struct _rh_window_attr * attr ) {
  
  if(!attr)
    attr = &_default_attr;
  
  h->attr = *attr;
}

int rh_window_attr_create(rh_window_attr_t * attr) {
   
  rh_window_attr_t out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_window_attr) ) )) {
    
    *out = _default_attr;
    
    *attr = out;
  }
  
  return -1;
}

int rh_window_attr_destroy(rh_window_attr_t attr) {
 
  free(attr);
}

static int _get_attr_mask(const char * property) {

  if(strcmp(property, "fullscreen") == 0)
    return _RH_WINDOW_FULLSCREEN;
  
  return 0;
}

int rh_window_attr_seti(rh_window_attr_t attr, const char * property, int i) {
  
    int attr_mask;
    
    if(!attr)
      return -1;
  
  if( strcmp( property, "x" ) == 0 ) 
    attr->x = i;
  else if( strcmp( property, "y" ) == 0 ) 
    attr->y = i;
  else if( strcmp( property, "w" ) == 0 ) 
    attr->w = i;
  else if( strcmp( property, "h" ) == 0 )
    attr->h = i;   
  else if(( attr_mask = _get_attr_mask( property ) )) {
    if(i)
      attr->flags |= attr_mask;
    else
      attr->flags &= ~attr_mask;
  }
  else
    return -1;
  
  return 0;
}

int rh_window_attr_geti(const rh_window_attr_t attr, const char * property, int *i) {
  
  int attr_mask;
  
  if(!i)
    return -1;
  
  if( strcmp( property, "x" ) == 0 ) 
    *i = attr->x;
  else if( strcmp( property, "y" ) == 0 ) 
    *i = attr->y;
  else if( strcmp( property, "w" ) == 0 ) 
    *i = attr->w;
  else if( strcmp( property, "h" ) == 0 )
    *i = attr->h;   
  else if(( attr_mask = _get_attr_mask( property ) ))
    *i = !!(attr->flags & attr_mask);
  else
    return -1;
  
  return 0;
}

int rh_window_create( rh_window_handle * wnd, rh_window_attr_t attr, rh_screen_handle screen ) {
  
  rh_window_handle out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_window) ) )) {
    
    _set_attr(out, attr);
    
    out->screen = screen;
    
    out->surface = eglCreateWindowSurface(
      screen->display->dpy, 
      screen->config, 
      (EGLNativeWindowType)(&screen->display->nativewindow),
      NULL);
    
    *wnd = out;
    
    return 0;
  }
  
  return -1;
}

int rh_window_destroy( rh_window_handle wnd ) {
  
  if(wnd) {
    eglDestroySurface(wnd->screen->display->dpy, wnd->surface);
    free(wnd);
  }
  return 0;
}

int rh_window_swapbuffers( rh_window_handle wnd ) {
  
  eglSwapBuffers (wnd->screen->display->dpy, wnd->surface);
  
  return 0;
}
