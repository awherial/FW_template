/*****************************************************************************
*   @file        sensor_tile_wrapper.h
*   @Author      Firmware Team
*   @date        05 Feb 2018 - 02:39pm
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
05 Feb 2018 - 02:39pm:
    By : ...
        Rev 1.0 : sensor_tile_wrapper.h file template created.
 -----------------------------------------------------------------------------

===============================================================================


===============================================================================
******************************************************************************/



/* Recursive include guard */
#ifndef 	sensor_tile_wrapper_h
	#define sensor_tile_wrapper_h


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
/***
 * Exported types -------------------------------------------------------------
***/
/***
 * Exported enums -------------------------------------------------------------
***/
// All peripherals on board
typedef enum {

    LSM6DSL_DEVICE_ID		= 0x01,
    LSM303AGR_DEVICE_ID	    = 0x02,
    LPS_22H_DEVICE_ID		= 0x03,

} BSP_DEVICE_ID_E;

typedef enum  {

    LSM6DSL_SYNC_READ_FLAG      = 0x0001,
    LSM6DSL_SYNC_WRITE_FLAG     = 0x0002,

    LSM303AGR_SYNC_READ_FLAG    = 0x0004,
    LSM303AGR_SYNC_WRITE_FLAG   = 0x0008,

    LPS22H_SYNC_READ_FLAG       = 0x0010,
    LPS22H_SYNC_WRITE_FLAG      = 0x0020,

} DMA_FLAG_IDS_E;


/***
 * Exported constants ---------------------------------------------------------
***/
#define LSM6DSL_WHO_AM_I_REG_ADDRS     (0x0F)
#define LSM6DSL_WHO_AM_I_REG_VALUE     (0x6A)






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
/***
 * Exported functions declaration ---------------------------------------------
***/
void spi_chip_select_lsm6dsl    (void);
void spi_chip_de_select_lsm6dsl (void);

/***
 * Exported Task declaration --------------------------------------------------
***/






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
