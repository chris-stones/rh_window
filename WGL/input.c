

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
 
  MSG msg;
  
  if( PeekMessage( &msg, input->window->hWnd, 0, 0, PM_REMOVE ) ) {
    
   TranslateMessage( &msg );
   DispatchMessage ( &msg );
   
   if( msg.hwnd == input->window->hWnd ) {
   
     input->input_data.msg = msg;
     
    return &input->input_data;
   }
  }

  return NULL;
}

rh_input_event_enum_t rh_input_gettype( rh_input_data data ) {
  
  if( data ) {
    
    switch( data->msg.message ) {
      
      default:
      return RH_INPUT_UNKNOWN;
    
      case WM_KEYDOWN:
	return RH_INPUT_KEYPRESS;
      case WM_KEYUP:
	return RH_INPUT_KEYRELEASE;
	
      case WM_LBUTTONDOWN:
      case WM_MBUTTONDOWN:
      case WM_RBUTTONDOWN:
	return RH_INPUT_BUTTONPRESS;
	
      case WM_LBUTTONUP:
      case WM_MBUTTONUP:
      case WM_RBUTTONUP:
	return RH_INPUT_BUTTONRELEASE;
	
      case WM_MOUSEMOVE:
	return RH_INPUT_MOTIONNOTIFY;
    }
  }
  
  return RH_INPUT_NONE;
}

int rh_input_getpointer( rh_input_data data, rh_input_button_enum_t * b, int * x, int * y, int * p ) {
  
  if( data ) {
  
    if( x ) *x = GET_X_LPARAM( data->msg.lParam);
    if( y ) *y = GET_Y_LPARAM( data->msg.lParam);
    if( p ) *p = 0;
    
    if( b ) {
      
      switch( data->msg.message ) {
	default:
	  *b = RH_INPUT_UNKNOWNBUTTON; 
	  break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	  *b = RH_INPUT_LEFTBUTTON; 
	  break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	  *b = RH_INPUT_MIDDLEBUTTON; 
	  break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
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

      switch( data->msg.wParam) {
	default:
	  *k = RH_INPUT_KEY_UNKNOWN;
	  break;
	case VK_ESCAPE:
	  *k = RH_INPUT_KEY_ESCAPE;
	  break;
	case VK_SPACE:
	  *k = RH_INPUT_KEY_SPACE;
	  break;
	case VK_RETURN:
	  *k = RH_INPUT_KEY_RETURN;
	  break;
	case 'A':
	  *k = RH_INPUT_KEY_A;
	  break;
	case 'B':
	  *k = RH_INPUT_KEY_B;
	  break;
	case 'C':
	  *k = RH_INPUT_KEY_C;
	  break;
	case 'D':
	  *k = RH_INPUT_KEY_D;
	  break;
	case 'E':
	  *k = RH_INPUT_KEY_E;
	  break;
	case 'F':
	  *k = RH_INPUT_KEY_F;
	  break;
	case 'G':
	  *k = RH_INPUT_KEY_G;
	  break;
	case 'H':
	  *k = RH_INPUT_KEY_H;
	  break;
	case 'I':
	  *k = RH_INPUT_KEY_I;
	  break;
	case 'J':
	  *k = RH_INPUT_KEY_J;
	  break;
	case 'K':
	  *k = RH_INPUT_KEY_K;
	  break;
	case 'L':
	  *k = RH_INPUT_KEY_L;
	  break;
	case 'M':
	  *k = RH_INPUT_KEY_M;
	  break;
	case 'N':
	  *k = RH_INPUT_KEY_N;
	  break;
	case 'O':
	  *k = RH_INPUT_KEY_O;
	  break;
	case 'P':
	  *k = RH_INPUT_KEY_P;
	  break;
	case 'Q':
	  *k = RH_INPUT_KEY_Q;
	  break;
	case 'R':
	  *k = RH_INPUT_KEY_R;
	  break;
	case 'S':
	  *k = RH_INPUT_KEY_S;
	  break;
	case 'T':
	  *k = RH_INPUT_KEY_T;
	  break;
	case 'U':
	  *k = RH_INPUT_KEY_U;
	  break;
	case 'V':
	  *k = RH_INPUT_KEY_V;
	  break;
	case 'W':
	  *k = RH_INPUT_KEY_W;
	  break;
	case 'X':
	  *k = RH_INPUT_KEY_X;
	  break;
	case 'Y':
	  *k = RH_INPUT_KEY_Y;
	  break;
	case 'Z':
	  *k = RH_INPUT_KEY_Z;
	  break;
	case '0':
	  *k = RH_INPUT_KEY_0;
	  break;
	case '1':
	  *k = RH_INPUT_KEY_1;
	  break;
	case '2':
	  *k = RH_INPUT_KEY_2;
	  break;
	case '3':
	  *k = RH_INPUT_KEY_3;
	  break;
	case '4':
	  *k = RH_INPUT_KEY_4;
	  break;
	case '5':
	  *k = RH_INPUT_KEY_5;
	  break;
	case '6':
	  *k = RH_INPUT_KEY_6;
	  break;
	case '7':
	  *k = RH_INPUT_KEY_7;
	  break;
	case '8':
	  *k = RH_INPUT_KEY_8;
	  break;
	case '9':
	  *k = RH_INPUT_KEY_9;
	  break;
      }
    }
    
    return 0;
  }
  
  if(k) *k = RH_INPUT_KEY_NONE;
  
  return -1;
}

