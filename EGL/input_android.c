
#include "input_android.h"

int rh_input_create( rh_input_handle *input, rh_window_handle wnd ) {
  
    rh_input_handle out;
    
    if(( out = calloc(1, sizeof( struct _rh_input ) ) )) {
     
      out->window = wnd;
      
      *input = out;
      
      return 0;
    }
    
    return -1;
}

int rh_input_destroy( rh_input_handle input ) {
  
  free( input );
}

rh_input_data rh_input_get( rh_input_handle input ) {
 
  
  return NULL;
}


int rh_input_getkey( rh_input_data data, rh_input_key_enum_t * k ) {
 
  if( data ) {
  
    if( k )
      *k = RH_INPUT_KEY_UNKNOWN;
  
    return 0;
  }
  
  if(k)
    *k = RH_INPUT_KEY_NONE;
  
  return -1;
}

rh_input_event_enum_t rh_input_gettype( rh_input_data data ) {
   
  return RH_INPUT_NONE;
}

int rh_input_getpointer( rh_input_data data, rh_input_button_enum_t * b, int * x, int * y, int * p ) {
 
  return -1;
}

