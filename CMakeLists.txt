cmake_minimum_required(VERSION 2.8)

project(screen_interface)

add_executable(screen_interface test.c)

if(RHWIN_GLX)
  add_subdirectory(GLX)
  target_link_libraries (screen_interface rh_window_glx m)
endif()

if(RHWIN_GLES2)
  add_subdirectory(EGL)
  target_link_libraries (screen_interface rh_window_egl m)
endif()

if(RHWIN_WGL)
  add_subdirectory(WGL)
  target_link_libraries (screen_interface rh_window_wgl)
endif()

install (FILES rh_window.h DESTINATION include)



