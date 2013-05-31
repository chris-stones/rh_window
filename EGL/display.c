
#include <stdlib.h>
#include <stdio.h>

#ifdef RH_TARGET_OS_RASPBERRYPI
  #include <bcm_host.h>
#endif

#include "display.h"

#ifdef RH_TARGET_OS_ANDROID
  struct ANativeWindow;
  typedef struct ANativeWindow ANativeWindow;
  int32_t ANativeWindow_setBuffersGeometry(ANativeWindow* window, int32_t width, int32_t height, int32_t format);
  
  static inline ANativeWindow * GetAndroidNativeWindow() {
	 
    /*** MEGGA HACK! ***/
    
    extern ANativeWindow * __rh_hack_get_android_native_window();
    
    return __rh_hack_get_android_native_window();
  }
#endif /*** RH_TARGET_OS_ANDROID **/

int rh_display_create( rh_display_handle * dpy ) {
 
  rh_display_handle h = NULL;
  
  if(( h = calloc(1, sizeof(struct _rh_display)) )) {
    
#ifdef RH_TARGET_OS_ANDROID
    h->nativewindow = (EGLNativeWindowType)GetAndroidNativeWindow();
#endif
        
#ifdef RH_TARGET_OS_RASPBERRYPI
    bcm_host_init();
    
    if( graphics_get_display_size(0 /* LCD */, &h->display_width, &h->display_height) < 0 )
      return -1;
   
   h->dst_rect.x = 0;
   h->dst_rect.y = 0;
   h->dst_rect.width = h->display_width;
   h->dst_rect.height = h->display_height;
   
    // You can hardcode the resolution here:
   //h->display_width = 1024;
   //h->display_height = 768;

   h->src_rect.x = 0;
   h->src_rect.y = 0;
   h->src_rect.width = h->display_width << 16;
   h->src_rect.height = h->display_height << 16;

   h->dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
   h->dispman_update = vc_dispmanx_update_start( 0 );

   h->dispman_element = vc_dispmanx_element_add ( h->dispman_update, 
      h->dispman_display, 0/*layer*/, &h->dst_rect, 0/*src*/,
      &h->src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 
      0/*clamp*/, 0/*transform*/);

   h->nativewindow_obj.element = h->dispman_element;
   h->nativewindow_obj.width = h->display_width;
   h->nativewindow_obj.height = h->display_height;
   
   h->nativewindow = (EGLNativeWindowType)(&h->nativewindow_obj);
   
   vc_dispmanx_update_submit_sync( h->dispman_update );
#endif /*** RH_TARGET_OS_RASPBERRYPI ***/
   
    if((h->dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY ) {
     
      printf("eglGetDisplay failed!!!\n");
      free(h);
      return -1;
    }
    
    printf("GOT AN EGL DISPLAY!\n");
    
    if( eglInitialize(h->dpy, &h->version_major, &h->version_minor) != EGL_TRUE ) {
     
      printf("eglInitialize failed!!!\n");
      free(h);
      return -1;
    }
    
    printf("EGL INITIALISED!\n");
    
    *dpy = h;
    return 0;
  }
  
  return -1;
}

int rh_display_destroy( rh_display_handle dpy ) {
 
  if(dpy) {
   
    eglTerminate(dpy->dpy);
    free(dpy);
#ifdef RH_TARGET_OS_RASPBERRYPI
    bcm_host_deinit();
#endif /*** RH_TARGET_OS_RASPBERRYPI ***/
  }
  
  return 0;
}

