#include "lv_demo_conf.h"

/*====================
   COLOR SETTINGS
 *====================*/

// CAN'T FIND
/*Enable more complex drawing routines to manage screens transparency.
 *Can be used if the UI is above an other layer, e.g. an OSD menu or video player.
 *Requires `LV_COLOR_DEPTH = 32` colors and the screen's `bg_opa` should be set to non LV_OPA_COVER value*/
#define LV_COLOR_SCREEN_TRANSP    0

// CAN'T FIND
/*Images pixels with this color will not be drawn if they are  chroma keyed)*/
#define LV_COLOR_CHROMA_KEY    lv_color_hex(0x00ff00)         /*pure green*/

/*====================
   HAL SETTINGS
 *====================*/

// UNUSED https://github.com/lvgl/lvgl/issues/4594
/*Use a custom tick source that tells the elapsed time in milliseconds.
 *It removes the need to manually update the tick with `lv_tick_inc()`)*/
#define LV_TICK_CUSTOM     0
#if LV_TICK_CUSTOM
#define LV_TICK_CUSTOM_INCLUDE  "Arduino.h"         /*Header for the system time function*/
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())     /*Expression evaluating to current system time in ms*/
#endif   /*LV_TICK_CUSTOM*/

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/*-------------
 * Drawing
 *-----------*/

// CAN'T FIND
/*Maximum buffer size to allocate for rotation. Only used if software rotation is enabled in the display driver.*/
#define LV_DISP_ROT_MAX_BUF         (10*1024)
/*-------------
 * GPU
 *-----------*/

// UNUSED https://github.com/lvgl/lvgl/issues/4594
/*Use STM32's DMA2D (aka Chrom Art) GPU*/
#define LV_USE_GPU_STM32_DMA2D  0
#if LV_USE_GPU_STM32_DMA2D
/*Must be defined to include path of CMSIS header of target processor
e.g. "stm32f769xx.h" or "stm32f429xx.h"*/
#define LV_GPU_DMA2D_CMSIS_INCLUDE
#endif

// UNUSED https://github.com/lvgl/lvgl/issues/4594
// Is this LV_USE_DRAW_PXP now?
/*Use NXP's PXP GPU iMX RTxxx platforms*/
#define LV_USE_GPU_NXP_PXP      0
#if LV_USE_GPU_NXP_PXP
/*1: Add default bare metal and FreeRTOS interrupt handling routines for PXP (lv_gpu_nxp_pxp_osa.c)
 *   and call lv_gpu_nxp_pxp_init() automatically during lv_init(). Note that symbol FSL_RTOS_FREE_RTOS
 *   has to be defined in order to use FreeRTOS OSA, otherwise bare-metal implementation is selected.
 *0: lv_gpu_nxp_pxp_init() has to be called manually before lv_init()
 */
#define LV_USE_GPU_NXP_PXP_AUTO_INIT 0
#endif

// UNUSED https://github.com/lvgl/lvgl/issues/4594
// Is this LV_USE_DRAW_VGLITE now?
/*Use NXP's VG-Lite GPU iMX RTxxx platforms*/
#define LV_USE_GPU_NXP_VG_LITE   0

/*-------------
 * Others
 *-----------*/

// UNUSED https://github.com/lvgl/lvgl/issues/4594
#define LV_USE_USER_DATA      1

// UNUSED https://github.com/lvgl/lvgl/issues/4594
/*Garbage Collector settings
 *Used if lvgl is binded to higher level language and the memory is managed by that language*/
#define LV_ENABLE_GC 0
#if LV_ENABLE_GC != 0
#  define LV_GC_INCLUDE "gc.h"                           /*Include Garbage Collector related things*/
#endif /*LV_ENABLE_GC*/

/*=====================
 *  COMPILER SETTINGS
 *====================*/

// CAN'T FIND
/*Prefix variables that are used in GPU accelerated operations, often these need to be placed in RAM sections that are DMA accessible*/
#define LV_ATTRIBUTE_DMA

// CAN'T FIND
/*Extend the default -32k..32k coordinate range to -4M..4M by using int32_t for coordinates instead of int16_t*/
#define LV_USE_LARGE_COORD  0

/*==================
 *   FONT USAGE
 *===================*/

// UNUSED https://github.com/lvgl/lvgl/issues/4594
/*Demonstrate special features*/
#define LV_FONT_MONTSERRAT_12_SUBPX      1

// CAN'T FIND, both still in Kconfig and LV_FONT_SUBPX_BGR still in lv_test_conf_full.h as well
/*Enable subpixel rendering*/
#define LV_USE_FONT_SUBPX       1
#if LV_USE_FONT_SUBPX
/*Set the pixel order of the display. Physical order of RGB channels. Doesn't matter with "normal" fonts.*/
#define LV_FONT_SUBPX_BGR       0  /*0: RGB; 1:BGR order*/
#endif

/*=================
 *  TEXT SETTINGS
 *=================*/

// UNUSED https://github.com/lvgl/lvgl/issues/4594
/*The control character to use for signalling text recoloring.*/
#define LV_TXT_COLOR_CMD "#"

/*==================
 *  WIDGET USAGE
 *================*/

#define LV_USE_ROLLER       1   /*Requires: lv_label*/
#if LV_USE_ROLLER
// CAN'T FIND, still in Kconfig
#  define LV_ROLLER_INF_PAGES       7   /*Number of extra "pages" when the roller is infinite*/
#endif

/*==================
 * EXTRA COMPONENTS
 *==================*/

/*-----------
 * Widgets
 *----------*/
// UNUSED https://github.com/lvgl/lvgl/issues/4594
#define LV_USE_COLORWHEEL   1

// CAN'T FIND
#define LV_USE_METER        1

/*---------------------
 * 3rd party libraries
 *--------------------*/

/*FreeType library*/
#define LV_USE_FREETYPE 0
#if LV_USE_FREETYPE
    /*Memory used by FreeType to cache characters [bytes] (-1: no caching)*/
    #define LV_FREETYPE_CACHE_SIZE (16 * 1024)
    #if LV_FREETYPE_CACHE_SIZE >= 0
        // CAN'T FIND
        /* 1: bitmap cache use the sbit cache, 0:bitmap cache use the image cache. */
        /* sbit cache:it is much more memory efficient for small bitmaps(font size < 256) */
        /* if font size >= 256, must be configured as image cache */
        #define LV_FREETYPE_SBIT_CACHE 0
    #endif
#endif
