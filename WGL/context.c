

#include <string.h>
#include <stdlib.h>

#include "context.h"
#include "window.h"
#include "screen.h"
#include "display.h"


int rh_bind_render_window(rh_render_handle render, rh_window_handle window) {
  
  
  return 0;
}

int rh_render_destroy(rh_render_handle handle) {
  
  free(handle);
  
  return 0;
}

int rh_render_create( rh_render_handle * _out, rh_screen_handle screen, int major_version, int minor_version, rh_render_handle shareCtx ) {

  rh_render_handle out = NULL;
  
  if((out = calloc(1, sizeof(struct _rh_render) ) )) {
  
    out->screen = screen;
    
    if(1) {
    
      *_out = out;
      return 0;
    }
  }
  
  free(out);
  
  return -1;
}

