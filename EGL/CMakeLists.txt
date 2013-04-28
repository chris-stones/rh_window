
# HACK!!!
ADD_DEFINITIONS(-fPIC)

FILE(GLOB c_source_files *.c)

add_library(rh_window_egl SHARED ${c_source_files} )

install (TARGETS rh_window_egl DESTINATION lib)

FIND_LIBRARY(EGL_LIB EGL)
FIND_LIBRARY(GLESv2_LIB GLESv2)

target_link_libraries (rh_window_egl ${EGL_LIB} ${GLESv2_LIB} )

