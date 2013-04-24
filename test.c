
#ifdef WIN32
	#include<Windows.h>
#endif

#include<stdio.h>

#include "rh_window.h"

#include<GL/gl.h>
#include<math.h>


int main(int argc, char **argv) {
    
  int exitflag = 0;
  
  rh_display_handle display = 0;
  rh_screen_handle  screen = 0;
  rh_window_handle  window = 0;
  rh_render_handle  render = 0;
  rh_input_handle   input = 0;
  rh_input_data     input_data = 0;

  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  
  rh_display_create(&display);
  rh_screen_create_default(&screen, display);
  rh_window_create(&window, NULL, screen);
  rh_render_create(&render,window, 2,1,0);
  rh_bind_render_window(render, window);
  rh_input_create(&input, window);
  
  glClearColor(1.0f,0.0f,1.0f,1.0f);
  
  while(!exitflag) {
  
    glClear(GL_COLOR_BUFFER_BIT);
    rh_window_swapbuffers(window);
    
    r += 1.0f/255.0f;
    g += 2.0f/255.0f;
    b += 3.0f/255.0f;
    
    glClearColor(sinf(r)/2.0f+0.5f,sinf(g)/2.0f+0.5f,sinf(b)/2.0f+0.5f,1.0f);
    
    if(( input_data = rh_input_get( input ) )) {
    
      switch( rh_input_gettype( input_data ) ) {
		case RH_INPUT_NONE:
		  printf("RH_INPUT_NONE\n");
		  break;
		case RH_INPUT_UNKNOWN:
		  printf("RH_INPUT_UNKNOWN\n");
		  break;
		case RH_INPUT_KEYPRESS:
		{
		  rh_input_key_enum_t k;
		  rh_input_getkey(input_data, &k);
		  printf("RH_INPUT_KEYPRESS %d\n", k);
		  break;
		}
		case RH_INPUT_KEYRELEASE:
		{
		  rh_input_key_enum_t k;
		  rh_input_getkey(input_data, &k);
		  printf("RH_INPUT_KEYRELEASE %d\n", k);
		  if( k == RH_INPUT_KEY_ESCAPE)
			exitflag = 1;
		  break;
		}
		case RH_INPUT_BUTTONPRESS:
		{
		  int x,y;
		  rh_input_button_enum_t b;
		  rh_input_getpointer(input_data, &b, &x, &y, NULL);
		  printf("RH_INPUT_BUTTONPRESS %d %d,%d\n",b,x,y);
		  break;
		}
		case RH_INPUT_BUTTONRELEASE:
		{
		  int x,y;
		  rh_input_button_enum_t b;
		  rh_input_getpointer(input_data, &b, &x, &y, NULL);
		  printf("RH_INPUT_BUTTONRELEASE %d %d,%d\n",b,x,y);
		  break;
		}
		case RH_INPUT_MOTIONNOTIFY:
		{
		  int x,y;
		  rh_input_getpointer(input_data, NULL, &x, &y, NULL);
		  printf("RH_INPUT_MOTIONNOTIFY %d,%d\n",x,y);
		  break;
		}
      }
    }
  }
  
  rh_input_destroy(input);
  rh_bind_render_window(render, NULL);
  rh_render_destroy(render);
  rh_window_destroy(window);
  rh_screen_destroy(screen);
  rh_display_destroy(display);
  
  return 0;
}


