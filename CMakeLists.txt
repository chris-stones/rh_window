cmake_minimum_required(VERSION 2.8)

project(screen_interface)

#install(TARGETS screen_interface RUNTIME DESTINATION bin)

add_subdirectory(GLX)
add_subdirectory(EGL)
add_subdirectory(WGL)

add_executable(screen_interface main.c)

install (FILES rh_window.h DESTINATION include)

target_link_libraries (screen_interface rh_window_glx)

