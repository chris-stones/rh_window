
#pragma once

#include<windows.h>

#include "../rh_window.h"

typedef enum {
  
  _RH_WINDOW_FULLSCREEN  	= (1<<0),
  _RH_WINDOW_DECORATIONS 	= (1<<1),
  _RH_WINDOW_CURSOR	 	= (1<<2),
  _RH_WINDOW_KEY_EVENTS		= (1<<3),
  _RH_WINDOW_CLICK_EVENTS 	= (1<<4),
  _RH_WINDOW_MOUSEMOVE_EVENTS   = (1<<5),
  _RH_WINDOW_ONTOP 		= (1<<6),
  
} _rh_window_attr_flags_enum;

struct _rh_window_attr {
  
  int x;
  int y;
  int w;
  int h;
  int flags;
};

struct _rh_window {
  
  struct _rh_window_attr attr;
  
  rh_screen_handle screen;
  
  char fs;
  
  HWND hWnd;
  ATOM windowClass;
  HDC dc;
};


