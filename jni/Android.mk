#  OpenGL lighting example
#
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
include $(LOCAL_PATH)/../../bluegin/BlueGin.mk

LOCAL_MODULE 	 := libcanabalt
LOCAL_CFLAGS 	 := $(BLUEGIN_CFLAGS)
LOCAL_C_INCLUDES := $(BLUEGIN_INCLUDE) jni/include

LOCAL_SRC_FILES  := src/BG.cpp \
					src/Billboard.cpp \
					src/Bomb.cpp \
					src/Building.cpp \
					src/Crane.cpp \
					src/CraneTrigger.cpp \
					src/DemoMgr.cpp \
					src/Dove.cpp \
					src/GibEmitter.cpp \
					src/Hall.cpp \
					src/HUD.cpp \
					src/Jet.cpp \
					src/Leg.cpp \
					src/Obstacle.cpp \
					src/Player.cpp \
					src/PlayState.cpp \
					src/Sequence.cpp \
					src/Shard.cpp \
					src/Smoke.cpp \
					src/Walker.cpp \
					src/Window.cpp \
				    src/CanabaltApp.cpp

LOCAL_STATIC_LIBRARIES := cinder-prebuilt bluegin-prebuilt flx-prebuilt box2d-prebuilt 
# LOCAL_LDLIBS 	 := $(BLUEGIN_LDLIBS)

include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/../../bluegin/Modules.mk

