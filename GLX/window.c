
#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include "window.h"
#include "screen.h"
#include "display.h"

static const struct _rh_window_attr _default_attr = 
{ 
  0, 0, 
  800, 600, 
  _RH_WINDOW_DECORATIONS | _RH_WINDOW_CURSOR | _RH_WINDOW_KEY_EVENTS | _RH_WINDOW_CLICK_EVENTS | _RH_WINDOW_MOUSEMOVE_EVENTS
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

typedef enum
{
  _NET_WM_STATE_REMOVE =0,
  _NET_WM_STATE_ADD = 1,
  _NET_WM_STATE_TOGGLE =2
  
} _net_wm_state_enum_t;

static void SetBorderless(rh_window_handle hnd) {

  /*** Stole this code from Stack Overflow
    * MOTIF hints are pretty out of date, but there doesn't seem to be a _NET_* alternative ?
    */
  Display * dpy = hnd->screen->display->dpy;
  Window window = hnd->window;

  struct MwmHints {
      unsigned long flags;
      unsigned long functions;
      unsigned long decorations;
      long input_mode;
      unsigned long status;
  };

  enum {
      MWM_HINTS_FUNCTIONS = (1L << 0),
      MWM_HINTS_DECORATIONS =  (1L << 1),
      MWM_FUNC_ALL = (1L << 0),
      MWM_FUNC_RESIZE = (1L << 1),
      MWM_FUNC_MOVE = (1L << 2),
      MWM_FUNC_MINIMIZE = (1L << 3),
      MWM_FUNC_MAXIMIZE = (1L << 4),
      MWM_FUNC_CLOSE = (1L << 5)
  };

  Atom mwmHintsProperty = XInternAtom(dpy, "_MOTIF_WM_HINTS", 0);
  struct MwmHints hints;
  hints.flags = MWM_HINTS_DECORATIONS;
  hints.decorations = 0;
  XChangeProperty(dpy, window, mwmHintsProperty, mwmHintsProperty, 32,
	  PropModeReplace, (unsigned char *)&hints, 5);
}

static void SetPointerVisible(rh_window_handle hnd, int vis) {

  Display * dpy = hnd->screen->display->dpy;
  Window  window = hnd->window;
  
  if(vis) {

	  XDefineCursor(dpy,window,None);
  }
  else
  {
	  Pixmap bm_no;
	  Colormap cmap;
	  Cursor no_ptr;
	  XColor black, dummy;
	  static char bm_no_data[] = {0, 0, 0, 0, 0, 0, 0, 0};

	  cmap = DefaultColormap(dpy, DefaultScreen(dpy));
	  XAllocNamedColor(dpy, cmap, "black", &black, &dummy);
	  bm_no = XCreateBitmapFromData(dpy, window, bm_no_data, 8, 8);
	  no_ptr = XCreatePixmapCursor(dpy, bm_no, bm_no, &black, &black, 0, 0);

	  XDefineCursor(dpy, window, no_ptr);
	  XFreeCursor(dpy, no_ptr);
	  if (bm_no != None)
		  XFreePixmap(dpy, bm_no);
	  XFreeColors(dpy, cmap, &black.pixel, 1, 0);
  }
}

static void SetAboveOthers(rh_window_handle hnd, int above) {

  Display * dpy = hnd->screen->display->dpy;
  
  Atom wmState    = XInternAtom(dpy,"_NET_WM_STATE", False);
  Atom wmAbove 	= XInternAtom(dpy,"_NET_WM_STATE_ABOVE", False);

  XEvent xev;
	      xev.xclient.type=ClientMessage;
	      xev.xclient.serial = 0;
	      xev.xclient.send_event=True;
	      xev.xclient.window=hnd->window;
	      xev.xclient.message_type=wmState;
	      xev.xclient.format=32;
	      xev.xclient.data.l[0] = above ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
	      xev.xclient.data.l[1] = wmAbove;
	      xev.xclient.data.l[2] = 0;

  XSendEvent(dpy,RootWindow(dpy, hnd->screen->xVisualInfo->screen),False,SubstructureRedirectMask | SubstructureNotifyMask,&xev);
}

static void SetFullscreenMonitors(rh_window_handle hnd) {

  Display * dpy = hnd->screen->display->dpy;
  XVisualInfo * vis = hnd->screen->xVisualInfo;
  int x = hnd->attr.x;
  int y = hnd->attr.y;
  int w = hnd->attr.w;
  int h = hnd->attr.h;
  int i;
  
  int xineramaScreenInfoLength = 0;
  XineramaScreenInfo *xineramaScreenInfo =
	  XineramaQueryScreens(dpy, &xineramaScreenInfoLength);

  int top = 	-1;
  int bot = 	-1;
  int left = 	-1;
  int right = -1;

  for(i=0; i<xineramaScreenInfoLength; i++) {

	  if(y == xineramaScreenInfo[i].y_org && top == -1)
		  top = xineramaScreenInfo[i].screen_number;

	  if(x == xineramaScreenInfo[i].x_org && left == -1)
		  left = xineramaScreenInfo[i].screen_number;

	  if(x+w-1 == xineramaScreenInfo[i].x_org+xineramaScreenInfo[i].width-1 && right==-1)
		  right = xineramaScreenInfo[i].screen_number;

	  if(y+h-1 == xineramaScreenInfo[i].y_org+xineramaScreenInfo[i].height-1 && bot==-1)
		  bot = xineramaScreenInfo[i].screen_number;

	  if(	y == xineramaScreenInfo[i].y_org &&
		  x == xineramaScreenInfo[i].x_org &&
		  x+w-1 == xineramaScreenInfo[i].x_org+xineramaScreenInfo[i].width-1 &&
		  y+h-1 == xineramaScreenInfo[i].y_org+xineramaScreenInfo[i].height-1) {

		  top = right =
		  bot = left  =
			  xineramaScreenInfo[i].screen_number;
	  }
  }

  XFree(xineramaScreenInfo);

  if(top>=0 && bot>=0 && left>=0 && right>=0) {

	  XEvent xev;
	  memset(&xev,0,sizeof xev);
		      xev.xclient.type=ClientMessage;
		      xev.xclient.serial = 0;
  //			xev.xclient.send_event=True;
		      xev.xclient.window=hnd->window;
		      xev.xclient.message_type = XInternAtom(dpy,"_NET_WM_FULLSCREEN_MONITORS", False);
		      xev.xclient.format=32;
		      xev.xclient.data.l[0] = top;
		      xev.xclient.data.l[1] = bot;
		      xev.xclient.data.l[2] = left;
		      xev.xclient.data.l[3] = right;
		      xev.xclient.data.l[4] = 1; // source indication - 1 for normal application.

	  XSendEvent(dpy,RootWindow(dpy, vis->screen),False,SubstructureRedirectMask | SubstructureNotifyMask,&xev);
  }
}

static void SetFullscreenMode(rh_window_handle h, int fullscreen) {

  if((!!_get_fs(h)) != (!!fullscreen)) {
    
    Display * dpy = h->screen->display->dpy;
    XVisualInfo * vis = h->screen->xVisualInfo;

    XEvent xev;
    xev.xclient.type=ClientMessage;
    xev.xclient.serial = 0;
    xev.xclient.send_event=True;
    xev.xclient.window=h->window;
    xev.xclient.message_type=XInternAtom( dpy ,"_NET_WM_STATE", False);
    xev.xclient.format=32;
    xev.xclient.data.l[0] = fullscreen ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
    xev.xclient.data.l[1] = XInternAtom(dpy,"_NET_WM_STATE_FULLSCREEN", False);
    xev.xclient.data.l[2] = 0;

    XSendEvent(dpy,RootWindow(dpy, vis->screen),False,SubstructureRedirectMask | SubstructureNotifyMask,&xev);

    _set_fs(h, fullscreen);

    if(fullscreen)
      SetFullscreenMonitors(h);
  }
}

static void Init(rh_window_handle h, int fullscreen, int borderless) {

  Display * dpy = h->screen->display->dpy;
  XVisualInfo * vis = h->screen->xVisualInfo;
  
  XSetWindowAttributes attribs;
  memset(&attribs,0,sizeof attribs);

  h->xEventsMask = NoEventMask;

  if( h->attr.flags & _RH_WINDOW_CLICK_EVENTS )
	  h->xEventsMask |= ButtonPressMask | ButtonReleaseMask;

  if( h->attr.flags & _RH_WINDOW_KEY_EVENTS )
	  h->xEventsMask |= KeyPressMask | KeyReleaseMask;

  if( h->attr.flags & _RH_WINDOW_MOUSEMOVE_EVENTS )
	  h->xEventsMask |= PointerMotionMask;

  attribs.event_mask = h->xEventsMask;
  attribs.border_pixel = 0;
  attribs.bit_gravity = StaticGravity;

  if(fullscreen)
    attribs.override_redirect = True;

  attribs.colormap = XCreateColormap(
      dpy,
      RootWindow(dpy, vis->screen ),
      vis->visual, AllocNone);

  GLint winMask = CWBorderPixel | CWBitGravity |
		  CWEventMask | CWColormap;

  h->window = XCreateWindow(dpy, RootWindow(dpy, vis->screen),h->attr.x,h->attr.y,
    h->attr.w,h->attr.h, // Window manager will probably override this!
    0,
    vis->depth, InputOutput,
    vis->visual, winMask, &attribs);

  h->glxWindow = glXCreateWindow(dpy,
    h->screen->glxFBConfig[0], // TODO: using first config in the list
    h->window,
    0);

  XMapWindow(dpy, h->window);

  XStoreName(dpy, h->window, "GLX");

  if(!fullscreen) {
	  XMoveWindow(dpy, h->window, h->attr.x, h->attr.y);
	  if(borderless)
		  SetBorderless(h);
  }
  else {

	  SetFullscreenMode( h, fullscreen );
	  SetAboveOthers( h, fullscreen );
  }

  XFlush(dpy);
}

int rh_window_create( rh_window_handle * wnd, rh_window_attr_t attr, rh_screen_handle screen ) {
 
  rh_window_handle out = NULL;
  
  if(( out = calloc(1, sizeof(struct _rh_window) ) )) {
    
    _set_attr(out, attr);
    
    out->screen = screen;
    
    Init(out, out->attr.flags & _RH_WINDOW_FULLSCREEN, out->attr.flags & _RH_WINDOW_FULLSCREEN);
    
    out->screen = screen;
    
    *wnd = out;
    
    return 0;
  }
  
  return -1;
}

int rh_window_destroy( rh_window_handle wnd )  {
  
  if( wnd ) {
    
    Display * dpy = wnd->screen->display->dpy;
    
    glXDestroyWindow(dpy, wnd->glxWindow);
    XDestroyWindow(dpy, wnd->window);
   
    free(wnd);
  }
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
  
  glXSwapBuffers (wnd->screen->display->dpy, wnd->glxWindow );
  
  return 0;
}

int rh_window_getsize( rh_window_handle wnd, int * w, int * h) {

  if(!wnd)
    return -1;
  
  if(w)
    *w = wnd->attr.w;
  
  if(h)
    *h = wnd->attr.h;
  
  return 0;
}



