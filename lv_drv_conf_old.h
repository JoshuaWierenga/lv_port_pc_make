/*********************
 * DELAY INTERFACE
 *********************/
 // CAN'T FIND
#define LV_DRV_DELAY_INCLUDE  <stdint.h>            /*Dummy include by default*/
// CAN'T FIND
#define LV_DRV_DELAY_US(us)  /*delay_us(us)*/       /*Delay the given number of microseconds*/
// CAN'T FIND
#define LV_DRV_DELAY_MS(ms)  /*delay_ms(ms)*/       /*Delay the given number of milliseconds*/

/*********************
 * DISPLAY INTERFACE
 *********************/

/*------------
 *  Common
 *------------*/
// CAN'T FIND
#define LV_DRV_DISP_INCLUDE         <stdint.h>           /*Dummy include by default*/
// CAN'T FIND
#define LV_DRV_DISP_CMD_DATA(val)  /*pin_x_set(val)*/    /*Set the command/data pin to 'val'*/
// CAN'T FIND
#define LV_DRV_DISP_RST(val)       /*pin_x_set(val)*/    /*Set the reset pin to 'val'*/

/*---------
 *  SPI
 *---------*/
// CAN'T FIND
#define LV_DRV_DISP_SPI_CS(val)          /*spi_cs_set(val)*/     /*Set the SPI's Chip select to 'val'*/
// CAN'T FIND
#define LV_DRV_DISP_SPI_WR_BYTE(data)    /*spi_wr(data)*/        /*Write a byte the SPI bus*/
// CAN'T FIND
#define LV_DRV_DISP_SPI_WR_ARRAY(adr, n) /*spi_wr_mem(adr, n)*/  /*Write 'n' bytes to SPI bus from 'adr'*/

/*------------------
 *  Parallel port
 *-----------------*/
// CAN'T FIND
#define LV_DRV_DISP_PAR_CS(val)          /*par_cs_set(val)*/   /*Set the Parallel port's Chip select to 'val'*/
// CAN'T FIND
#define LV_DRV_DISP_PAR_SLOW             /*par_slow()*/        /*Set low speed on the parallel port*/
// CAN'T FIND
#define LV_DRV_DISP_PAR_FAST             /*par_fast()*/        /*Set high speed on the parallel port*/
// CAN'T FIND
#define LV_DRV_DISP_PAR_WR_WORD(data)    /*par_wr(data)*/      /*Write a word to the parallel port*/
// CAN'T FIND
#define LV_DRV_DISP_PAR_WR_ARRAY(adr, n) /*par_wr_mem(adr,n)*/ /*Write 'n' bytes to Parallel ports from 'adr'*/

/***************************
 * INPUT DEVICE INTERFACE
 ***************************/

/*----------
 *  Common
 *----------*/
// CAN'T FIND
#define LV_DRV_INDEV_INCLUDE     <stdint.h>             /*Dummy include by default*/
// CAN'T FIND
#define LV_DRV_INDEV_RST(val)    /*pin_x_set(val)*/     /*Set the reset pin to 'val'*/
// CAN'T FIND
#define LV_DRV_INDEV_IRQ_READ    0 /*pn_x_read()*/      /*Read the IRQ pin*/

/*---------
 *  SPI
 *---------*/
// CAN'T FIND
#define LV_DRV_INDEV_SPI_CS(val)            /*spi_cs_set(val)*/     /*Set the SPI's Chip select to 'val'*/
// CAN'T FIND
#define LV_DRV_INDEV_SPI_XCHG_BYTE(data)    0 /*spi_xchg(val)*/     /*Write 'val' to SPI and give the read value*/

/*---------
 *  I2C
 *---------*/
// CAN'T FIND
#define LV_DRV_INDEV_I2C_START              /*i2c_start()*/       /*Make an I2C start*/
// CAN'T FIND
#define LV_DRV_INDEV_I2C_STOP               /*i2c_stop()*/        /*Make an I2C stop*/
// CAN'T FIND
#define LV_DRV_INDEV_I2C_RESTART            /*i2c_restart()*/     /*Make an I2C restart*/
// CAN'T FIND
#define LV_DRV_INDEV_I2C_WR(data)           /*i2c_wr(data)*/      /*Write a byte to the I1C bus*/
// CAN'T FIND
#define LV_DRV_INDEV_I2C_READ(last_read)    0 /*i2c_rd()*/        /*Read a byte from the I2C bud*/


/*********************
 *  DISPLAY DRIVERS
 *********************/

/*-------------------
 *  SDL
 *-------------------*/

// CAN'T FIND
/* Scale window by this factor (useful when simulating small screens) */
#  define SDL_ZOOM        1

// CAN'T FIND
// Is this in LV_SDL_RENDER_MODE now?
/* Used to test true double buffering with only address changing.
 * Use 2 draw buffers, bith with SDL_HOR_RES x SDL_VER_RES size*/
#  define SDL_DOUBLE_BUFFERED 0

// CAN'T FIND
// Is this LV_SDL_BUF_COUNT now?
/*Open two windows to test multi display support*/
#  define SDL_DUAL_DISPLAY            0

// CAN'T FIND
/* Window Title  */
#  define SDL_WINDOW_TITLE "TFT Simulator"
#endif

/*----------------------------
 *  Native Windows (win32drv)
 *---------------------------*/

#if USE_WIN32DRV
// CAN'T FIND
/* Scale window by this factor (useful when simulating small screens) */
#  define WIN32DRV_MONITOR_ZOOM        1
#endif
