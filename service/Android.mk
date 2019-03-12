LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
    ../common/IDemoService.cpp \
    ../common/IDemoServiceCallback.cpp \
    ../common/NotificationClient.cpp \
    DemoService.cpp

LOCAL_SHARED_LIBRARIES:= libcutils libutils libbinder liblog

LOCAL_MODULE := DemoService

include $(BUILD_EXECUTABLE)
