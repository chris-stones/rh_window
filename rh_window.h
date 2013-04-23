
#pragma once

#ifdef __cplusplus
extern "C" {
#endif 

struct _rh_display;
struct _rh_screen;
struct _rh_render;
struct _rh_window;
struct _rh_window_attr;
struct _rh_input;
struct _rh_input_data;

typedef struct _rh_display * rh_display_handle;
typedef struct _rh_screen  * rh_screen_handle;
typedef struct _rh_render  * rh_render_handle;
typedef struct _rh_window  * rh_window_handle;
typedef struct _rh_window_attr * rh_window_attr_t;
typedef struct _rh_input * rh_input_handle;
typedef struct _rh_input_data * rh_input_data;

typedef enum {
  
  RH_INPUT_NONE,
  RH_INPUT_UNKNOWN,
  RH_INPUT_KEYPRESS,
  RH_INPUT_KEYRELEASE,
  RH_INPUT_BUTTONPRESS,
  RH_INPUT_BUTTONRELEASE,
  RH_INPUT_MOTIONNOTIFY,
  
} rh_input_event_enum_t;

typedef enum {
  
  RH_INPUT_NOBUTTON,
  RH_INPUT_UNKNOWNBUTTON,
  RH_INPUT_LEFTBUTTON,
  RH_INPUT_MIDDLEBUTTON,
  RH_INPUT_RIGHTBUTTON,
  
  
} rh_input_button_enum_t;

typedef enum {

  RH_INPUT_KEY_NONE,
  RH_INPUT_KEY_UNKNOWN,
  
  RH_INPUT_KEY_ESCAPE,
  RH_INPUT_KEY_SPACE,
  RH_INPUT_KEY_RETURN,
  RH_INPUT_KEY_0,
  RH_INPUT_KEY_1,
  RH_INPUT_KEY_2,
  RH_INPUT_KEY_3,
  RH_INPUT_KEY_4,
  RH_INPUT_KEY_5,
  RH_INPUT_KEY_6,
  RH_INPUT_KEY_7,
  RH_INPUT_KEY_8,
  RH_INPUT_KEY_9,
  RH_INPUT_KEY_A,
  RH_INPUT_KEY_B,
  RH_INPUT_KEY_C,
  RH_INPUT_KEY_D,
  RH_INPUT_KEY_E,
  RH_INPUT_KEY_F,
  RH_INPUT_KEY_G,
  RH_INPUT_KEY_H,
  RH_INPUT_KEY_I,
  RH_INPUT_KEY_J,
  RH_INPUT_KEY_K,
  RH_INPUT_KEY_L,
  RH_INPUT_KEY_M,
  RH_INPUT_KEY_N,
  RH_INPUT_KEY_O,
  RH_INPUT_KEY_P,
  RH_INPUT_KEY_Q,
  RH_INPUT_KEY_R,
  RH_INPUT_KEY_S,
  RH_INPUT_KEY_T,
  RH_INPUT_KEY_U,
  RH_INPUT_KEY_V,
  RH_INPUT_KEY_W,
  RH_INPUT_KEY_X,
  RH_INPUT_KEY_Y,
  RH_INPUT_KEY_Z,
  
} rh_input_key_enum_t;

int rh_display_create( rh_display_handle * dpy );
int rh_display_destroy( rh_display_handle dpy );

int rh_screen_create( rh_screen_handle * scr, int screen_index, rh_display_handle dpy, ... );
int rh_screen_create_default( rh_screen_handle * scr, rh_display_handle dpy, ... );
int rh_screen_destroy( rh_screen_handle scr );

int rh_window_attr_create(rh_window_attr_t * attr);
int rh_window_attr_destroy(rh_window_attr_t attr);
int rh_window_attr_seti(rh_window_attr_t attr, const char * property, int i);
int rh_window_attr_geti(const rh_window_attr_t attr, const char * property, int *i);

int rh_window_create( rh_window_handle * wnd, rh_window_attr_t attr, rh_screen_handle scr );
int rh_window_destroy( rh_window_handle wnd );
int rh_window_swapbuffers( rh_window_handle wnd );

int rh_input_create( rh_input_handle *input, rh_window_handle wnd );
int rh_input_destroy( rh_input_handle input );
rh_input_data rh_input_get( rh_input_handle input );
rh_input_event_enum_t rh_input_gettype( rh_input_data data );
int rh_input_getpointer( rh_input_data data, rh_input_button_enum_t * button, int * x, int * y, int * pointer );
int rh_input_getkey( rh_input_data data, rh_input_key_enum_t * key );

int rh_render_create( rh_render_handle * render, rh_window_handle window, int major_version, int minor_version, rh_render_handle share );
int rh_render_destroy( rh_render_handle render);

int rh_bind_render_window(rh_render_handle render, rh_window_handle window);

#ifdef __cplusplus
} // extern "C" {
#endif 

