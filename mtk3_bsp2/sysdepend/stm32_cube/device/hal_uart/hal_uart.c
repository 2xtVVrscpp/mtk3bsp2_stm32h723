/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2023-2024 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2024/02.
 *
 *----------------------------------------------------------------------
 */
#include <sys/machine.h>
#include <config_bsp/stm32_cube/config_bsp.h>

#ifdef MTKBSP_STM32CUBE
#if DEVCNF_USE_HAL_UART

#include <stdlib.h>

#include <tk/tkernel.h>
#include <tk/device.h>

#include <sysdepend/stm32_cube/cpu_status.h>
#include <mtkernel/kernel/knlinc/tstdlib.h>
#include <mtkernel/device/common/drvif/msdrvif.h>
#include "hal_uart_cnf.h"

/*
 *	hal_uart.c
 *	UART device driver (STM32Cube FW)
*/

/*---------------------------------------------------------------------*/
/*UART Device driver Control block
 */
typedef struct {
	UART_HandleTypeDef	*huart;		// HAL handle
	ID			devid;		// Device ID
	UINT		omode;		// Open mode
	UW			unit;		// Unit no
	ER			err;		// Error code that occurred during interrupt processing
	ID			evtmbfid;	// MBF ID for event notification
} T_HAL_UART_DCB;

/* Interrupt detection flag */
LOCAL ID	id_flgid;
LOCAL T_CFLG	id_flg	= {
			.flgatr		= TA_TFIFO | TA_WMUL,
			.iflgptn	= 0,
};

#if TK_SUPPORT_MEMLIB
LOCAL T_HAL_UART_DCB	*dev_uart_cb[DEV_HAL_UART_UNITNM];
#define		get_dcb_ptr(unit)	(dev_uart_cb[unit])
#else
LOCAL T_HAL_UART_DCB	dev_uart_cb[DEV_HAL_UART_UNITNM];
#define		get_dcb_ptr(unit)	(&dev_UART_cb[unit])
#endif

/*---------------------------------------------------------------------*/
/*Device-specific data control
 */

/* HAL Callback functions */
LOCAL void HAL_UART_Callback(UART_HandleTypeDef *huart, ER err)
{
	T_HAL_UART_DCB	*p_dcb;
	UINT	i;

	ENTER_TASK_INDEPENDENT

	for(i = 0; i < DEV_HAL_UART_UNITNM; i++) {
		p_dcb = get_dcb_ptr(i);
		if(p_dcb->huart == huart) {
			p_dcb->err = err;
			tk_set_flg(id_flgid, 1<< p_dcb->unit);
			break;
		}
	}

	LEAVE_TASK_INDEPENDENT
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Callback(huart, E_OK);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Callback(huart, E_OK);
}

void HAL_UART_MemRxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Callback(huart, E_OK);
}

void HAL_UART_MemTxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Callback(huart, E_OK);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Callback(huart, E_IO);
}

void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Callback(huart, E_ABORT);
}

LOCAL ER read_data(T_HAL_UART_DCB *p_dcb, T_DEVREQ *req)
{
	HAL_StatusTypeDef	hal_sts;
	UINT			wflgptn, rflgptn;
	ER			err;

	wflgptn = 1 << p_dcb->unit;
	tk_clr_flg(id_flgid, ~wflgptn);

	/* your code to read data */
	hal_sts = HAL_UART_Receive_IT(
				p_dcb->huart,	// UART_Handle
				req->buf,		// Pointer to data buffer,
				req->size		// Amount of data to be sent
				);
	/*  */

	if(hal_sts != HAL_OK) return E_BUSY;

	err = tk_wai_flg(id_flgid, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_UART_TMOUT);
	if(err >= E_OK) {
		err  = p_dcb->err;
		if(err >= E_OK) req->asize = req->size;
	}

	return err;
}

LOCAL ER write_data(T_HAL_UART_DCB *p_dcb, T_DEVREQ *req)
{
	HAL_StatusTypeDef	hal_sts;
	UINT			wflgptn, rflgptn;
	ER			err;

	wflgptn = 1 << p_dcb->unit;
	tk_clr_flg(id_flgid, ~wflgptn);


	/* your code to write data*/
	hal_sts = HAL_UART_Transmit_IT(
				p_dcb->huart,	// UART_Handle
				req->buf,		// Pointer to data buffer,
				req->size		// Amount of data to be sent
				);
	/*  */

	if(hal_sts != HAL_OK) return E_BUSY;

	err = tk_wai_flg(id_flgid, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_UART_TMOUT);
	if(err >= E_OK) {
		err  = p_dcb->err;
		if(err >= E_OK) req->asize = req->size;
	}

	return err;
}

/*----------------------------------------------------------------------
 * mSDI I/F function
 */
/*
 * Open device
 */
LOCAL ER dev_uart_openfn( ID devid, UINT omode, T_MSDI *msdi)
{
	T_HAL_UART_DCB	*p_dcb;

	p_dcb = (T_HAL_UART_DCB*)(msdi->dmsdi.exinf);
	p_dcb->omode = omode;
	return E_OK;
}

/*
 * Close Device
 */
LOCAL ER dev_uart_closefn( ID devid, UINT option, T_MSDI *msdi)
{

	return E_OK;
}

/*
 * Read Device
 */
LOCAL ER dev_uart_readfn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_UART_DCB	*p_dcb;
	ER		err;

	p_dcb = (T_HAL_UART_DCB*)(p_msdi->dmsdi.exinf);

	if(req->start >= 0) {
		err = read_data( p_dcb, req);	// Device specific data
	}
	return err;
}

/*
 * Write Device
 */
LOCAL ER dev_uart_writefn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_UART_DCB	*p_dcb;
	ER		rtn;

	p_dcb = (T_HAL_UART_DCB*)(p_msdi->dmsdi.exinf);

	if(req->start >= 0) {
		rtn = write_data( p_dcb, req);	// Device specific data
	}
	return rtn;
}

/*
 * Event Device
 */
LOCAL ER dev_uart_eventfn( INT evttyp, void *evtinf, T_MSDI *msdi)
{
	return E_NOSPT;
}

/*----------------------------------------------------------------------
 * Device driver initialization and registration
 */
EXPORT ER dev_init_hal_uart( UW unit, UART_HandleTypeDef *huart )
{
	T_HAL_UART_DCB	*p_dcb;
	T_IDEV		idev;
	T_MSDI		*p_msdi;
	T_DMSDI		dmsdi;
	ER		err;
	INT		i;

	if( unit >= DEV_HAL_UART_UNITNM) return E_PAR;

#if TK_SUPPORT_MEMLIB
	p_dcb = (T_HAL_UART_DCB*)Kmalloc(sizeof(T_HAL_UART_DCB));
	if( p_dcb == NULL) return E_NOMEM;
	dev_uart_cb[unit]	= p_dcb;
#else
	p_dcb = &dev_uart_cb[unit];
#endif

	id_flgid = tk_cre_flg(&id_flg);
	if(id_flgid <= E_OK) {
		err = (ER)id_flgid;
		goto err_1;
	}

	/* Device registration information */
	dmsdi.exinf	= p_dcb;
	dmsdi.drvatr	= 0;			/* Driver attributes */
	dmsdi.devatr	= TDK_UNDEF;		/* Device attributes */
	dmsdi.nsub	= 0;			/* Number of sub units */
	dmsdi.blksz	= 1;			/* Unique data block size (-1 = unknown) */
	dmsdi.openfn	= dev_uart_openfn;
	dmsdi.closefn	= dev_uart_closefn;
	dmsdi.readfn	= dev_uart_readfn;
	dmsdi.writefn	= dev_uart_writefn;
	dmsdi.eventfn	= dev_uart_eventfn;
	
	knl_strcpy( (char*)dmsdi.devnm, DEVNAME_HAL_UART);
	i = knl_strlen(DEVNAME_HAL_UART);
	dmsdi.devnm[i] = (UB)('a' + unit);
	dmsdi.devnm[i+1] = 0;

	err = msdi_def_dev( &dmsdi, &idev, &p_msdi);
	if(err != E_OK) goto err_1;

	p_dcb->huart	= huart;
	p_dcb->devid	= p_msdi->devid;
	p_dcb->unit	= unit;
	p_dcb->evtmbfid	= idev.evtmbfid;

	return E_OK;

err_1:
#if TK_SUPPORT_MEMLIB
	Kfree(p_dcb);
#endif
	return err;
}

#endif		/* DEVCNF_USE_HAL_UART */
#endif		/* MTKBSP_STM32CUBE */
