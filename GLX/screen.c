

#include "screen.h"

#include <stdlib.h>

static const int * _get_glx_attribs() {

	static const int attribs[] = {

		GLX_RENDER_TYPE,		GLX_RGBA_BIT,
		GLX_X_RENDERABLE,		True,
		GLX_DRAWABLE_TYPE,		GLX_WINDOW_BIT,
		GLX_DOUBLEBUFFER,		True,
		GLX_RED_SIZE,			8,
		GLX_GREEN_SIZE,			8,
		GLX_BLUE_SIZE,			8,
		0
	};
	return attribs;
}

int rh_screen_create_default( rh_screen_handle * scr, rh_display_handle h, ... ) {
  
  return rh_screen_create( scr, XDefaultScreen(h->dpy), h);
}

int rh_screen_create( rh_screen_handle * scr, int screen_index, rh_display_handle h, ... ) {
  
  rh_screen_handle out = NULL;
  
  if(( out = calloc(1, sizeof( struct _rh_screen )) )) {
    
    out->display 	= h;
    out->glxFBConfig	= glXChooseFBConfig(h->dpy, screen_index, _get_glx_attribs(), &out->glxFBConfigSize);
    out->xVisualInfo	= glXGetVisualFromFBConfig(h->dpy, out->glxFBConfig[0] );
    out->screenConfig	= XRRGetScreenInfo( h->dpy, RootWindow(h->dpy, screen_index ) );
    out->res		= XRRGetScreenResources(h->dpy, RootWindow(h->dpy,screen_index));
    
    *scr = out;
    return 0;
  }
  
  if(out) {
    if(out->glxFBConfig) XFree( out->glxFBConfig );
    if(out->xVisualInfo) XFree( out->xVisualInfo );
    if(out->screenConfig) XRRFreeScreenConfigInfo(out->screenConfig);
    if(out->res) XFree(out->res);
    free(out);
  }
  
  return -1;
}


int rh_screen_destroy( rh_screen_handle scr ) {
 
  if(scr) {
    if(scr->glxFBConfig) XFree( scr->glxFBConfig );
    if(scr->xVisualInfo) XFree( scr->xVisualInfo );
    if(scr->screenConfig) XRRFreeScreenConfigInfo(scr->screenConfig);
    if(scr->res) XFree(scr->res);
    free(scr);
  }
}


