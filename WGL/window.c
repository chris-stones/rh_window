
#include <string.h>
#include <stdlib.h>

#include "window.h"
#include "screen.h"
#include "display.h"

static const struct _rh_window_attr _default_attr = 
{ 
  0, 0, 
  800, 600, 
  _RH_WINDOW_DECORATIONS | _RH_WINDOW_CURSOR | _RH_WINDOW_KEY_EVENTS | _RH_WINDOW_CLICK_EVENTS
};

static void _set_attr( rh_window_handle h, const struct _rh_window_attr * attr ) {
  
  if(!attr)
    attr = &_default_attr;
  
  h->attr = *attr;
}

static void _set_fs( rh_window_handle h, int fs ) {
 
  h->fs = (char)fs;
}

static int _get_fs( rh_window_handle h ) {
 
  return h->fs;
}

static void SetBorderless(rh_window_handle hnd) {

  // TODO
}

static void SetPointerVisible(rh_window_handle hnd, int vis) {

  // TODO
}

static void SetAboveOthers(rh_window_handle hnd, int above) {

  // TODO
}

static void SetFullscreenMonitors(rh_window_handle hnd) {

  // TODO
}

static void SetFullscreenMode(rh_window_handle h, int fullscreen) {

  if((!!_get_fs(h)) != (!!fullscreen)) {
    
    // TODO:

    if(fullscreen)
      SetFullscreenMonitors(h);
  }
}

static DWORD ExStyle() {

  return  WS_EX_APPWINDOW ;
}

static DWORD WindowStyle() {

  return WS_OVERLAPPEDWINDOW	|
	  WS_CLIPCHILDREN 	|
	  WS_CLIPSIBLINGS 	;
}

static HINSTANCE Instance() {

  return (HINSTANCE)(GetModuleHandle(NULL));
}

static UINT ClassStyle() {

  return CS_OWNDC;
}

static ATOM ClassName(rh_window_handle h) {

  WNDCLASSEX wndClass;
  char classname[64];

  memset(&wndClass,0,sizeof wndClass);
  sprintf(classname, "rh_classname %p", h);

  wndClass.cbSize = sizeof(WNDCLASSEX);
  wndClass.style  = ClassStyle();
  wndClass.lpfnWndProc = &DefWindowProc;
  wndClass.hInstance = Instance();
  wndClass.hCursor = LoadCursor(NULL/*Instance()*/,IDC_ARROW);
  wndClass.lpszClassName = classname;

  return RegisterClassEx( &wndClass );
}

static void Init(rh_window_handle h) {

  h->windowClass = ClassName(h);

  h->hWnd = CreateWindowEx(
		  ExStyle(),
		  (LPCTSTR)((void*)(size_t)(h->windowClass)), 
		  TEXT("WIN32"),
		  WindowStyle(),
		  h->attr.x,h->attr.y,h->attr.w,h->attr.h,
		  NULL,
		  NULL,
		  Instance(),
		  NULL);

  ShowWindow(h->hWnd, SW_SHOW);
}

int rh_window_create( rh_window_handle * wnd, rh_window_attr_t attr, rh_screen_handle screen ) {
 
  rh_window_handle out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_window) ) )) {
    
    _set_attr(out, attr);
    
    out->screen = screen;
    
    Init(out);
    
    out->screen = screen;
    
    *wnd = out;
    
    return 0;
  }
  
  return -1;
}

int rh_window_destroy( rh_window_handle wnd )  {
  
  if( wnd ) {
          
    free(wnd);
  }
  return 0;
}

int rh_window_attr_create(rh_window_attr_t * attr) {

  rh_window_attr_t out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_window_attr) ) )) {
    
    *out = _default_attr;
    
    *attr = out;
  }
  
  return -1;
}

int rh_window_attr_destroy(rh_window_attr_t attr) {
  
  free(attr);
  return 0;
}


static int _get_attr_mask(const char * property) {

  if(strcmp(property, "fullscreen") == 0)
    return _RH_WINDOW_FULLSCREEN;
  if(strcmp(property, "decorations") == 0)
    return _RH_WINDOW_DECORATIONS;
  if(strcmp(property, "cursor") == 0)
    return _RH_WINDOW_CURSOR;
  if(strcmp(property, "key_events") == 0)
    return _RH_WINDOW_KEY_EVENTS;
  if(strcmp(property, "click_events") == 0)
    return _RH_WINDOW_CLICK_EVENTS;
  if(strcmp(property, "mousemove_events") == 0)
    return _RH_WINDOW_MOUSEMOVE_EVENTS;
  if(strcmp(property, "ontop") == 0)
    return _RH_WINDOW_ONTOP;
  
  return 0;
}

int rh_window_attr_seti(rh_window_attr_t attr, const char * property, int i) {
  
  int attr_mask;
  
  if( strcmp( property, "x" ) == 0 ) 
    attr->x = i;
  else if( strcmp( property, "y" ) == 0 ) 
    attr->y = i;
  else if( strcmp( property, "w" ) == 0 ) 
    attr->w = i;
  else if( strcmp( property, "h" ) == 0 )
    attr->h = i;   
  else if(( attr_mask = _get_attr_mask( property ) )) {
    if(i)
      attr->flags |= attr_mask;
    else
      attr->flags &= ~attr_mask;
  }
  else
    return -1;
  
  return 0;
}

int rh_window_attr_geti(const rh_window_attr_t attr, const char * property, int *i) {

  int attr_mask;
  
  if(!i)
    return -1;
  
  if( strcmp( property, "x" ) == 0 ) 
    *i = attr->x;
  else if( strcmp( property, "y" ) == 0 ) 
    *i = attr->y;
  else if( strcmp( property, "w" ) == 0 ) 
    *i = attr->w;
  else if( strcmp( property, "h" ) == 0 )
    *i = attr->h;   
  else if(( attr_mask = _get_attr_mask( property ) ))
    *i = !!(attr->flags & attr_mask);
  else
    return -1;
  
  return 0;
}

int rh_window_swapbuffers( rh_window_handle wnd ) {

  // TODO

  return 0;
}



