
#include "screen.h"

#include <stdlib.h>

static const int * _get_glx_attribs() {

  static const int attribs[] = {
    0
  };
  return attribs;
}

int rh_screen_create_default( rh_screen_handle * scr, rh_display_handle h, ... ) {
  
  return rh_screen_create( scr, 0, h);
}

int rh_screen_create( rh_screen_handle * scr, int screen_index, rh_display_handle h, ... ) {
  
  rh_screen_handle out = NULL;
  
  if(( out = calloc(1, sizeof( struct _rh_screen )) )) {
    
    out->display = h;
    
    *scr = out;
    return 0;
  }
  
  if(out) {

    free(out);
  }
  
  return -1;
}


int rh_screen_destroy( rh_screen_handle scr ) {
 
  if(scr) {
    
    free(scr);
  }
  return 0;
}


