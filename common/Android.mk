LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

  ## Check for ARM NEON
  AROMA_ARM_NEON      := false
  ifeq ($(ARCH_ARM_HAVE_NEON),true)
    AROMA_ARM_NEON    := true
  endif
  
  ##
  ## Force Compiling Without ARM NEON
  ##   -- Uncomment This Line --
  ##
  # AROMA_ARM_NEON      := false
  #

LOCAL_MODULE := libaroma_common
  ## ZLIB SOURCE FILES
  LOCAL_SRC_FILES := 	\
    zlib/adler32.c \
    zlib/crc32.c \
    zlib/infback.c \
    zlib/inffast.c \
    zlib/inflate.c \
    zlib/inftrees.c \
    zlib/zutil.c
  ## ZLIB NEON SOURCE
  ifeq ($(AROMA_ARM_NEON),true)
    LOCAL_SRC_FILES += zlib/inflate_fast_copy_neon.s
  endif
  
  ## PNG SOURCE FILES
  LOCAL_SRC_FILES += \
    png/png.c \
    png/pngerror.c \
    png/pnggccrd.c \
    png/pngget.c \
    png/pngmem.c \
    png/pngpread.c \
    png/pngread.c \
    png/pngrio.c \
    png/pngrtran.c \
    png/pngrutil.c \
    png/pngset.c \
    png/pngtrans.c \
    png/pngvcrd.c
  ## PNG NEON SOURCE
  ifeq ($(AROMA_ARM_NEON),true)
    LOCAL_SRC_FILES += png/png_read_filter_row_neon.s
  endif
    
  ## MINUTF8 & MINZIP SOURCE FILES
  LOCAL_SRC_FILES += \
    minutf8/minutf8.c \
    minzip/DirUtil.c \
    minzip/Hash.c \
    minzip/Inlines.c \
    minzip/SysUtil.c \
    minzip/Zip.c
  
  ## FREETYPE SOURCE FILES
  LOCAL_SRC_FILES += \
    freetype/autofit/autofit.c \
    freetype/base/basepic.c \
    freetype/base/ftapi.c \
    freetype/base/ftbase.c \
    freetype/base/ftbbox.c \
    freetype/base/ftbitmap.c \
    freetype/base/ftglyph.c \
    freetype/base/ftinit.c \
    freetype/base/ftpic.c \
    freetype/base/ftstroke.c \
    freetype/base/ftsynth.c \
    freetype/base/ftsystem.c \
    freetype/cff/cff.c \
    freetype/pshinter/pshinter.c \
    freetype/psnames/psnames.c \
    freetype/raster/raster.c \
    freetype/sfnt/sfnt.c \
    freetype/smooth/smooth.c \
    freetype/truetype/truetype.c \
    freetype/base/ftlcdfil.c
   
  ## EDIFY PARSER SOURCE FILES
  LOCAL_SRC_FILES += \
    aroma/edify/expr.c \
    aroma/edify/lex.yy.c \
    aroma/edify/parser.c

  ## AROMA LIBRARIES SOURCE FILES
  LOCAL_SRC_FILES += \
    aroma/aroma_array.c \
    aroma/aroma_freetype.c \
    aroma/aroma_graph.c \
    aroma/aroma_input.c \
    aroma/aroma_languages.c \
    aroma/aroma_libs.c \
    aroma/aroma_memory.c \
    aroma/aroma_png.c \
    aroma/aroma_zip.c

  ## AROMA CONTROLS SOURCE FILES
  LOCAL_SRC_FILES += \
    aroma/controls/aroma_control_button.c \
    aroma/controls/aroma_control_check.c \
    aroma/controls/aroma_control_checkopt.c \
    aroma/controls/aroma_control_console.c \
    aroma/controls/aroma_control_edit.c \
    aroma/controls/aroma_control_filebox.c \
    aroma/controls/aroma_control_ime.c \
    aroma/controls/aroma_control_ime2.c \
    aroma/controls/aroma_control_label.c \
    aroma/controls/aroma_control_progress.c \
    aroma/controls/aroma_control_threads.c \
    aroma/controls/aroma_control_checkbox.c \
    aroma/controls/aroma_control_imgbutton.c \
    aroma/controls/aroma_control_menubox.c \
    aroma/controls/aroma_control_optbox.c \
    aroma/controls/aroma_control_textbox.c \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_CFLAGS := -O2 
LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY=1 -DDARWIN_NO_CARBON 
LOCAL_CFLAGS += -fdata-sections -ffunction-sections
LOCAL_CFLAGS += -Wl,--gc-sections -fPIC -DPIC
LOCAL_CFLAGS += -D_AROMA_NODEBUG
  
  ifeq ($(AROMA_ARM_NEON),true)
    LOCAL_CFLAGS                  += -mfloat-abi=softfp -mfpu=neon -D__ARM_HAVE_NEON
  endif

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/include
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_EXPORT_LDFLAGS := -lm

include $(BUILD_STATIC_LIBRARY)
