
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
//static void user_image_demo();
static void hal_init(void);

/**********************
 *  STATIC VARIABLES
 **********************/
static int32_t monitor_hor_res = -1;
static int32_t monitor_ver_res = -1;
#if LV_USE_WINDOWS
static wchar_t *window_title = NULL;
#else
static char *window_title = NULL;
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#if 0
static void user_image_demo()
{
  lv_obj_t * img = lv_gif_create(lv_scr_act());
  lv_gif_set_src(img, "A:lvgl/examples/libs/gif/bulb.gif");
  lv_obj_align(img, LV_ALIGN_BOTTOM_RIGHT, -20, -20);

  lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 5);
    lv_color_t fg_color = lv_palette_darken(LV_PALETTE_BLUE, 4);

    lv_obj_t * qr = lv_qrcode_create(lv_scr_act(), 150, fg_color, bg_color);

    /*Set data*/
    const char * data = "https://lvgl.io";
    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_center(qr);

    /*Add a border with bg_color*/
    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);

    /*Create a font*/
    static lv_ft_info_t info;
    /*FreeType uses C standard file system, so no driver letter is required.*/
    info.name = "./lvgl/examples/libs/freetype/Lato-Regular.ttf";
    info.weight = 24;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;
    if(!lv_ft_font_init(&info)) {
        LV_LOG_ERROR("create failed.");
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, info.font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello world\nI'm a font created with FreeType");
    lv_obj_set_pos(label, 10, 10);

    lv_obj_t *  img1 = lv_img_create(lv_scr_act());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    lv_img_set_src(img1, "A:lvgl/examples/libs/png/wink.png");
    lv_obj_align(img1, LV_ALIGN_LEFT_MID, 20, 0);

    lv_obj_t * wp;

    wp = lv_img_create(lv_scr_act());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    lv_img_set_src(wp, "A:lvgl/examples/libs/sjpg/small_image.sjpg");
    lv_obj_align(wp, LV_ALIGN_RIGHT_MID, -20, 0);

    lv_obj_t * img2 = lv_img_create(lv_scr_act());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    lv_img_set_src(img2, "A:lvgl/examples/libs/sjpg/lv_example_jpg.jpg");
    //lv_obj_center(img);
    lv_obj_align(img2, LV_ALIGN_TOP_RIGHT, -20, 20);

    lv_obj_t * img3 = lv_img_create(lv_scr_act());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
#if LV_COLOR_DEPTH == 32
    lv_img_set_src(img3, "A:lvgl/examples/libs/bmp/example_32bit.bmp");
#elif LV_COLOR_DEPTH == 16
    lv_img_set_src(img, "A:lvgl/examples/libs/bmp/example_16bit.bmp");
#endif
    lv_obj_align(img3, LV_ALIGN_BOTTOM_MID, 0, -20);

    lv_obj_t * img4 = lv_img_create(lv_scr_act());
    lv_img_set_src(img4, "A:lvgl/examples/libs/ffmpeg/ffmpeg.png");
    lv_obj_align(img4, LV_ALIGN_BOTTOM_LEFT, 20, -20);

    lv_obj_t * player = lv_ffmpeg_player_create(lv_scr_act());
    lv_ffmpeg_player_set_src(player, "./lvgl/examples/libs/ffmpeg/birds.mp4");
    lv_ffmpeg_player_set_auto_restart(player, true);
    lv_ffmpeg_player_set_cmd(player, LV_FFMPEG_PLAYER_CMD_START);
    lv_obj_align(player, LV_ALIGN_TOP_MID, 0, 20);
}
#endif

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  monitor_hor_res = 1024;
  monitor_ver_res = 768;
#if LV_USE_WINDOWS
  window_title = L"LVGL Demo";
#else
  window_title = "LVGL Demo";
#endif

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

  /*add your ui here, if using demos make sure the appropriate guard is defined*/

  // Switch demo by updating the "DEMO USAGE" section in lv_conf.h
  #if LV_USE_DEMO_BENCHMARK
  lv_demo_benchmark();
  #elif LV_USE_DEMO_KEYPAD_AND_ENCODER
  lv_demo_keypad_encoder();
  #elif LV_USE_DEMO_MUSIC
  lv_demo_music();
  #elif LV_USE_DEMO_STRESS
  lv_demo_stress();
  #elif LV_USE_DEMO_WIDGETS
  lv_demo_widgets();
  #else
  //user_image_demo();
  my_gui(); /*replace this with your gui*/
  #endif

  // TODO: Move to hal_init/tick_thread?
  while(1) {
    lv_task_handler();
  }

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void)
{
#if LV_USE_SDL
  lv_display_t *display = lv_sdl_window_create(monitor_hor_res, monitor_ver_res);

  lv_group_t *g = lv_group_create();
  lv_group_set_default(g);

  /* create input devices */
  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
  lv_indev_t *keyboard = lv_sdl_keyboard_create();

  /* register input devices */
  lv_indev_set_group(mouse, g);
  lv_indev_set_group(mousewheel, g);
  lv_indev_set_group(keyboard, g);

  lv_sdl_window_set_title(display, window_title);

  // TODO: Use lv_sdl_window_set_resizeable?
#elif LV_USE_WINDOWS
  lv_display_t *display = lv_windows_create_display(window_title, monitor_hor_res, monitor_ver_res, 100, false, false);

  lv_group_t *g = lv_group_create();
  lv_group_set_default(g);

  /* create input devices */
  lv_indev_t *mouse = lv_windows_acquire_pointer_indev(display);
  lv_indev_t *mousewheel = lv_windows_acquire_keypad_indev(display);
  lv_indev_t *keyboard = lv_windows_acquire_encoder_indev(display);

  /* register input devices */
  lv_indev_set_group(mouse, g);
  lv_indev_set_group(mousewheel, g);
  lv_indev_set_group(keyboard, g);
#elif LV_USE_X11
  // TODO: Fix warning when using on screen keyboard on both button press and release(so four errors total, F, 3, F, 3)
  // draw_letter: lv_draw_letter: glyph dsc. not found for U+FE8F lv_draw_label.c:380
  // draw_letter: lv_draw_letter: glyph dsc. not found for U+FE83 lv_draw_label.c:380
  // TODO: Fix crash during closing
  // lv_display_set_buffers: Asserted at expression: buf1 != NULL Null buffer lv_display.c:401
  lv_display_t *display = lv_x11_window_create(window_title, monitor_hor_res, monitor_ver_res);
  lv_x11_inputs_create(display, NULL);
#endif

// TODO: Readd theme and/or custom mouse?
#if 0
#if LV_USE_SDL || LV_USE_X11
  /* Set diplay theme */
  /* TODO: Fix LV_USE_THEME_MONO on linux SDL and use on all targets? */
#if LV_USE_THEME_MONO
  lv_theme_t * th = lv_theme_mono_init(disp, LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
#elif LV_USE_THEME_DEFAULT
  lv_theme_t * th = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
#endif

  lv_disp_set_theme(disp, th);
#endif

#if LV_USE_SDL || LV_USE_X11

  // TODO: Support this with win32drv? Currently it results in two mouse cursors
  /* Set a cursor for the mouse */
  LV_IMG_DECLARE(mouse_cursor_icon);                   /*Declare the image file.*/
  lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor*/
  lv_img_set_src(cursor_obj, &mouse_cursor_icon);      /*Set the image source*/
  lv_indev_set_cursor(mouse_indev, cursor_obj);        /*Connect the image  object to the driver*/
#endif
#endif
}
