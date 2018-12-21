LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
#log para
LOCAL_LDLIBS    := -lm -llog 
LOCAL_C_INCLUDES:=$(LOCAL_PATH)/include
LOCAL_SRC_FILES:= \
src/adhocd.c

LOCAL_MODULE:= libadhocd

#TARGET_PRELINK_MODULE := false
LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
#LOCAL_C_INCLUDES :=
#LOCAL_STATIC_LIBRARIES :=
LOCAL_SHARED_LIBRARIES += \
libcutils libutils liblog
include $(BUILD_SHARED_LIBRARY)





#LOCAL_PATH := $(call my-dir)
##Android.mk通常需要定义好LOCAL_PATH,表示当前工作路径
##函数my-dir是编译系统提供的，返回当前路径
 
#include $(CLEAR_VARS)
##这一步操作主要是清空之前定义的LOCAL_XXX开头的变量，是必须要的操作
 
#LOCAL_C_INCLUDES:=$(LOCAL_PATH)/include
##定义源文件所需的头文件所需的目录
 
#LOCAL_MODULE:= libadhocyaya
##定义编译出来的模块名
 
##LOCAL_SHARED_LIBRARIES := liblog
##编译此模块需要依赖的动态库
 
#LOCAL_SRC_FILES := src/hello-android.c
##定义编译模块所需的源文件
#LOCAL_SRC_FILES:= \
#src/adhocyaya.c
 
#include $(BUILD_SHARED_LIBRARY)
##定义编译出来的目标文件，如动态库，静态库，jar包以及apk




#编译可执行文件，步骤和上述一样
#include $(CLEAR_VARS)
#LOCAL_C_INCLUDES:=$(LOCAL_PATH)/include
#LOCAL_SHARED_LIBRARIES := liblog \
						  #libhello-android 
 
#LOCAL_SRC_FILES	:= src/main.c
#LOCAL_MODULE	:= main
#include $(BUILD_EXECUTABLE)

