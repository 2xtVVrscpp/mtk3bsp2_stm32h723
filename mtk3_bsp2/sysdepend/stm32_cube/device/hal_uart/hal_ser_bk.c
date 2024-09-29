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
#if DEVCNF_USE_HAL_SER

#include <stdlib.h>

#include <tk/tkernel.h>
#include <tk/device.h>

#include <sysdepend/stm32_cube/cpu_status.h>
#include <mtkernel/kernel/knlinc/tstdlib.h>
#include <mtkernel/device/common/drvif/msdrvif.h>
#include "hal_ser_cnf.h"

/*
 *	hal_iser.c
 *	SER device driver (STM32Cube FW)
*/

/*---------------------------------------------------------------------*/
/*SER Device driver Control block
 */
typedef struct {
	UART_HandleTypeDef	*hser;		// HAL handle
	ID			devid;		// Device ID
	UINT		omode;		// Open mode
	UW			unit;		// Unit no
	ER			err;		// Error code that occurred during interrupt processing
	ID			evtmbfid;	// MBF ID for event notification
	UW			dmode;		// Device mode
	UW			tadr;		// Target Address
} T_HAL_SER_DCB;

/* Interrupt detection flag */
LOCAL ID	id_flgid;
LOCAL T_CFLG	id_flg	= {
			.flgatr		= TA_TFIFO | TA_WMUL,
			.iflgptn	= 0,
};

#if TK_SUPPORT_MEMLIB
LOCAL T_HAL_SER_DCB	*dev_ser_cb[DEV_HAL_SER_UNITNM];
#define		get_dcb_ptr(unit)	(dev_ser_cb[unit])
#else
LOCAL T_HAL_SER_DCB	dev_ser_cb[DEV_HAL_SER_UNITNM];
#define		get_dcb_ptr(unit)	(&dev_SER_cb[unit])
#endif

/*---------------------------------------------------------------------*/
/*Device-specific data control
 */

/* HAL Callback functions */
LOCAL void HAL_SER_Callback(UART_HandleTypeDef *hser, ER err)
{
	T_HAL_SER_DCB	*p_dcb;
	UINT	i;

	ENTER_TASK_INDEPENDENT

	for(i = 0; i < DEV_HAL_SER_UNITNM; i++) {
		p_dcb = get_dcb_ptr(i);
		if(p_dcb->hser == hser) {
			p_dcb->err = err;
			tk_set_flg(id_flgid, 1<< p_dcb->unit);
			break;
		}
	}

	LEAVE_TASK_INDEPENDENT
}

void HAL_SER_MasterRxCpltCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_OK);
}

void HAL_SER_MasterTxCpltCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_OK);
}

void HAL_SER_SlaveRxCpltCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_OK);
}

void HAL_SER_SlaveTxCpltCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_OK);
}

void HAL_SER_MemRxCpltCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_OK);
}

void HAL_SER_MemTxCpltCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_OK);
}

void HAL_SER_ErrorCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_IO);
}

void HAL_SER_AbortCpltCallback(UART_HandleTypeDef *hser)
{
	HAL_SER_Callback(hser, E_ABORT);
}

LOCAL ER read_data(T_HAL_SER_DCB *p_dcb, T_DEVREQ *req)
{
	UINT			wflgptn, rflgptn;
	ER			err;

	wflgptn = 1 << p_dcb->unit;
	tk_clr_flg(id_flgid, ~wflgptn);

	/* your code to read data */

	err = tk_wai_flg(id_flgid, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_SER_TMOUT);
	if(err >= E_OK) {
		err  = p_dcb->err;
		if(err >= E_OK) req->asize = req->size;
	}

	return err;
}

LOCAL ER write_data(T_HAL_SER_DCB *p_dcb, T_DEVREQ *req)
{
	UINT			wflgptn, rflgptn;
	ER			err;

	wflgptn = 1 << p_dcb->unit;
	tk_clr_flg(id_flgid, ~wflgptn);


	/* your code to write data*/

	err = tk_wai_flg(id_flgid, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_SER_TMOUT);
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
LOCAL ER dev_ser_openfn( ID devid, UINT omode, T_MSDI *msdi)
{
	T_HAL_SER_DCB	*p_dcb;

	p_dcb = (T_HAL_SER_DCB*)(msdi->dmsdi.exinf);
	p_dcb->omode = omode;
	return E_OK;
}

/*
 * Close Device
 */
LOCAL ER dev_ser_closefn( ID devid, UINT option, T_MSDI *msdi)
{
	return E_OK;
}

/*
 * Read Device
 */
LOCAL ER dev_ser_readfn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_SER_DCB	*p_dcb;
	ER		err;

	p_dcb = (T_HAL_SER_DCB*)(p_msdi->dmsdi.exinf);

	if(req->start >= 0) {
		err = read_data( p_dcb, req);	// Device specific data
	}
	return err;
}

/*
 * Write Device
 */
LOCAL ER dev_ser_writefn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_SER_DCB	*p_dcb;
	ER		rtn;

	p_dcb = (T_HAL_SER_DCB*)(p_msdi->dmsdi.exinf);

	if(req->start >= 0) {
		rtn = write_data( p_dcb, req);	// Device specific data
	}
	return rtn;
}

/*
 * Event Device
 */
LOCAL ER dev_ser_eventfn( INT evttyp, void *evtinf, T_MSDI *msdi)
{
	return E_NOSPT;
}

/*----------------------------------------------------------------------
 * Device driver initialization and registration
 */
EXPORT ER dev_init_hal_ser( UW unit, UART_HandleTypeDef *hser )
{
	T_HAL_SER_DCB	*p_dcb;
	T_IDEV		idev;
	T_MSDI		*p_msdi;
	T_DMSDI		dmsdi;
	ER		err;
	INT		i;

	if( unit >= DEV_HAL_SER_UNITNM) return E_PAR;

#if TK_SUPPORT_MEMLIB
	p_dcb = (T_HAL_SER_DCB*)Kmalloc(sizeof(T_HAL_SER_DCB));
	if( p_dcb == NULL) return E_NOMEM;
	dev_ser_cb[unit]	= p_dcb;
#else
	p_dcb = &dev_ser_cb[unit];
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
	dmsdi.openfn	= dev_ser_openfn;
	dmsdi.closefn	= dev_ser_closefn;
	dmsdi.readfn	= dev_ser_readfn;
	dmsdi.writefn	= dev_ser_writefn;
	dmsdi.eventfn	= dev_ser_eventfn;
	
	knl_strcpy( (char*)dmsdi.devnm, DEVNAME_HAL_SER);
	i = knl_strlen(DEVNAME_HAL_SER);
	dmsdi.devnm[i] = (UB)('a' + unit);
	dmsdi.devnm[i+1] = 0;

	err = msdi_def_dev( &dmsdi, &idev, &p_msdi);
	if(err != E_OK) goto err_1;

	p_dcb->hser	= hser;
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

#endif		/* DEVCNF_USE_HAL_SER */
#endif		/* MTKBSP_STM32CUBE */
