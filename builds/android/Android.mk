################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################

BASE_PATH := $(call my-dir)
APP_PLATFORM = android-10

LOCAL_PATH := $(BASE_PATH)

#   Info for libzmq

include $(CLEAR_VARS)
LOCAL_MODULE := zmq
LOCAL_SRC_FILES := libzmq.so
include $(PREBUILT_SHARED_LIBRARY)

#   Build zgtask

include $(CLEAR_VARS)
LOCAL_MODULE := zgtask
LOCAL_C_INCLUDES := ../../include $(LIBZMQ)/include
LOCAL_SRC_FILES := zgtask_task.c zgtask_net.c zgtask_client.c zgtask_node.c zgtask_worker.c zgtask_tree.c
LOCAL_SHARED_LIBRARIES := zmq
include $(BUILD_SHARED_LIBRARY)

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
