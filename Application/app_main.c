#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <mtkernel/device/ser/sysdepend/stm32h7/ser_mode_sysdep.h>
#include <mtkernel/device/include/dev_ser.h>

#define GREEN_PIN		1<<0	/*((uint16_t)0x0001)  Pin B0 selected		*/
#define RED_PIN		1<<14	/*((uint16_t)0x4000)  Pin B14 selected		*/
#define YELLOW_PIN	1<<1	/*((uint16_t)0x0002)  Pin E1 selected		*/
#define GPIO_PC8	1<<8	/*((uint16_t)0x0080)  Pin C8 selected		*/

//#define SCI0_RX (1<<10) //PA0	UART4_TX
//#define SCI0_TX (1<<9)  //PC11	UART4_RX
//
//#define USERT1_TX (1<<6)// PB6
//#define USERT1_RX (1<<7)// PB7

#define BUFSIZE 256

enum DEVICE_CODE{
	DEV_UART,
	DEV_I2C,
	DEV_ADC,
};

//LOCAL void task_1(INT stacd, void *exinf);	// task execution function
//LOCAL ID	tskid_1;			// Task ID number
//LOCAL T_CTSK ctsk_1 = {				// Task creation information
//	.itskpri	= 10,
//	.stksz		= 1024,
//	.task		= task_1,
//	.tskatr		= TA_HLNG | TA_RNG3,
//};

ID dd_com = -1;

LOCAL void read_tsk(INT stacd, void *exinf);  // task execution function
LOCAL ID    tskid_read;            // Task ID number
LOCAL T_CTSK ctsk_read = {             // Task creation information
    .itskpri    = 10,
    .stksz      = 1024,
    .task       = read_tsk,
    .tskatr     = TA_HLNG | TA_RNG3,
};

LOCAL void send_tsk(INT stacd, void *exinf);  // task execution function
LOCAL ID    tskid_send;            // Task ID number
LOCAL T_CTSK ctsk_send = {             // Task creation information
    .itskpri    = 10,
    .stksz      = 1024,
    .task       = send_tsk,
    .tskatr     = TA_HLNG | TA_RNG3,
};

//LOCAL void task_1(INT stacd, void *exinf)
//{
//	while(1) {
//		/* Inverts the LED on the board. */
//		out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))^(GREEN_PIN|RED_PIN));
//
//		out_w(GPIO_ODR(C), (in_w(GPIO_ODR(C)))^GPIO_PC8);
//
//		tk_dly_tsk(3000);
//	}
//}

LOCAL ER open_device(enum DEVICE_CODE target)
{
	ER err = E_OK;

	switch(target){
		case DEV_UART:
			dd_com = tk_opn_dev((UB*)"huartd", TD_UPDATE);
			if(dd_com < E_OK){
				tm_printf((UB*)"uart_init: open error\n");
				err = -1;
			}
			break;
		case DEV_I2C:
			dd_com = tk_opn_dev((UB*)"hiica", TD_UPDATE);
			if(dd_com < E_OK){
				tm_printf((UB*)"uart_init: open error\n");
				err = -1;
			}
			break;
		default:
			tm_printf((UB*)"undefined error\n");
			err = -2;
			break;
	}

	return err;
}

LOCAL SZ get_str_siz(const char str[], const char d){
	SZ i = 0;
	while(str[i] != d){
		if(str[i] == '\0'){
			break;
		}
		i++;
	}
	return i;
}

LOCAL void read_tsk(INT stacd, void *exinf)
{
	char data_com[BUFSIZE] = {'\0'};
	ER err;
	UB err_cnt = 0, i;

	tm_printf((UB*)"tsk read start\n");

	if(dd_com == -1){
		err = open_device(DEV_UART);
		if(err != E_OK){
			tm_printf((UB*)"open error\n");
			tk_ext_tsk();
		}
	}

    while(1){
    	err = tk_rea_dev(dd_com, 0, data_com, BUFSIZE, TMO_FEVR);
    	i = get_str_siz(data_com, '\r');
    	data_com[i] = (UB)'\0';
    	tm_printf((UB*)"get data: %s\n", data_com);

    	if(err >= E_OK){
    		tm_printf((UB*)"Read Success %d\n", err);
    		err_cnt = 0;
    	} else {
    		tm_printf((UB*)"Read Error %d\n", err);
    		err_cnt++;

    		// timeout
        	if(err_cnt > 5){
        		break;
        	}
    	}
    	data_com[0] = (UB)'\0';

    	tk_dly_tsk(700);
    }
	tk_ext_tsk();
}

LOCAL void send_tsk(INT stacd, void *exinf)
{
//	char data_com[BUFSIZE] = {'\0'};
	ER err;
	UB i = 0;

	tm_printf((UB*)"tsk send start\n");

	if(dd_com == -1){
		err = open_device(DEV_UART);
		if(err != E_OK){
			tm_printf((UB*)"open error\n");
			tk_ext_tsk();
		}
	}

	while(1){
		err = tk_wri_dev(dd_com, 0, "hello\n", get_str_siz("hello\n", '\0'), TMO_FEVR);
		if(err >= E_OK){
			tm_printf((UB*)"Send Success: %d\n", err);
			i = 0;
		} else {
			tm_printf((UB*)"Send Error: %d\n", err);
			i++;

			// timeout
			if(i > 5){
				break;
			}
		}

		tk_dly_tsk(1000);
	}
	tk_ext_tsk();
}

/* usermain関数 */
EXPORT INT    usermain( void )
{
    tm_printf((UB*)"Start User-main program.\n");

    /* Create & Start Tasks */
//    tskid_1 = tk_cre_tsk(&ctsk_1);
//    tk_sta_tsk(tskid_1, 0);

    tskid_read = tk_cre_tsk(&ctsk_read);
    tk_sta_tsk(tskid_read, 0);

//    tskid_send = tk_cre_tsk(&ctsk_send);
//    tk_sta_tsk(tskid_send, 0);

    tk_slp_tsk(TMO_FEVR);

    return 0;
}






