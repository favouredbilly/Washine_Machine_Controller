/*------------------------------------------------------------------*-
Basic_EOS.C
------------------------------------------------------------------*/
#include "Main.H"
#include "Basic_EOS.H"
#include "Wash_Machine.H"
/*------------------------------------------------------------------*-
ISR()
Invoked periodically by Timer 2 overflow:
see Init_Timer2() for timing details.
-*------------------------------------------------------------------*/
 ISR() interrupt INTERRUPT_Timer_2_Overflow
 {
// Must manually reset the T2 flag
TF2 = 0;
//===== USER CODE - Begin =======================================
// Call 'Update' function here
		WASHER_Update();
//===== USER CODE - End =========================================
}


/*-------------------------------------------------------------*-
Init_Timer2()
...
-*-------------------------------------------------------------*/
void Init_Timer2(const tByte TICK_MS)
{
tLong Inc;
tWord Reload_16;
tByte Reload_08H, Reload_08L;
/* Timer 2 is configured as a 16-bit timer,
which is automatically reloaded when it overflows */
T2CON = 0x04; /* Load T2 control register */
/* Number of timer increments required (max 65536) */
Inc = ((tLong)TICK_MS * (Oscillator_freq/1000)) / (tLong)Oscillation_per_instruction;
/* 16-bit reload value */
Reload_16 = (tWord) (65536UL - Inc);
/* 8-bit reload values (High & Low) */
Reload_08H = (tByte)(Reload_16 / 256);
Reload_08L = (tByte)(Reload_16 % 256);
/* Used for manually checking timing (in simulator) */
/*P2 = Reload_08H; */
/*P3 = Reload_08L; */
TH2 = Reload_08H; /* Load T2 high byte */
RCAP2H = Reload_08H; /* Load T2 reload capt. reg. high byte */
TL2 = Reload_08L; /* Load T2 low byte */
RCAP2L = Reload_08L; /* Load T2 reload capt. reg. low byte */
/* Timer 2 interrupt is enabled, and ISR will be called
whenever the timer overflows. */
ET2 = 1;
/* Start Timer 2 running */
TR2 = 1;
EA = 1; /* Globally enable interrupts */
}

/*-------------------------------------------------------------*-
Go_To_Sleep()
This operating system enters 'idle mode' between clock ticks
to save power. The next clock tick will return the processor
to the normal operating state.
-*-------------------------------------------------------------*/
void Go_To_Sleep(void)
{
PCON |= 0x01; /* Enter idle mode (generic 8051 version) */
}
/*-------------------------------------------------------------*-
---- END OF FILE ---------------------------------------
-*-------------------------------------------------------------*/
