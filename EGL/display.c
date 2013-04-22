
#include <stdlib.h>

#include "display.h"

int rh_display_create( rh_display_handle * dpy ) {
 
  rh_display_handle h = NULL;
  
  if(( h = calloc(1, sizeof(struct _rh_display)) )) {
   
    if((h->dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY ) {
     
      free(h);
      return -1;
    }
    
    if( eglInitialize(h->dpy, &h->version_major, &h->version_minor) != EGL_TRUE ) {
     
      free(h);
      return -1;
    }
    
    *dpy = h;
    return 0;
  }
  
  return -1;
}

int rh_display_destroy( rh_display_handle dpy ) {
 
  if(dpy) {
   
    eglTerminate(dpy->dpy);
    free(dpy);
  }
  
  return 0;
}

