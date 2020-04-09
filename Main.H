/*-------------------------------------------------------------*-
Main.H
-*-------------------------------------------------------------*/
#ifndef _MAIN_H
#define _MAIN_H
//--------------------------------------------------------

#include <reg52.h>
/* Oscillator / resonator frequency (in Hz) e.g. (11059200UL) */
#define Oscillator_freq (12000000UL)

/* Number of oscillations per instruction (12, etc)   */

#define Oscillation_per_instruction (12)
/* --------------------------------------------------------

-------------------------------------------------------- */

typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tLong;
/* Interrupts  */
/* --------------------------------------------------------
The following definistions allow me to use 
timer 0, timer 1 and timer 2 interrupts
-------------------------------------------------------- */

#define INTERRUPT_Timer_0_Overflow 1
#define INTERRUPT_Timer_1_Overflow 3
#define INTERRUPT_Timer_2_Overflow 5
#endif