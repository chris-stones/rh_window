
#pragma once

#include<windows.h>
#include<windowsx.h>

#include <stdlib.h>

#include "../rh_window.h"
#include "window.h"
#include "screen.h"
#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _rh_input_data {
  
  MSG msg;
};

struct _rh_input {
  
  rh_window_handle window;
  
  struct _rh_input_data input_data;
};

#ifdef __cplusplus
} // extern "C" {
#endif

