

#include <string.h>
#include <stdlib.h>

#include "context.h"
#include "window.h"
#include "screen.h"
#include "display.h"


int rh_bind_render_window(rh_render_handle render, rh_window_handle window) {
  
  wglMakeCurrent(render->dc,render->rc);
  
  return 0;
}

int rh_render_destroy(rh_render_handle handle) {

  if(handle) {
    
    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(handle->rc);
    ReleaseDC( handle->window->hWnd, handle->dc);
    
    free(handle);
  }
  
  return 0;
}

int rh_render_create( rh_render_handle * _out, rh_window_handle window, int major_version, int minor_version, rh_render_handle shareCtx ) {

  rh_render_handle out = NULL;
  
  if((out = calloc(1, sizeof(struct _rh_render) ) )) {
  
	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat;

    out->window = window;
   
    memset(&pfd, 0, sizeof pfd);
    pfd.nSize = sizeof pfd;
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;
    pfd.iPixelType = PFD_TYPE_RGBA ;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 16;
    
    out->window = window;
    out->dc = GetDC( window->hWnd );
    window->dc = out->dc;

    nPixelFormat = ChoosePixelFormat(out->dc, &pfd);
    SetPixelFormat(out->dc,nPixelFormat, &pfd);

    out->rc = wglCreateContext(out->dc);
    wglMakeCurrent(out->dc,out->rc);
    
    if(out->rc) {
    
      *_out = out;
      return 0;
    }
  }
  
  free(out);
  
  return -1;
}

