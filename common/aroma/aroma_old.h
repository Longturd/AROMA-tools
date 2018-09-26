/*
 * Copyright (C) 2011 Ahmad Amarullah ( http://amarullz.com/ )
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Descriptions:
 * -------------
 * Main AROMA common HEADER
 *
 */

#ifndef __AROMA_COMMON_H__
#define __AROMA_COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>

//-- Main Definitions
#define AROMA_DIR         "META-INF/com/google/android/aroma"
#define AROMA_TMP         "/tmp/aroma"
#define AROMA_THEME_CNT   24

//#######################################################//
//##                                                   ##//
//##               LIST OF DEFINITIONS                 ##//
//##                                                   ##//
//#######################################################//

//
// Common Data Type
//

/* primitive unsigneds */
typedef uint8_t byte;
typedef uint16_t word;
typedef uint16_t color;
typedef uint32_t dword;

/* primitive pointers */
typedef color * colorp;
typedef byte * bytep;
typedef word * wordp;
typedef dword * dwordp;
typedef void * voidp;

//
// AROMA Canvas Structure
//
typedef struct {
  int     w;       // Width
  int     h;       // Height
  int     sz;      // Data Size
  color * data;    // Data
} CANVAS;

//
// AROMA PNG Canvas Structure
//
typedef struct {
  int     w;       // Width
  int     h;       // Height
  int     s;       // Buffer Size
  byte    c;       // Channels
  byte  * r;       // Red Channel
  byte  * g;       // Green Channel
  byte  * b;       // Blue Channel
  byte  * a;       // Alpha Channel
} PNGCANVAS, * PNGCANVASP;


//
// AROMA PNG Font Canvas Structure
//
typedef struct {
  byte    loaded;    // Font is Loaded
  int     fx[96];    // Font X Positions
  byte    fw[96];    // Font Width
  byte    fh;        // Font Height
  int     w;         // Png Width
  int     h;         // Png Height
  int     s;         // Buffer Size
  byte    c;         // Channels
  byte  * d;         // Fonts Alpha Channel
} PNGFONTS;

//
// AROMA Main Configuration Structure
//
typedef struct  {
  // Colors
  color winbg;                // Window Background
  color winbg_g;              // Window Background Gradient
  color winfg;                // Window Foreground
  color winfg_gray;           // Window Foreground
  color dialogbg;             // Dialog Background
  color dialogbg_g;           // Dialog Background Gradient
  color dialogfg;             // Dialog Foreground
  color textbg;               // Text / List Background
  color textfg;               // Text / List Font Color
  color textfg_gray;          // List Grayed Font Color ( List Description )
  color controlbg;            // Control/Button Background
  color controlbg_g;          // Control/Button Background Gradient
  color controlfg;            // Control/Button Font Color
  color selectbg;             // Selected Item/Control Background
  color selectbg_g;           // Selected Item/Control Background Gradient
  color selectfg;             // Selected Item/Control Font Color
  color titlebg;              // Title Background
  color titlebg_g;            // Title Background Gradient
  color titlefg;              // Title Font Color
  color dlgtitlebg;           // Dialog Title Background
  color dlgtitlebg_g;         // Dialog Title Background Gradient
  color dlgtitlefg;           // Dialog Title Font Color
  color navbg;                // Scrollbar Color
  color navbg_g;              // Navigation Bar Background
  color scrollbar;            // Navigation Bar Background Gradient
  color border;               // Border Color
  color border_g;             // Border Color Gradient
  color progressglow;         // Progress Bar Glow Color
  
  // Property
  byte  roundsz;              // Control Rounded Size
  byte  btnroundsz;           // Button Control Rounded Size
  byte  winroundsz;           // Window Rounded Size
  
  // Transition
  byte  fadeframes;           // Number of Frame used for Fade Transition
  
  // Common Text
  /*  char  text_ok[64];          // OK
    char  text_next[64];        // Next >
    char  text_back[64];        // < Back
  
    char  text_yes[64];         // Yes
    char  text_no[64];          // No
    char  text_about[64];       // About
    char  text_calibrating[64]; // Calibration Tools
    char  text_quit[64];        // Quit
    char  text_quit_msg[128];   // Quit Message
  
    // ROM Text
    char rom_name[128];          // ROM Name
    char rom_version[128];       // ROM Version
    char rom_author[128];        // ROM Author
    char rom_device[128];        // ROM Device Name
    char rom_date[128];          // ROM Date
  */
  
  // CUSTOM KEY
  int ckey_up;
  int ckey_down;
  int ckey_select;
  int ckey_back;
  int ckey_menu;
  
  // THEME
  PNGCANVASP  theme[AROMA_THEME_CNT];
  byte        theme_9p[AROMA_THEME_CNT];
  char        themename[64];
} AC_CONFIG;

//
// AROMA Assosiative Array Structure
//
typedef struct {
  char * key;
  char * val;
} AARRAY_ITEM, * AARRAY_ITEMP;

typedef struct {
  int length;
  AARRAY_ITEMP items;
} AARRAY, * AARRAYP;

//
// AROMA ZIP Memory Structure
//
typedef struct {
  int sz;         // Data Size
  byte * data;    // Data
} AZMEM;

typedef struct {
  int     n;  //-- Count
  char ** f;  //-- Filenames
  byte  * t;  //-- Type ( 0=file, 1=dir )
} AZREADDIR, * AZREADDIRP;

//
// Math Macro
//
#define LOWORD(l) ((word)(l))
#define HIWORD(l) ((word)(((dword)(l) >> 16) & 0xFFFF))
#define MAKEDWORD(a, b) ((dword) (((word) (a)) | ((dword) ((word) (b))) << 16))

#define max(a,b) ((a>=b)?a:b)
#define min(a,b) ((a<=b)?a:b)
#define MIN(a,b) min(a,b)
#define MAX(a,b) max(a,b)
int div2ceil(int a);
int div2floor(int a);

//
// AROMA Graphic Pixel Macro
//
#define ag_r(rgb)	          ((byte) (((((word)(rgb))&0xF800))>>8) )
#define ag_g(rgb)	          ((byte) (((((word)(rgb))&0x07E0))>>3) )
#define ag_b(rgb)	          ((byte) (((((word)(rgb))&0x001F))<<3) )
#define ag_rgb(r,g,b)       ((color) ((r >> 3) << 11)| ((g >> 2) << 5)| ((b >> 3) << 0))

dword ag_rgba32(byte r, byte g, byte b, byte a);
dword ag_rgb32(byte r, byte g, byte b);
byte ag_r32(dword rgb);
byte ag_g32(dword rgb);
byte ag_b32(dword rgb);
byte ag_a32(dword rgb);
byte artNEON();

#define ag_close_r(r)       (((byte) r)>>3<<3)
#define ag_close_g(g)       (((byte) g)>>2<<2)
#define ag_close_b(b)       ag_close_r(b)
#define ag_rgbto32(rgb)     (ag_rgba32(ag_r(rgb),ag_g(rgb),ag_b(rgb),0xff))
#define ag_rgbto16(rgb)     (ag_rgb(ag_r32(rgb),ag_g32(rgb),ag_b32(rgb)))
void ag_txtxy(int * x, int * y, int maxwidth, const char * ss, byte isbig, int haltat);

byte libaroma_color_close_r(byte c);
word libaroma_rgb_to16(dword rgb);
dword libaroma_rgba(byte r, byte g, byte b, byte a);

//-- .9.png struct
typedef struct {
  int x;  //-- Strect X
  int y;  //-- Strect Y
  int w;  //-- Strect Width
  int h;  //-- Strect Height
  
  int t;  //-- Padding Top
  int l;  //-- Padding Left
  int b;  //-- Padding Bottom
  int r;  //-- Padding Right
} APNG9, *APNG9P;

//
// AROMA PNG Functions
//
byte      apng_load(PNGCANVAS * pngcanvas, char * imgname);       // Load PNG From Zip Item
void      apng_close(PNGCANVAS * pngcanvas);                            // Release PNG Memory
byte      apng_draw(CANVAS * _b, PNGCANVAS * p, int xpos, int ypos);    // Draw PNG Into Canvas
byte apng_stretch(
  CANVAS * _b,
  PNGCANVAS * p,
  int dx,
  int dy,
  int dw,
  int dh,

  int sx,
  int sy,
  int sw,
  int sh
);
byte apng9_calc(PNGCANVAS * p, APNG9P v, byte with_pad);
byte apng9_draw(
  CANVAS * _b,
  PNGCANVAS * p,
  int dx,
  int dy,
  int dw,
  int dh,
  APNG9P v,
  byte with_pad
);

//
// Customization Functions
//
AC_CONFIG * acfg();           // Get Config Structure
void        acfg_init();      // Set Default Config
void acfg_init_ex(byte themeonly);

//
//  AROMA Array Functions
//

AARRAYP   aarray_create();
char   *  aarray_get(AARRAYP a, char * key);
byte      aarray_set(AARRAYP a, char * key, char * val);
byte      aarray_del(AARRAYP a, char * key);
byte      aarray_free(AARRAYP a);

//
// AROMA Freetype Wrapper
//
byte    aft_fontready(byte isbig);
byte    aft_open();
byte    aft_close();
int     aft_kern(int c, int p, byte isbig);
int     aft_fontwidth(int c, byte isbig);
int     aft_spacewidth(byte isbig);
byte    aft_fontheight(byte isbig);
byte    aft_load(const char * source_name, int size, byte isbig, char * relativeto);
byte aft_drawfont(CANVAS * _b, byte isbig, int fpos, int xpos, int ypos, color cl, byte underline, byte bold, byte italic, byte lcd);
byte aft_isrtl(int c, byte checkleft);


//
// AROMA PNG Font Functions
//
byte      apng_loadfont(PNGFONTS * pngfont, const char * imgname);      // Load PNG Font From Zip Item
byte      apng_drawfont(CANVAS * _b, PNGFONTS * p, byte fpos,           // Draw PNG Font Into Canvas
                        int xpos, int ypos, color cl, byte underline, byte bold);
byte      apng_draw_ex(CANVAS * _b, PNGCANVAS * p, int xpos,            // Draw PNG Font Into Canvas
                       int ypos, int sxpos, int sypos, int sw, int sh);            // With Extra Arguments

//
// AROMA Graphic Function
//
void      ag_setcaret(int x, int y, int h);
byte      ag_isfreetype(byte isbig);
byte      ag_fontready(byte isbig);
CANVAS  * agc();          // Get Main AROMA Graph Canvas
byte      ag_init();      // Init AROMA Graph and Framebuffers
byte      ag_close_thread(); // Close Graph Thread
void      ag_close();     // Close AROMA Graph and Framebuffers
void      ag_changecolorspace(int r, int g, int b, int a); // Change Color Space

void      ag_sync();                        // Sync Main Canvas with Framebuffer
int       agw();                            // Get Display X Resolution
int       agh();                            // Get Display Y Resolution
int       agdp();                           // Get Device Pixel Size (WVGA = 3, HVGA = 2)
void      set_agdp(int dp);                 // Force Graphic Device Pixel Size
void      ag_sync_fade(int frame);          // Transition Sync - Async
void      ag_sync_fade_wait(int frame);     // Transition Sync - Sync
void      ag_sync_force();                  // Force to Sync
void      ag_setbusy();                     // Set Display to show Please Wait Progress
void      ag_setbusy_withtext(char * text); // Display Busy Progress with Custom Text

//
// AROMA Canvas Functions
//
void ag_takescreenshoot();
void ag_canvas(CANVAS * c, int w, int h); // Create Canvas
void ag_ccanvas(CANVAS * c);              // Release Canvas
void ag_blank(CANVAS * c);                // Set Blank into Canvas memset(0)


//
// AROMA Canvas Manipulation Functions
//
color  *  agxy(CANVAS * _b, int x, int y);                            // Get Pixel Pointer
byte      ag_setpixel(CANVAS * _b, int x, int y, color cl);           // Set Pixel Color
byte      ag_subpixel(CANVAS * _b, int x, int y, color cl, byte l);   // Set Pixel Color with Opacity


//
// AROMA Canvas Drawing Functions
//
byte      ag_rect(CANVAS * _b, int x, int y, int w, int h, color cl); // Draw Solid Rectangle
byte      ag_rectopa(CANVAS * _b, int x, int y, int w, int h,         // Draw Solid Rectangle with Opacity
                     color cl, byte l);
byte      ag_draw(CANVAS * dc, CANVAS * sc, int dx, int dy);          // Draw Canvas to Canvas
byte      ag_draw_ex(CANVAS * dc, CANVAS * sc, int dx, int dy,        // Draw Canvas to Canvas + Extra Arguments
                     int sx, int sy, int sw, int sh);
byte      ag_roundgrad(CANVAS * _b, int x, int y, int w, int h,       // Draw Rounded & Gradient Rectangle
                       color cl1, color cl2, int roundsz);
byte      ag_roundgrad_ex(CANVAS * _b, int x, int y, int w, int h,    // Draw Rounded & Gradient Rectangle
                          color cl1, color cl2, int roundsz, byte tlr,              // With Extra Arguments
                          byte trr, byte blr, byte brr);
void ag_dither(byte * qe, int qp, int qx, int dthx, int dthy, int dthw, int dthh, byte r, byte g, byte b);
color ag_dodither(int x, int y, dword col);
color ag_dodither_rgb(int x, int y, byte sr, byte sg, byte sb);

//
// AROMA Color Calculator Functions
//
color     ag_subpixelget(CANVAS * _b, int x, int y, color cl, byte l); // Calculate Color Opacity with Canvas Pixel

#define ag_calculatealpha(d,s,a) libaroma_alpha(d,s,a)
#define ag_calculatealphaTo32(d,s,a) libaroma_alpha32(d,s,a)
color     strtocolor(char * c);                                       // Convert String Hex Color #fff,#ffffff to color
dword     ag_calchighlight(color c1, color c2);
dword     ag_calcpushlight(color c1, color c2);
color     ag_calpushad(color c_g);
color     ag_calculatecontrast(color c, float intensity);

//
// AROMA PNG Font Functions
//
int   ag_fontheight(byte isbig);                      // Get Font Height
byte  ag_loadsmallfont(char * fontname, byte is_freetype, char * relativeto); // Load Small Font From Zip
byte  ag_loadbigfont(char * fontname, byte is_freetype, char * relativeto); // Load Big Font From Zip
byte  ag_loadfixedfont(char * fontname, byte is_freetype, char * relativeto);
void  ag_closefonts();                                // Release Big & Small Fonts
byte ag_drawchar_ex2(CANVAS * _b, int x, int y, int c, color cl, byte isbig, byte underline, byte bold, byte italic, byte lcd);
byte  ag_drawchar(CANVAS * _b, int x, int y, int c,  // Draw Character into Canvas
                  color cl, byte isbig);
byte ag_drawchar_ex(CANVAS * _b, int x, int y, int c, color cl, byte isbig, byte underline, byte bold, byte italic);
byte  ag_text(CANVAS * _b, int maxwidth, int x, int y, // Draw String into Canvas
              const char * s, color cl, byte isbig);
byte  ag_textf(CANVAS * _b, int maxwidth, int x, int y, // Draw String into Canvas
               const char * s, color cl, byte isbig);        // Force Default Color

byte ag_text_ex(CANVAS * _b, int maxwidth, int x, int y, // Draw String into Canvas
                const char * s, color cl_def, byte isbig,     // With Extra Arguments
                byte forcecolor);
int   ag_txtheight(int maxwidth,                      // Calculate String Height to be drawn
                   const char * s, byte isbig);
int   ag_txtwidth(const char * s, byte isbig);        // Calculate String Width to be drawn
int  ag_tabwidth(int x, byte isbig);
byte ag_fontwidth(int c, byte isbig);               // Calculate font width for 1 character
byte ag_texts(CANVAS * _b, int maxwidth, int x, int y, const char * s, color cl_def, byte isbig);
byte ag_textfs(CANVAS * _b, int maxwidth, int x, int y, const char * s, color cl_def, byte isbig);
byte ag_text_exl(CANVAS * _b, int maxwidth, int x, int y, const char * s, color cl_def, byte isbig, byte forcecolor, byte multiline);

//
// AROMA Zip Functions
//
byte      az_init(const char * filename);                               // Init Zip Archive
void      az_close();                                                   // Release Zip Archive
byte      az_readmem(AZMEM * out, const char * zpath, byte bytesafe);   // Read Zip Item into Memory
byte      az_extract(const char * zpath, const char * dest);            // Extract Zip Item into Filesystem
void        az_readdir_free(AZREADDIRP r);
AZREADDIRP  az_readdir(char * path);

//**********[ AROMA LOGGING ]**********//
#define _AROMA_DEBUG_TAG "aroma"
#ifndef _AROMA_NODEBUG
#define LOGS(...) dprintf(1, _AROMA_DEBUG_TAG "/s: " __VA_ARGS__)
#define LOGE(...) dprintf(1, _AROMA_DEBUG_TAG "/e: " __VA_ARGS__)
#define LOGW(...) dprintf(1, _AROMA_DEBUG_TAG "/w: " __VA_ARGS__)
#define LOGI(...) dprintf(1, _AROMA_DEBUG_TAG "/i: " __VA_ARGS__)
#define LOGV(...) dprintf(1, _AROMA_DEBUG_TAG "/v: " __VA_ARGS__)
#define LOGD(...) dprintf(1, _AROMA_DEBUG_TAG "/d: " __VA_ARGS__)
#else
#define LOGS(...) dprintf(1, _AROMA_DEBUG_TAG "/s: " __VA_ARGS__)
#define LOGE(...) dprintf(1, _AROMA_DEBUG_TAG "/e: " __VA_ARGS__)
#define LOGW(...) /**/
#define LOGI(...) /**/
#define LOGV(...) /**/
#define LOGD(...) /**/
#endif
#define ALOGT(...)
#define ALOGRT(...)

//**********[ AROMA LOGGING - LIBAROMA STYLE ]**********//
#define ALOGE(...) \
  dprintf(1, _AROMA_DEBUG_TAG "[E] " __VA_ARGS__); \
  dprintf(1, "\n");
#define ALOGI(...) \
  dprintf(1, _AROMA_DEBUG_TAG "[I] " __VA_ARGS__); \
  dprintf(1, "\n");
#define ALOGS(...) \
  dprintf(1, _AROMA_DEBUG_TAG "[S] " __VA_ARGS__); \
  dprintf(1, "\n");
#define ALOGW(...) \
  dprintf(1, _AROMA_DEBUG_TAG "[W] " __VA_ARGS__); \
  dprintf(1, "\n");
#define ALOGV(...) \
  dprintf(1, _AROMA_DEBUG_TAG "[V] " __VA_ARGS__); \
  dprintf(1, "\n");

#include "aroma/fb/engine.h"
#include "aroma/fb/fb.h"
#endif // __AROMA_COMMON_H__
