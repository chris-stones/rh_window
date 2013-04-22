
#pragma once

#include<android/looper.h>

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
 
  input->input_data.ident = ALooper_pollAll(0, NULL, &input->input_data.events , &input->input_data.source);
  
  if( input->input_data.ident >= 0) {
    
   
    
   return &input->input_data;  
  }
  
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

