/*****************************************************************************
*   @file        sensor_tile_board.h
*   @Author      Firmware Team
*   @date        02 Feb 2018 - 04.15pm
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
02 Feb 2018 - 04.15pm:
    By : ...
        Rev 1.0 : sensor_tile_board.h file template created.
 -----------------------------------------------------------------------------

===============================================================================


===============================================================================
******************************************************************************/



/* Recursive include guard */
#ifndef 	sensor_tile_board_h
	#define sensor_tile_board_h


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
#include "board.h"
#include "my_types.h"



/***
 * Exported define ------------------------------------------------------------
***/
#define LSM6DSL_BUS_HANDLE      (&hspi1)


/***
 * Exported types -------------------------------------------------------------
***/
/***
 * Exported enums -------------------------------------------------------------
***/



/***
 * Exported constants ---------------------------------------------------------
***/
/***
 * Exported Structures --------------------------------------------------------
***/
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
extern device_info_t   lsm6dsl_handle;
extern device_info_t   lsm303agr_handle;
extern device_info_t   lps22h_handle;


/***
 * Exported functions declaration ---------------------------------------------
***/
RETURN_TYPE_E   sensor_io_init  (BSP_DEVICE_ID_E    bsp_id);
RETURN_TYPE_E   sensor_io_write (device_info_t * dev_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng);
RETURN_TYPE_E   sensor_io_read  (device_info_t * dev_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng);
//void            sensor_io_write_cb  (DMA_XFER_CB_E  cb_type);
//void            sensor_io_read_cb   (DMA_XFER_CB_E  cb_type);
RETURN_TYPE_E  sensor_io_spi_write  (comm_bus_info_t * bus_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng);
RETURN_TYPE_E  sensor_io_spi_read   (comm_bus_info_t * bus_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng);

comm_bus_info_t * get_bus_peripheral_from_id        (COMM_BUS_ID_E   bus_id);
comm_bus_info_t * get_device_handle_from_bus_handle (void    *   bus_handle);

/***
 * Exported Task declaration --------------------------------------------------
***/






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
