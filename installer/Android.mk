LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
  
  ##
  ## VERSIONING
  ##
  AROMA_NAME    := AROMA Installer
  AROMA_ID      := AROMAINSTALLER
  AROMA_VERSION := 2.70RC2
  AROMA_BUILD   := $(shell date +%y%m%d%H)
  AROMA_CN      := Flamboyan

  ## LOCAL PATH COPY
  AROMA_INSTALLER_LOCALPATH := $(LOCAL_PATH)

  ## AROMA INSTALLER SOURCE FILES
  LOCAL_SRC_FILES += \
    src/main/aroma_controls.c \
    src/main/aroma_ui.c \
    src/main/aroma_installer.c \
    src/main/aroma.c
  
  ## MODULE SETTINGS
  LOCAL_MODULE                  := aroma_installer
  LOCAL_MODULE_TAGS             := eng
  LOCAL_FORCE_STATIC_EXECUTABLE := true
  
  ## INCLUDES & OUTPUT PATH
  LOCAL_C_INCLUDES              := $(AROMA_INSTALLER_LOCALPATH)/src
  LOCAL_MODULE_PATH             := $(AROMA_INSTALLER_LOCALPATH)/out
  
  ## COMPILER FLAGS
  LOCAL_LDFLAGS                  := -lm -static
#  LOCAL_CFLAGS                  += -D_AROMA_VERBOSE_INFO
  
  ## SET VERSION
  LOCAL_CFLAGS += -DAROMA_NAME="\"$(AROMA_NAME)\""
  LOCAL_CFLAGS += -DAROMA_VERSION="\"$(AROMA_VERSION)\""
  LOCAL_CFLAGS += -D$(AROMA_ID)=1
  LOCAL_CFLAGS += -DAROMA_BUILD="\"$(AROMA_BUILD)\""
  LOCAL_CFLAGS += -DAROMA_BUILD_CN="\"$(AROMA_CN)\""
  
  ## INCLUDED LIBRARIES
  LOCAL_STATIC_LIBRARIES        := libaroma_common
  
  ##
  ## Remove Old Build
  ##
  ifeq ($(MAKECMDGOALS),$(LOCAL_MODULE))
    $(shell rm -rf $(PRODUCT_OUT)/obj/EXECUTABLES/$(LOCAL_MODULE)_intermediates)
  endif

include $(BUILD_EXECUTABLE)
    
    
include $(CLEAR_VARS)
LOCAL_MODULE        := aroma_installer.zip
LOCAL_MODULE_TAGS   := eng
ifeq ($(MAKECMDGOALS),aroma_installer.zip)
  $(info ==========================================================================)
  $(info )
  $(info MAKING AROMA Installer ZIP)
  OUTPUT_SH := $(shell $(AROMA_INSTALLER_LOCALPATH)/tools/android_building.sh)
  ifeq ($(OUTPUT_SH),0)
    $(info Please Compile AROMA Installer First, by running: make -j4 aroma_installer)
  else
    $(info AROMA ZIP is On $(AROMA_INSTALLER_LOCALPATH)/out/aroma.zip)
  endif
  $(info )
  $(info ==========================================================================)
endif

