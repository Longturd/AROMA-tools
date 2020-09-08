LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
  
  ##
  ## VERSIONING
  ##
  AROMA_NAME    := AROMA Filemanager
  AROMA_ID      := AROMAFM
  AROMA_VERSION := 1.92
  AROMA_BUILD   := $(shell date +%y%m%d%H)
  AROMA_CN      := Degung Gamelan

  ## LOCAL PATH COPY
  AROMAFM_LOCALPATH := $(LOCAL_PATH)
  
  ## binary output path
  AROMA_OUT_PATH := $(TARGET_RECOVERY_ROOT_OUT)/../../aromafm_out
  
  ## AROMA FILEMANAGER SOURCE FILES
  LOCAL_SRC_FILES += \
    src/main/aroma_controls.c \
    src/main/aroma.c \
    src/main/aroma_ui.c

  ## MODULE SETTINGS
  LOCAL_MODULE                  := aroma_filemanager
  LOCAL_MODULE_TAGS             := eng
  LOCAL_FORCE_STATIC_EXECUTABLE := true
  
  ## INCLUDES & OUTPUT PATH
  LOCAL_C_INCLUDES              := $(AROMAFM_LOCALPATH)/src
  LOCAL_MODULE_PATH             := $(AROMA_OUT_PATH)
  
  ## COMPILER FLAGS
  LOCAL_LDFLAGS                 += -lm -static
  
  ## SET VERSION
  LOCAL_CFLAGS += -DAROMA_NAME="\"$(AROMA_NAME)\""
  LOCAL_CFLAGS += -DAROMA_VERSION="\"$(AROMA_VERSION)\""
  LOCAL_CFLAGS += -DAROMA_BUILD="\"$(AROMA_BUILD)\""
  LOCAL_CFLAGS += -D$(AROMA_ID)=1
  LOCAL_CFLAGS += -DAROMA_BUILD_CN="\"$(AROMA_CN)\""
  
  ## INCLUDED LIBRARIES
  LOCAL_STATIC_LIBRARIES        := libaroma_common
  
## Remove Old Build
$(shell rm -rf $(PRODUCT_OUT)/obj/EXECUTABLES/$(LOCAL_MODULE)_intermediates)

## Create zip installer
AROMA_DEVICE_NAME   := $(shell echo $(TARGET_PRODUCT) | cut -d _ -f 2)
AROMA_ZIP_FILE      := $(AROMA_OUT_PATH)/aromafm_$(AROMA_DEVICE_NAME).zip
$(AROMA_ZIP_FILE): aroma_filemanager
	$(info )
	$(info Making Aroma Installer Zip...)
	$(AROMAFM_LOCALPATH)/tools/android_building.sh $(AROMAFM_LOCALPATH) $(AROMA_OUT_PATH) $(AROMA_DEVICE_NAME)
	$(info Install ----> $(AROMA_ZIP_FILE))
	$(info )

ALL_DEFAULT_INSTALLED_MODULES += $(AROMA_ZIP_FILE)

include $(BUILD_EXECUTABLE)
