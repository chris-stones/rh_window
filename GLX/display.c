
#include "display.h"

#include<stdlib.h>

int rh_display_create( rh_display_handle * h )  {
  
  rh_display_handle out = NULL; 
  
  if(( out = calloc(1, sizeof( struct _rh_display ) ) )) {
    
    if(( out->dpy = XOpenDisplay(NULL) )) {
      
      *h = out;
      return 0;
    }
  }
  
  if(out) {
    if(out->dpy)
      XCloseDisplay(out->dpy);
    free(out);
  }
  
  return -1;
}

int rh_display_destroy( rh_display_handle dpy ) {
  
  if(dpy) {
    if(dpy->dpy)
      XCloseDisplay(dpy->dpy);
    free(dpy);
  }

  return 0;
}

