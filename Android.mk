LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(rockhopper_INCLUDE_BASE)
LOCAL_EXPORT_CFLAGS := -DRH_TARGET_ANDROID=1

LOCAL_MODULE    := rh_window
LOCAL_SRC_FILES := EGL/context.c
LOCAL_SRC_FILES += EGL/display.c
LOCAL_SRC_FILES += EGL/input.c
LOCAL_SRC_FILES += EGL/screen.c
LOCAL_SRC_FILES += EGL/window.c

LOCAL_LDLIBS    += -llog -landroid -lEGL -lGLESv2

include $(BUILD_STATIC_LIBRARY)

