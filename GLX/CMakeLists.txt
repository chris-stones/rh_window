
# HACK!!!
ADD_DEFINITIONS(-fPIC)

FILE(GLOB c_source_files *.c)

add_library(rh_window_glx SHARED ${c_source_files} )

install (TARGETS rh_window_glx DESTINATION lib)

target_link_libraries (rh_window_glx X11 Xrandr Xinerama GL)

