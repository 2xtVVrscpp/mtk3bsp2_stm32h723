/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2023-2024 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2024/03.
 *
 *----------------------------------------------------------------------
 */

#ifndef	_DEV_HAL_SER_H_
#define	_DEV_HAL_SER_H_
/*
 *	hal_ser.h
 *	SER device driver (STM32Cube FW)
*/
/*----------------------------------------------------------------------
 * SER Device
 */
#define DEV_HAL_SER1	0
#define DEV_HAL_SER2	1
#define DEV_HAL_SER3	2
#define DEV_HAL_SER4	3
#define DEV_HAL_SER5	4

/*----------------------------------------------------------------------
 * Attribute data
 */
#define TDN_HAL_SER_MODE	(-100)	// SER Mode
//#define TDN_HAL_SER_TADR	(-101)	// Target Address
#define TDN_HAL_SER_MAX		(-101)

//#define HAL_SER_MODE_CNT	(0)	// SER Mode: Controller mode
//#define HAL_SER_MODE_TAR	(1)	// SER Mode: Target mode

/*----------------------------------------------------------------------
 * Device driver initialization and registration
 */

IMPORT ER dev_init_hal_ser( UW unit, UART_HandleTypeDef *hser );

/*----------------------------------------------------------------------
 * SER register access support function
 */
EXPORT ER ser_read_reg(ID dd, UW sadr, UW radr, UB *data);
EXPORT ER ser_write_reg(ID dd, UW sadr, UW radr, UB data);

#endif	/* _DEV_HAL_SER_H_ */
