/******************************************************************************
*   @file        sensor_tile_board.c
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



/*********************** SOURCE REVISION LOG **********************************
	This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

===============================================================================
 02 Feb 2018 - 04.15pm:
    By : ...
        Rev 1.0 : sensor_tile_board.c file template created.
 ------------------------------------------------------------------------------

===============================================================================

===============================================================================
******************************************************************************/




/******************************************************************************
* Includes
******************************************************************************/
/***
 * Standard C Library Includes ------------------------------------------------
***/
#include <stdint.h>
#include <string.h>

/***
 * Third Party Library Includes -----------------------------------------------
***/
#include "stm32l4xx_hal.h"
#include "spi.h"

/***
 * Project Library Includes ---------------------------------------------------
***/
#include "sensor_tile_board.h"
#include "LSM6DSL_ACC_GYRO_wrapper.h"

/***
 * External Function Declarations (external dependencies) ---------------------
***/
/***
 * External Variable Declarations (external dependencies) ---------------------
***/
/***
 * Global Variables Defination ------------------------------------------------
***/
device_info_t   lsm6dsl_handle;
device_info_t   lsm303agr_handle;
device_info_t   lps22h_handle;

comm_bus_info_t spi_1_handle;
comm_bus_info_t spi_2_handle;
comm_bus_info_t spi_3_handle;
comm_bus_info_t i2c_1_handle;
comm_bus_info_t i2c_2_handle;
comm_bus_info_t i2c_3_handle;


/* Private [static] - File Specific */
/* Private Structures ---------------------------------------------------------
***/
/***
 * Private Unions -------------------------------------------------------------
***/
/***
 * Private typedefs -----------------------------------------------------------
***/
/***
 * Private defines ------------------------------------------------------------
***/
/***
 * Private macros -------------------------------------------------------------
***/
/***
 * Private Enums --------------------------------------------------------------
***/
/***
 * Private variables ----------------------------------------------------------
***/
/***
 * Private Functions Declaration ----------------------------------------------
***/
static void sensor_LSM6DSL_aquire   (void);
static void sensor_LSM6DSL_release  (void);
//static void sensor_LSM303AGR_aquire (void);
//static void sensor_LSM303AGR_release(void);



/***
 *  ISR Definations -----------------------------------------------------------
***/

/**
 * @name   ISR
 * @brief   interrupt service routine.
 * @ingroup interrupts
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 */



/**
  * @brief  Tx Half Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_TxHalfCpltCallback (SPI_HandleTypeDef *hspi)    {

    comm_bus_info_t  * bus_p;

    bus_p = get_device_handle_from_bus_handle (hspi);
    bus_p->fp_dma_write_cb(DMA_XFER_HALF_CMPLT_CB);

    // set OS flag so that the waiting task can continue
        // set 'bus_p->sync_flag_write'

}

/**
  * @brief  Tx Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_TxCpltCallback (SPI_HandleTypeDef *hspi)    {

    comm_bus_info_t  * bus_p;

    bus_p = get_device_handle_from_bus_handle (hspi);
    bus_p->fp_dma_write_cb(DMA_XFER_COMPLETE_CB);

    // set OS flag so that the waiting task can continue
        // set 'bus_p->sync_flag_write'

}



/**
  * @brief  Rx Half Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_RxHalfCpltCallback (SPI_HandleTypeDef *hspi)    {

    comm_bus_info_t  * bus_p;

    bus_p = get_device_handle_from_bus_handle (hspi);
    bus_p->fp_dma_read_cb(DMA_XFER_HALF_CMPLT_CB);

    // set OS flag so that the waiting task can continue
        // set 'bus_p->sync_flag_read'
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_RxCpltCallback (SPI_HandleTypeDef *hspi)   {

    comm_bus_info_t  * bus_p;

    bus_p = get_device_handle_from_bus_handle (hspi);
    bus_p->fp_dma_read_cb(DMA_XFER_COMPLETE_CB);

    // set OS flag so that the waiting task can continue
        // set 'bus_p->sync_flag_read'

}



/**
  * @brief  SPI error callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_ErrorCallback (SPI_HandleTypeDef *hspi) {

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_ErrorCallback should be implemented in the user file
   */
  /* NOTE : The ErrorCode parameter in the hspi handle is updated by the SPI processes
            and user can use HAL_SPI_GetError() API to check the latest error occurred
   */

    // todo
        // use some logic to find out source of error and called relevent error handler
    //sensor_io_write_cb  (DMA_XFER_ERROR_CB);
            // or
    //sensor_io_read_cb   (DMA_XFER_ERROR_CB);



}

/**
  * @brief  SPI Abort Complete callback.
  * @param  hspi SPI handle.
  * @retval None
  */
void HAL_SPI_AbortCpltCallback (SPI_HandleTypeDef *hspi) {

    // todo
        // use some logic to find out source and called relevent abort handler
    //sensor_io_write_cb  (DMA_XFER_ABORT_CB);
            // or
    //sensor_io_read_cb   (DMA_XFER_ABORT_CB);


}


/* Private function Definations ---------------------------------------------*/
/**
 * @name    Private function
 * @brief   visible / called within this file..
 * @ingroup private / static
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
static void sensor_LSM6DSL_aquire (void) {

#if RTOS
    mutex_spi1Handle
#endif
    // chip select
    lsm6dsl_chip_select ();

}

static void sensor_LSM6DSL_release (void) {

    // chip select
    lsm6dsl_chip_de_select ();

#if RTOS
    // release mutex_spi_1
        // todo
#endif

}
//static void sensor_bus_aquire (device_info_t  * devp) {
//
//    if (devp->bus_type == SPI)  {
//        switch (devp->dev_address)
//        {
//
//
//
//        }
//    }
//    else if (devp->bus_type == I2C)  {
//        switch (devp->dev_address)
//        {
//
//
//
//        }
//    }
//
//
//
//
//#if RTOS
//    mutex_spi1Handle
//#endif
//    // chip select
//    lsm6dsl_chip_select ();
//
//}
//
//static void sensor_bus_release (device_info_t  * devp) {
//
//    // chip select
//    lsm6dsl_chip_de_select ();
//
//#if RTOS
//    // release mutex_spi_1
//        // todo
//#endif
//
//}

///**
// * @name    Private function
// * @brief   visible / called within this file..
// * @ingroup private / static
// *
// * @param
// *
// * @retval TRUE   Successfully did nothing.
// * @retval FALSE  Oops, did something.
// *
// * Example Usage:
// * @code
// *    example_nada(3); // Do nothing 3 times.
// * @endcode
// */
//static void sensor_LSM303AGR_aquire (void) {
//
//#if RTOS
//    // get mutex_spi_2
//        // todo
//#endif
//    // chip select
//    lsm303agr_chip_select ();
//
//}
//
//static void sensor_LSM303AGR_release (void) {
//
//    // chip select
//    lsm303agr_chip_de_select ();
//
//#if RTOS
//    // release mutex_spi_2
//        // todo
//#endif
//
//}

comm_bus_info_t * get_bus_peripheral_from_id (COMM_BUS_ID_E   bus_id)   {

    comm_bus_info_t  *  bus_p = NULL;

    switch (bus_id)
    {
        case SPI_1:
            bus_p = &spi_1_handle;
            break;
        case SPI_2:
            bus_p = &spi_2_handle;
            break;
        case SPI_3:
            bus_p = &spi_3_handle;
            break;
        case I2C_1:
            bus_p = &i2c_1_handle;
            break;
        case I2C_2:
            bus_p = &i2c_2_handle;
            break;
        case I2C_3:
            bus_p = &i2c_3_handle;
            break;

    }

    return bus_p;

}

comm_bus_info_t * get_device_handle_from_bus_handle (void * bus_handle)   {

    comm_bus_info_t  *  bus_p = NULL;

    if (bus_handle == SPI1)    {
        bus_p = &spi_1_handle;
    }
    else if (bus_handle == SPI2)    {
        bus_p = &spi_2_handle;
    }
    else if (bus_handle == SPI3)    {
        bus_p = &spi_3_handle;
    }
    else if (bus_handle == I2C1)    {
        bus_p = &i2c_1_handle;
    }
    else if (bus_handle == I2C2)    {
        bus_p = &i2c_2_handle;
    }
    else if (bus_handle == I2C3)    {
        bus_p = &i2c_3_handle;
    }


    return bus_p;

}


/* Public [Global] - Visible to all */

/***
 * Global Functions Defination ------------------------------------------------
***/

/**
 * @name    Public function
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
RETURN_TYPE_E  sensor_io_init  (BSP_DEVICE_ID_E    bsp_id) {

    RETURN_TYPE_E   result = RESULT_OK;

    switch (bsp_id)
    {
        case LSM6DSL_DEVICE_ID  :
            lsm6dsl_handle.dev_state        = DEV_NOT_CONFIGURED;
            lsm6dsl_handle.bus_type         = SPI;
            lsm6dsl_handle.bus_id           = SPI_1;
            lsm6dsl_handle.dev_id           = LSM6DSL_DEVICE_ID;
            lsm6dsl_handle.bus_handle       = LSM6DSL_BUS_HANDLE;
            lsm6dsl_handle.fp_dev_aquire    = sensor_LSM6DSL_aquire;
            lsm6dsl_handle.fp_dev_release   = sensor_LSM6DSL_release;
            lsm6dsl_handle.dev_address      = 0;     // only relevant for I2C
            lsm6dsl_handle.isInitialized    = 0;
            lsm6dsl_handle.isEnabled        = 0;
            lsm6dsl_handle.sync_flag_write  = LSM6DSL_SYNC_WRITE_FLAG;
            lsm6dsl_handle.sync_flag_read   = LSM6DSL_SYNC_READ_FLAG;
            lsm6dsl_handle.fp_dma_write_cb  = lsm6dsl_write_cb;
            lsm6dsl_handle.fp_dma_read_cb   = lsm6dsl_read_cb;
            lsm6dsl_handle.who_am_i         = LSM6DSL_WHO_AM_I_REG_VALUE;
            break;
        case LSM303AGR_DEVICE_ID:
            lsm303agr_handle.dev_id         = LSM303AGR_DEVICE_ID;
                // todo
            break;
        case LPS_22H_DEVICE_ID	:
            lps22h_handle.dev_id            = LPS_22H_DEVICE_ID;
                // todo
            break;
    }

    return result;

}


/**
 * @name    Public function
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 */
RETURN_TYPE_E  sensor_io_write (device_info_t * dev_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng)   {

    RETURN_TYPE_E       result = RESULT_OK;
    comm_bus_info_t   * bus_p;

    switch (dev_infop->bus_type)
    {
        case SPI   :
            // 1. try to aquire device and bus..
            dev_infop->fp_dev_aquire();

            if (!dev_infop->isInitialized)  {
                if (spi_init (dev_infop->bus_handle) == HAL_OK)
                    dev_infop->isInitialized = 1;
            }
            else if (!dev_infop->isEnabled) {
                // todo
            }
            // copy form 'device_info_t' to 'comm_bus_info_t'
            bus_p = get_bus_peripheral_from_id (dev_infop->bus_id);
            // copying strcture entirely with first element offset
            memcpy ((void*)bus_p->bus_type, (void*)dev_infop->bus_type, sizeof(comm_bus_info_t) - 1);

            sensor_io_spi_write (bus_p, bufp, size, blkng);

            // wait on os flag

            dev_infop->fp_dev_release();
            break;
        case I2C   :
            // todo
            break;
        case UART  :
        case USART :
        case USB   :
        case INVALID_BUS:
            return RESULT_ERROR;
            break;

    }

    return result;

}


/**
 * @name    Public function
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 */
RETURN_TYPE_E  sensor_io_read  (device_info_t * dev_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng)   {

    RETURN_TYPE_E       result = RESULT_OK;
    comm_bus_info_t   * bus_p;

    switch (dev_infop->bus_type)
    {
        case SPI   :
            // 1. try to aquire device and bus..
            dev_infop->fp_dev_aquire();

            if (!dev_infop->isInitialized)  {
                if (spi_init (dev_infop->bus_handle) == HAL_OK)
                    dev_infop->isInitialized = 1;
            }
            else if (!dev_infop->isEnabled) {
                // todo
            }
            // copy form 'device_info_t' to 'comm_bus_info_t'
            bus_p = get_bus_peripheral_from_id (dev_infop->bus_id);
            // copying strcture entirely with first element offset
            memcpy ((void*)bus_p->bus_type, (void*)dev_infop->bus_type, sizeof(comm_bus_info_t) - 1);

            sensor_io_spi_read (bus_p, bufp, size, blkng);

            // wait on os flag

            dev_infop->fp_dev_release();
            break;
        case I2C   :
            // todo
            break;
        case UART  :
        case USART :
        case USB   :
        case INVALID_BUS:
            return RESULT_ERROR;
            break;

    }

    return result;
}


/**
 * @name    Public function
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 */
RETURN_TYPE_E  sensor_io_spi_write  (comm_bus_info_t * bus_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng)   {


    RETURN_TYPE_E  result = RESULT_OK;
    // todo
        // validate all input parameters
        // return error if not in limits..

    // Clear Os flag
        // todo

    if (blkng == NON_BLOCKING_MODE) {
        //HAL_StatusTypeDef   spi_read_nb (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)  {
        if (spi_write_nb (bus_infop->bus_handle, bufp, size) != HAL_OK) {
             result = RESULT_ERROR;
        }
    }
    else    {
        //HAL_StatusTypeDef   spi_read (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
        if (spi_write (bus_infop->bus_handle, bufp, size, 1000) != HAL_OK) {
            result = RESULT_ERROR;
        }
        // set Os flag .. so that the waiting task can proceed..
            // todo
    }

    return result;

}



/**
 * @name    Public function
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 */
RETURN_TYPE_E  sensor_io_spi_read  (comm_bus_info_t * bus_infop, uint8_t * bufp, uint16_t size, DEV_ACCESS_MODE_E  blkng)   {

    RETURN_TYPE_E  result = RESULT_OK;
    // todo
        // validate all input parameters
        // return error if not in limits..

    // Clear Os flag
        // todo

    if (blkng == NON_BLOCKING_MODE) {
        //HAL_StatusTypeDef   spi_read_nb (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)  {
        if (spi_read_nb (bus_infop->bus_handle, bufp, size) != HAL_OK) {
             result = RESULT_ERROR;
        }
    }
    else    {
        //HAL_StatusTypeDef   spi_read (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
        if (spi_read (bus_infop->bus_handle, bufp, size, 1000) != HAL_OK) {
            result = RESULT_ERROR;
        }
        // set Os flag .. so that the waiting task can proceed..
            // todo
    }

    return result;

}



/***
 * Independent Task Definations -----------------------------------------------
***/

/**
 * @name    Independent Task
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 */






/**
 * @see Dio_Init
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 *
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 09/01/2015 </td><td> 0.5.0            </td><td> JWB      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */

//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
//            if (blkng == NON_BLOCKING_MODE) {
//                //HAL_StatusTypeDef   spi_read_nb (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)  {
//                if (spi_read_nb (dev_infop->bus_handle, bufp, size) != HAL_OK) {
//                    // register call back function
//                    if (dev_infop->fp_dma_read_cb)  {
//                        dev_infop->fp_dma_read_cb ();
//                    }
//                    result = RESULT_ERROR;
//                }
//            }
//            else    {
//                //HAL_StatusTypeDef   spi_read (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//                if (spi_read (dev_infop->bus_handle, bufp, size, 1000) != HAL_OK) {
//                    result = RESULT_ERROR;
//                }
//            }