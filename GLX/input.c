

#include "input.h"

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
 
  Display *dpy = input->window->screen->display->dpy;
  Window window = input->window->window;
  XEvent *event = &input->input_data.xevent;
  long int xEventsMask = input->window->xEventsMask;
  
  if( XCheckWindowEvent(dpy,window,xEventsMask, event) == True )
    return &input->input_data;
  
  return NULL;
}

rh_input_event_enum_t rh_input_gettype( rh_input_data data ) {
  
  if( data ) {
    
    switch( data->xevent.type ) {
      default:
	return RH_INPUT_UNKNOWN;
      case KeyPress:
	return RH_INPUT_KEYPRESS;
      case KeyRelease:
	return RH_INPUT_KEYRELEASE;
      case ButtonPress:
	return RH_INPUT_BUTTONPRESS;
      case ButtonRelease:
	return RH_INPUT_BUTTONRELEASE;
      case MotionNotify:
	return RH_INPUT_MOTIONNOTIFY;
    }
  }
  
  return RH_INPUT_NONE;
}

int rh_input_getpointer( rh_input_data data, rh_input_button_enum_t * b, int * x, int * y, int * p ) {
  
  if( data ) {
  
    if( x ) *x = data->xevent.xbutton.x;
    if( y ) *y = data->xevent.xbutton.y;
    if( p ) *p = 0;
    
    if( b ) {
      switch( data->xevent.xbutton.button ) {
	default:
	  *b = RH_INPUT_UNKNOWNBUTTON;
	  break;
	case 1:
	  *b = RH_INPUT_LEFTBUTTON;
	  break;
	case 2:
	  *b = RH_INPUT_MIDDLEBUTTON;
	  break;
	case 3:
	  *b = RH_INPUT_RIGHTBUTTON;
	  break;
      }
    }
    return 0;
  }
  
  if(b) *b = RH_INPUT_NOBUTTON;
  
  return -1;
}

int rh_input_getkey( rh_input_data data, rh_input_key_enum_t * k ) {

  if( data ) {
    
    if( k ) {
     
      KeySym key = XLookupKeysym( &data->xevent.xkey, 0 );
      
      switch( key ) {
	default: 	*k = RH_INPUT_KEY_UNKNOWN;	break;
	case XK_Escape: *k = RH_INPUT_KEY_ESCAPE; 	break;
	case XK_space:  *k = RH_INPUT_KEY_SPACE; 	break;
	case XK_Return: *k = RH_INPUT_KEY_RETURN; 	break;
	case XK_0:	*k = RH_INPUT_KEY_0;		break;
	case XK_1:	*k = RH_INPUT_KEY_1;		break;
	case XK_2:	*k = RH_INPUT_KEY_2;		break;
	case XK_3:	*k = RH_INPUT_KEY_3;		break;
	case XK_4:	*k = RH_INPUT_KEY_4;		break;
	case XK_5:	*k = RH_INPUT_KEY_5;		break;
	case XK_6:	*k = RH_INPUT_KEY_6;		break;
	case XK_7:	*k = RH_INPUT_KEY_7;		break;
	case XK_8:	*k = RH_INPUT_KEY_8;		break;
	case XK_9:	*k = RH_INPUT_KEY_9;		break;
	case XK_A:	*k = RH_INPUT_KEY_A;		break;
	case XK_B:	*k = RH_INPUT_KEY_B;		break;
	case XK_C:	*k = RH_INPUT_KEY_C;		break;
	case XK_D:	*k = RH_INPUT_KEY_D;		break;
	case XK_E:	*k = RH_INPUT_KEY_E;		break;
	case XK_F:	*k = RH_INPUT_KEY_F;		break;
	case XK_G:	*k = RH_INPUT_KEY_G;		break;
	case XK_H:	*k = RH_INPUT_KEY_H;		break;
	case XK_I:	*k = RH_INPUT_KEY_I;		break;
	case XK_J:	*k = RH_INPUT_KEY_J;		break;
	case XK_K:	*k = RH_INPUT_KEY_K;		break;
	case XK_L:	*k = RH_INPUT_KEY_L;		break;
	case XK_M:	*k = RH_INPUT_KEY_M;		break;
	case XK_N:	*k = RH_INPUT_KEY_N;		break;
	case XK_O:	*k = RH_INPUT_KEY_O;		break;
	case XK_P:	*k = RH_INPUT_KEY_P;		break;
	case XK_Q:	*k = RH_INPUT_KEY_Q;		break;
	case XK_R:	*k = RH_INPUT_KEY_R;		break;
	case XK_S:	*k = RH_INPUT_KEY_S;		break;
	case XK_T:	*k = RH_INPUT_KEY_T;		break;
	case XK_U:	*k = RH_INPUT_KEY_U;		break;
	case XK_V:	*k = RH_INPUT_KEY_V;		break;
	case XK_W:	*k = RH_INPUT_KEY_W;		break;
	case XK_X:	*k = RH_INPUT_KEY_X;		break;
	case XK_Y:	*k = RH_INPUT_KEY_Y;		break;
	case XK_Z:	*k = RH_INPUT_KEY_Z;		break;
      }
      
      return 0;
    }
    
    if(k) *k = RH_INPUT_KEY_NONE;
    
    return 0;
  }
  
  if(k) *k = RH_INPUT_KEY_NONE;
  
  return -1;
}

