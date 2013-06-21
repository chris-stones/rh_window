
#pragma once

#ifdef __ANDROID__
#ifndef RH_TARGET_OS_ANDROID
#define RH_TARGET_OS_ANDROID 1
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif 

// Forward Declarations of private, implementation data.
struct _rh_display;
struct _rh_screen;
struct _rh_render;
struct _rh_window;
struct _rh_window_attr;
struct _rh_input;
struct _rh_input_data;

// User handles.
typedef struct _rh_display * rh_display_handle;		// Connection to display. Typically one per application.
typedef struct _rh_screen  * rh_screen_handle;		// Screen handle ( NOT a monitor! Think Session / X11 ). Typically one per application.		
typedef struct _rh_window  * rh_window_handle;		// Window handle. One per window.
typedef struct _rh_render  * rh_render_handle;		// Render context. Typically One per window.
typedef struct _rh_window_attr * rh_window_attr_t;	// Optional. Window attributes.
typedef struct _rh_input * rh_input_handle;		// Input handle. One per window.
typedef struct _rh_input_data * rh_input_data;		// Input data container. keys / buttons / positions.

// Input type. returned by rh_input_gettype();
typedef enum {
  
  RH_INPUT_NONE,		// No events.
  RH_INPUT_UNKNOWN,		// Unknown Event.
  RH_INPUT_KEYPRESS,		// Keyboard Key Pressed.
  RH_INPUT_KEYRELEASE,		// Keyboard Key Released.
  RH_INPUT_BUTTONPRESS,		// Mouse Button Pressed.
  RH_INPUT_BUTTONRELEASE,	// Mouse Button Released.
  RH_INPUT_MOTIONNOTIFY,	// Mouse Motion Notify.
  
} rh_input_event_enum_t;

// Mouse Button Enum. Returned by rh_input_getpointer();
typedef enum {
  
  RH_INPUT_NOBUTTON,		// Event did not involve a button.
  RH_INPUT_UNKNOWNBUTTON,	// Event involved unknown button.
  RH_INPUT_LEFTBUTTON,		// Event involved the left mouse button.
  RH_INPUT_MIDDLEBUTTON,	// Event involved the middle mouse button.
  RH_INPUT_RIGHTBUTTON,		// Event involved the right mouse button.
  
} rh_input_button_enum_t;

// Keyboard Key Enum. Returned by rh_input_getkey
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

/***
* Create / Destroy a display context.
* A display context represents a connection to the display.
* Typically, you will create only one per application.
*/
int rh_display_create( rh_display_handle * dpy );
int rh_display_destroy( rh_display_handle dpy );

/***
* Create / Destroy a screen context.
* A screen context represents your work-space. ( X11 Screen )
* A screen is NOT a physical monitor.
* Typically, you will crate only one per application.
* You would only really need 2 screens if you had an ATI card, and a NVIDIA card, and wanted to use them both at the same time.
*/
int rh_screen_create( rh_screen_handle * scr, int screen_index, rh_display_handle dpy );
int rh_screen_create_default( rh_screen_handle * scr, rh_display_handle dpy );
int rh_screen_destroy( rh_screen_handle scr );

/***
* Create / Destroy a window attribute.
*	create a window attribute struct to pass to rh_window_create.
*	If none is given, undefined defaults will be used.
*	valid properties are implementation dependent.
*	common properties are... "w" "h" "fullscreen" "decorations" "cursor" "ontop"
*/
int rh_window_attr_create(rh_window_attr_t * attr);
int rh_window_attr_destroy(rh_window_attr_t attr);
int rh_window_attr_seti(rh_window_attr_t attr, const char * property, int i);
int rh_window_attr_geti(const rh_window_attr_t attr, const char * property, int *i);

/***
* Create / Destroy a window.
*/
int rh_window_create( rh_window_handle * wnd, rh_window_attr_t attr, rh_screen_handle scr );
int rh_window_destroy( rh_window_handle wnd );
int rh_window_swapbuffers( rh_window_handle wnd );

/***
* Create / Destroy an input context.
* You should crate an input context, and call rh_input_get in your main loop.
*/
int rh_input_create( rh_input_handle *input, rh_window_handle wnd );
int rh_input_destroy( rh_input_handle input );

// Check for input. NULL is returned on no input.
rh_input_data rh_input_get( rh_input_handle input );

// Get input kind.
rh_input_event_enum_t rh_input_gettype( rh_input_data data );

// IF the input kind involved the mouse pointer, you can get its position / button here.
int rh_input_getpointer( rh_input_data data, rh_input_button_enum_t * button, int * x, int * y, int * pointer );

// IF the input involved the keyboard, you can query qhich key here.
int rh_input_getkey( rh_input_data data, rh_input_key_enum_t * key );

// manually add pointer events - android kludge.
void rh_input_despatch_pointer_event(rh_input_event_enum_t event, rh_input_button_enum_t btn, int pointer, float x, float y);

/***
* Create / Destroy a rendering context.
*/
int rh_render_create( rh_render_handle * render, rh_window_handle window, int major_version, int minor_version, rh_render_handle share );
int rh_render_destroy( rh_render_handle render);

/***
* Bind a rendering context to a window.
*/
int rh_bind_render_window(rh_render_handle render, rh_window_handle window);

#ifdef __cplusplus
} // extern "C" {
#endif 

