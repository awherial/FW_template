/*****************************************************************************
*   @file        board.h
*   @Author      Firmware Team
*   @date        02 Feb 2018 - 04.21pm
*   @project
*   @module
*   @version     v1.0.0
*   @brief
*
*
*
*
*******************************************************************************
* Copyright (c) 2011, Ducere Technologies. All rights reserved.
* Unauthorised copying/redistribution and  its use in  source and binary forms,
* with or without modification, is not permitted. Proprietary and confidential.
*
* Attention:
*   All  information   contained  herein  is,  and   remains  the  property  of
*   Ducere     Technologies     Private     Limited,     Hyderabad,      India.
*   The intellectual and technical concepts contained herein are proprietary to
*   Ducere   Technologies  and  may  be  covered by patents in process, and are
*   protected   by   trade   secret   or   copyright law. Dissemination of this
*   information   or  reproduction  of  this material  is  strictly  forbidden.
******************************************************************************/


/********************* INTERFACE CHANGE LIST **********************************

	This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

===============================================================================
02 Feb 2018 - 04.21pm:
    By : ...
        Rev 1.0 : board.h file template created.
 -----------------------------------------------------------------------------

===============================================================================


===============================================================================
******************************************************************************/



/* Recursive include guard */
#ifndef 	board_h
	#define board_h


#ifdef __cplusplus
 extern "C" {
#endif


/******************************************************************************
* Includes
******************************************************************************/
/***
 * Standard C Library Includes ------------------------------------------------
***/
#include <stdint.h>

/***
 * Third Party Library Includes -----------------------------------------------
***/
/***
 * Project Library Includes ---------------------------------------------------
***/
#include "my_types.h"



/***
 * Exported define ------------------------------------------------------------
***/
// ============================================
// Select board
// ============================================
#if     1

    #include "sensor_tile_wrapper.h"

#endif

/***
 * Exported types -------------------------------------------------------------
***/
/***
 * Exported enums -------------------------------------------------------------
***/
typedef enum COMM_BUS_E {

    INVALID_BUS ,
    SPI         ,
    I2C         ,
    UART        ,
    USART       ,
    USB         ,

} COMM_BUS_E;

typedef enum  {

    SPI_1   ,
    SPI_2   ,
    SPI_3   ,

    I2C_1   ,
    I2C_2   ,
    I2C_3   ,

    // todo
        // for ohter peripherals

} COMM_BUS_ID_E;

typedef enum  {

    DEV_NOT_PREESNT,
    DEV_NOT_CONFIGURED,
    DEV_CONFIGURED,
    DEV_STANDBY,
    DEV_SLEEP_MODE,
    DEV_READY,
    DEV_RESET,
    DEV_BUSY_TX,
    DEV_BUSY_RX,
    DEV_IDLE,

} DEV_STATE_E;

typedef enum  {

    BUS_DEV_UN_INITIALIZED,
    BUS_DEV_INITIALIZED,
    BUS_IDLE        ,
    BUS_BUSY_TX     ,
    BUS_BUSY_RX     ,
    BUS_DMA_TX      ,
    BUS_DMA_RX      ,

} COMM_BUS_STATE_E;


typedef enum  {

    BLOCKING_MODE       = 0x00,
    NON_BLOCKING_MODE   = 0x01,

} DEV_ACCESS_MODE_E;

///**
//  * @brief  HAL DMA Callback ID structure definition
//  */
//typedef enum
//{
//  HAL_DMA_XFER_CPLT_CB_ID          = 0x00,    /*!< Full transfer     */
//  HAL_DMA_XFER_HALFCPLT_CB_ID      = 0x01,    /*!< Half transfer     */
//  HAL_DMA_XFER_ERROR_CB_ID         = 0x02,    /*!< Error             */
//  HAL_DMA_XFER_ABORT_CB_ID         = 0x03,    /*!< Abort             */
//  HAL_DMA_XFER_ALL_CB_ID           = 0x04     /*!< All               */
//
//}HAL_DMA_CallbackIDTypeDef;

typedef enum  {

    DMA_XFER_COMPLETE_CB     = 0x00,
    DMA_XFER_HALF_CMPLT_CB   = 0x01,
    DMA_XFER_ERROR_CB        = 0x02,
    DMA_XFER_ABORT_CB        = 0x03,
    DMA_XFER_ANY_CB          = 0x04,

} DMA_XFER_CB_E;




/***
 * Exported constants ---------------------------------------------------------
***/
/***
 * Exported Structures --------------------------------------------------------
***/
//typedef struct  {
//
//    //
//    DEV_ACCESS_MODE_E   acc_type;
//
//    void                (*fp_cb) ( );   // callback function pointer
//
//
//} DEVICE_RW_PARAMS_T;


typedef struct  {

    DEV_STATE_E         dev_state;      // device id in the present BSP
    // Board Specific device ID
    COMM_BUS_E          bus_type;       // type of bus on which the device is connected
    COMM_BUS_ID_E       bus_id;         // bus id or instance
    BSP_DEVICE_ID_E     dev_id;         // device id in the present BSP


    // below is the pointer to the communication peripheral as per the underlying uc HAL driver
    void    *           bus_handle;

    void                (*fp_dev_aquire ) ();     // will take care of chip-select
    void                (*fp_dev_release) ();    // will take care of chip-select

    uint8_t             dev_address;    // I2C device ID
    uint8_t             isInitialized;  // Sensor setup done.
    uint8_t             isEnabled;      // Sensor ON.
    uint8_t             dummy1;         // for maintaining word boundry

    uint32_t            sync_flag_write;
    uint32_t            sync_flag_read;

    void                (*fp_dma_write_cb) (DMA_XFER_CB_E );
    void                (*fp_dma_read_cb ) (DMA_XFER_CB_E );

    /* Identity */
    uint8_t             who_am_i;       // indicates device family type

} device_info_t;




typedef struct  {

    COMM_BUS_STATE_E    bus_state;
    // Board Specific device ID
    COMM_BUS_E          bus_type;
    COMM_BUS_ID_E       bus_id;
    BSP_DEVICE_ID_E     dev_id;


    // below is the pointer to the communication peripheral as per the underlying uc HAL driver
    void    *           bus_handle;

    void                (*fp_bus_aquire ) ();     // will take care and mutex
    void                (*fp_bus_release) ();    // will take care and mutex

    uint8_t             dev_address;    // I2C device ID
    uint8_t             isInitialized;  // peripheral config done.
    uint8_t             isEnabled;      // peripheral ON.
    uint8_t             dummy1;         // for maintaining word boundry

    uint32_t            sync_flag_write;
    uint32_t            sync_flag_read;

    void                (*fp_dma_write_cb) (DMA_XFER_CB_E );
    void                (*fp_dma_read_cb ) (DMA_XFER_CB_E );

} comm_bus_info_t;





/***
 * Exported Unions ------------------------------------------------------------
***/
/***
 * Exported typedef -----------------------------------------------------------
***/
/***
 * Exported macros ------------------------------------------------------------
***/
/***
 * Exported Variables declaration ---------------------------------------------
***/
/***
 * Exported functions declaration ---------------------------------------------
***/
void    sensor_io_write_cb  (DMA_XFER_CB_E  cb_type);
void    sensor_io_read_cb   (DMA_XFER_CB_E  cb_type);


/***
 * Exported Task declaration --------------------------------------------------
***/






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
//                                     // communication peripheral struct ptr,
//                                     // |    bufptr,   buf_size, timeout_msecs
//    RETURN_TYPE_E       (*fp_write) (void *, uint8_t *, uint16_t, uint32_t);    // blocking write
//    RETURN_TYPE_E       (*fp_read ) (void *, uint8_t *, uint16_t, uint32_t);    // blocking read
//
//    RETURN_TYPE_E       (*fp_write_nb) (void *, uint8_t *, uint16_t, (*fp_cb) ( ));    // non-blocking write
//    RETURN_TYPE_E       (*fp_read_nb ) (void *, uint8_t *, uint16_t, (*fp_cb) ( ));    // non-blocking read
