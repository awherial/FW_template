/*****************************************************************************
*   @file        LSM6DSL_ACC_GYRO_wrapper.h
*   @Author      Firmware Team
*   @date        02 Feb 2018 - 03.23am
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
02 Feb 2018 - 03.23am:
    By : ...
        Rev 1.0 : LSM6DSL_ACCGYRO_wrapper.h file template created.
 -----------------------------------------------------------------------------

===============================================================================


===============================================================================
******************************************************************************/



/* Recursive include guard */
#ifndef 	LSM6DSL_ACC_GYRO_wrapper_h
	#define LSM6DSL_ACC_GYRO_wrapper_h


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
#include "component.h"

/***
 * Project Library Includes ---------------------------------------------------
***/



/***
 * Exported define ------------------------------------------------------------
***/
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
extern DrvContextTypeDef   lsm_6dsl_handle;


/***
 * Exported functions declaration ---------------------------------------------
***/
void lsm6dsl_write_cb (DMA_XFER_CB_E  cb_type);
void lsm6dsl_read_cb  (DMA_XFER_CB_E  cb_type);
void lsm6dsl_chip_select    (void);
void lsm6dsl_chip_de_select (void);


/***
 * Exported Task declaration --------------------------------------------------
***/






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
