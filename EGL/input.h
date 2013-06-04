#pragma once

#include <stdlib.h>

#include "../rh_window.h"
#include "window.h"
#include "screen.h"
#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _rh_input_data {
  
  rh_input_event_enum_t event;
  rh_input_button_enum_t btn;
  int pointer;
  float x; 
  float y;
};

struct _rh_input {
  
  struct _rh_input_data input_data;
};

#ifdef __cplusplus
} // extern "C" {
#endif

