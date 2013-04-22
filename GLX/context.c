

#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <string.h>
#include <stdlib.h>

#include "context.h"
#include "window.h"
#include "screen.h"
#include "display.h"


/* code stolen from http://www.opengl.org/archives/resources/features/OGLextensions/ */
static int IsExtensionSupported(const char *extension)
{
  const GLubyte *extensions = NULL;
  const GLubyte *start;
  GLubyte *where, *terminator;

  /* Extension names should not have spaces. */
  where = (GLubyte *) strchr(extension, ' ');
  if (where || *extension == '\0')
    return 0;
  extensions = glGetString(GL_EXTENSIONS);
  /* It takes a bit of care to be fool-proof about parsing the
     OpenGL extensions string. Don't be fooled by sub-strings,
     etc. */
  start = extensions;
  for (;;) {
    where = (GLubyte *) strstr((const char *) start, extension);
    if (!where)
      break;
    terminator = where + strlen(extension);
    if (where == start || *(where - 1) == ' ')
      if (*terminator == ' ' || *terminator == '\0')
        return 1;
    start = terminator;
  }
  return 0;
}

int rh_bind_render_window(rh_render_handle render, rh_window_handle window) {
  
  GLXDrawable drawable = window ? window->glxWindow : None;
  GLXContext  context  = window ? render->glx_ctx : NULL; // if window is null, bind a null render ctx.
  
  glXMakeContextCurrent(render->screen->display->dpy, drawable, drawable, context );
  
  return 0;
}

int rh_render_destroy(rh_render_handle handle) {

  glXMakeCurrent( handle->screen->display->dpy, None, NULL);
  glXDestroyContext ( handle->screen->display->dpy, handle->glx_ctx );
  
  free(handle);
  
  return 0;
}

int rh_render_create( rh_render_handle * _out, rh_screen_handle screen, int major_version, int minor_version, rh_render_handle shareCtx ) {

  rh_render_handle out = NULL;
  
  if((out = calloc(1, sizeof(struct _rh_render) ) )) {
  
    Display * dpy = screen->display->dpy;
    
    GLXFBConfig framebufferConfig = screen->glxFBConfig[0]; // TODO: using first config for now.
    
    out->screen = screen;
    
    if(major_version > 2) {

	typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

	glXCreateContextAttribsARBProc glXCreateContextAttribsARB =
	  (glXCreateContextAttribsARBProc)
	    (glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" ) );

	if( IsExtensionSupported("GLX_ARB_create_context") && glXCreateContextAttribsARB) {

	  const int context_attribs[] = {
		  GLX_CONTEXT_MAJOR_VERSION_ARB, major_version,
		  GLX_CONTEXT_MINOR_VERSION_ARB, minor_version,
		  //GLX_CONTEXT_FLAGS_ARB,
		  //GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		  None
	  };

	  out->glx_ctx = glXCreateContextAttribsARB( dpy, framebufferConfig, shareCtx ? shareCtx->glx_ctx : NULL, True, context_attribs);
	}
    }
    else
      out->glx_ctx = glXCreateNewContext( dpy, framebufferConfig, GLX_RGBA_TYPE, shareCtx ? shareCtx->glx_ctx : NULL, True );

    if(out->glx_ctx) {
    
      *_out = out;
      return 0;
    }
  }
  
  free(out);
  
  return -1;
}

