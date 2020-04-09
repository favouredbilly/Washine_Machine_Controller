/*-------------------------------------------------------------*-
Port.H
--------------------------------------------------------
Header file for porth definitions
-*-------------------------------------------------------------*/
#ifndef _PORT_H
#define _PORT_H
#include <reg52.h>


	/*-----OUTPUT PINS------------*/
sbit Control_derterget_switch = P2^0;
sbit Control_door_switch 	= P2^1;
sbit Control_motor_switch 	= P2^2;
sbit Control_pump_switch 	= P2^3;
sbit Control_watervalve_switch = P2^4;

/*---------INPUT PINS--------------*/
/*------selector switches----------*/
sbit select1= P3^0;
sbit select2= P3^2;
sbit select3= P3^3;
/*----Start Switch---------------*/
sbit Start_pin = P3^1;
sbit water_level = P1^4;


#endif
/*-------------------------------------------------------------*-
---- END OF FILE ---------------------------------------
-*-------------------------------------------------------------*/