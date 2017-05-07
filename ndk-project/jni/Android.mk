LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, $(wildcard $(LOCAL_PATH)/libpng/*.c))
LOCAL_C_INCLUDES := $(LOCAL_PATH)/libpng
LOCAL_CFLAGS     += -O2
LOCAL_MODULE     := png

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

extra_sources := $(subst $(LOCAL_PATH)/,, $(wildcard $(LOCAL_PATH)/haru_bindings/*.cpp))

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/libpng \
    $(LOCAL_PATH)/libharu/include \
    $(LOCAL_PATH)/libharu/src \
    $(LOCAL_PATH)/haru_bindings
LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, $(wildcard $(LOCAL_PATH)/libharu/src/*.c)) $(extra_sources)
LOCAL_LDLIBS    := -lz  -lm -llog
LOCAL_CFLAGS    += -O2  -D__ANDROID__ -fPIC
LOCAL_MODULE    := haru

ifeq ($(TARGET_ARCH_ABI),$(filter $(TARGET_ARCH_ABI), arm64-v8a mips64 x86_64))
LOCAL_CFLAGS    += -D__ANDROID64__
endif

LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)
