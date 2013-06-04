
#include "input.h"


static const int input_buffer_length = 64;
static struct _rh_input_data input_buffer[input_buffer_length] = {0, };
static int input_buffer_read = 0;
static int input_buffer_write = 0;

void rh_input_despatch_pointer_event(rh_input_event_enum_t event, rh_input_button_enum_t btn, int pointer, float x, float y) {
 
  input_buffer[input_buffer_write].event = event;
  input_buffer[input_buffer_write].btn = btn;
  input_buffer[input_buffer_write].pointer = pointer;
  input_buffer[input_buffer_write].x = x;
  input_buffer[input_buffer_write].y = y;
  input_buffer_write = (input_buffer_write+1)%input_buffer_length;
}

static int dequeue_pointer(struct _rh_input_data * out) {
  
  if(input_buffer_read != input_buffer_write) {
    
    *out = input_buffer[input_buffer_read];
    
    input_buffer_read = (input_buffer_read+1)%input_buffer_length;
    
    return 1;
  }
  return 0;
}

//static void enqueue_key(rh_input_event_enum_t event, rh_input_key_enum_t key) {
//  
//}

int rh_input_create( rh_input_handle *input, rh_window_handle wnd ) {
  
    rh_input_handle out;
    
    if(( out = calloc(1, sizeof( struct _rh_input ) ) )) {
      
      *input = out;
      
      return 0;
    }
    
    return -1;
}

int rh_input_destroy( rh_input_handle input ) {
  
  free( input );
}

rh_input_data rh_input_get( rh_input_handle input ) {
 
  if(dequeue_pointer( &input->input_data ) ) {
   
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

rh_input_event_enum_t rh_input_gettype( rh_input_data data ) {
  
  if(data)
    return data->event;
  
  return RH_INPUT_NONE;
}

int rh_input_getpointer( rh_input_data data, rh_input_button_enum_t * b, int * x, int * y, int * p ) {
 
  if(*b) b = RH_INPUT_NOBUTTON;
  
  if(data) {
   
    if(b) *b = data->btn;
    if(x) *x = (int)data->x;
    if(y) *y = (int)data->y;
    if(p) *p = data->pointer;
    
    return 0;
  }
  
  return -1;
}

/*** ANDROID GLUE CODE - use as a callback, or add to native_app_glue 
static int rh_input_despatch( void * app, void * _AInputEvent ) {
  
    if (AInputEvent_getType(_AInputEvent) == AINPUT_EVENT_TYPE_MOTION ) { // 2
        
	size_t pointers = AMotionEvent_getPointerCount(_AInputEvent);
	int i;
	
	int rawaction = AMotionEvent_getAction(_AInputEvent);
	int action = rawaction & AMOTION_EVENT_ACTION_MASK;
	int handledId = -1;
		
	if( action == AMOTION_EVENT_ACTION_DOWN ) { // 0
	
	  int pointerIndex = (rawaction & 0xff00) >> 8;
	  int pointerId = AMotionEvent_getPointerId(_AInputEvent, pointerIndex);
	  float x = AMotionEvent_getX(_AInputEvent, pointerIndex);
	  float y = AMotionEvent_getY(_AInputEvent, pointerIndex);
	  
	  rh_input_despatch_pointer_event( RH_INPUT_BUTTONPRESS, RH_INPUT_LEFTBUTTON, pointerId, x, y );
	  
	  handledId = pointerId;
	}
	else if( action == AMOTION_EVENT_ACTION_UP ) { // 1
	  
	  int pointerIndex = (rawaction & 0xff00) >> 8;
	  int pointerId = AMotionEvent_getPointerId(_AInputEvent, pointerIndex);
	  float x = AMotionEvent_getX(_AInputEvent, pointerIndex);
	  float y = AMotionEvent_getY(_AInputEvent, pointerIndex);
	  
	  rh_input_despatch_pointer_event( RH_INPUT_BUTTONRELEASE, RH_INPUT_LEFTBUTTON, pointerId, x, y );
	  
	  handledId = pointerId;
	}
	
	for(i=0;i<pointers;i++) {
	  
	  float x,y;
	  int pointerId = AMotionEvent_getPointerId(_AInputEvent, i);
	  if(pointerId == handledId)
	    continue;
	  
	  x = AMotionEvent_getX(_AInputEvent, i);
	  y = AMotionEvent_getY(_AInputEvent, i);
	  
	  rh_input_despatch_pointer_event( RH_INPUT_MOTIONNOTIFY, RH_INPUT_LEFTBUTTON, pointerId, x, y);
	}
	
        return 1;
    }
    return 0;
}
***/

