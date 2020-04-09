#include "Main.H"
#include "Port.H"
#include "Wash_Machine.H"

/* ------ Private constants ----------------------------------- */
#define OFF 1
#define ON 0
#define MAX_FILL_DURATION (tLong) 160  							//1000  1 minutes. But lower value used for simulation
#define MIXED_DURATION	120												//30000  	30 minutes. But lower value used for simulation
#define DELICATE_DURATION 120											//40000  40 minutes. But lower value used for simulation
#define RINSE_AND_SPINE_DURATION 100								//10000 10 minutes. But lower value used for simulation

/* ------ Private variables ----------------------------------- */
static eSystem_state System_state_G;
//static tWord Time_in_state_G;
static tLong Time_in_state_G;

/* -------------------------------------------------------------------
					INPUT FUNCTIONS
------------------------------------------------------------------------- */
/* -------------------------------------------------------------------
 Selector for normal wash with detergent for MIXED cloths
------------------------------------------------------------------------- */
bit Selector_mixed(void)
{
	if (select1==0)
	{
		return 1;
	}
	else
	{
	return 0;
	}
	
}

/* -------------------------------------------------------------------
 Selector for normal wash with detergent for DELICATE cloths
------------------------------------------------------------------------- */
bit Selector_delicate(void)
{
	if (select2==0)
	{
		return 1;
	}
	else
	{
	return 0;
	}
	
}

/* -------------------------------------------------------------------
 Selector for normal RINSE_AND_SPINE of cloths without detergent 
------------------------------------------------------------------------- */
bit Selector_rinse_spine(void)
{
	if (select3==0)
	{
		return 1;
	}
	else
	{
	return 0;
	}
	
}
/* --------------------------------------------------------------- */
bit WASHER_Read_Start_Switch(void)
{
/* starting switch */
if (Start_pin == 0)
{
/* Start switch pressed */
return 1;
}
else
{
return 0;
}
}
/* --------------------------------------------------------------- */
bit WASHER_Read_Water_Level(void)
{
/* water level sensor... */
if(water_level==0){
	
return 1;	
}
else 
{
return 0;
}

}



/* --------------------------------------------------------------- 
				OUTPUT FUNCTIONS
 --------------------------------------------------------------- */
void WASHER_Control_Detergent_Hatch(bit State)
{
Control_derterget_switch = State;
}

void WASHER_Control_Door_Lock(bit state1)
{
Control_door_switch = state1;	
}

void WASHER_Control_Motor(bit state2)
{
Control_motor_switch = state2;
}

void WASHER_Control_Pump(bit state3)
{
Control_pump_switch = state3;		
}

void WASHER_Control_Water_Valve(bit state4)
{
Control_watervalve_switch = state4;
}


/* --------------------------------------------------------------- */
void WASHER_Init(const eSystem_state start_state)
{

System_state_G = start_state;
//P2 =0x00;
	
}

/* --------------------------------------------------------------- */
void WASHER_Update(void)
{
	TF2 = 0;
/* Call once per second */
switch (System_state_G)
{
case AKOKO:
{
//	P0 = 0x00;
//P2 = 0xFF;
//P3= 0x00;

//P3 = 0XFF;
/* Set up initial state */
/* Motor is off */
WASHER_Control_Motor(OFF);
/* Pump is off */
WASHER_Control_Pump(OFF);
/* Valve is closed */
WASHER_Control_Water_Valve(OFF);
/* Wait (indefinitely) until START is pressed */
if (WASHER_Read_Start_Switch() != 1)
{
return;
}
/* Start switch pressed
-> read the selector dial and assure that one of three programs is selected before starting*/
if (Selector_mixed()==1 | Selector_delicate()==1 | Selector_rinse_spine()==1)
{
		/* Change state */
	System_state_G = START;
}


break;
}


case START:
{

/* Lock the door */
WASHER_Control_Door_Lock(ON);
/* Start filling the drum */
WASHER_Control_Water_Valve(ON);
/* Release the detergent (if anyof these) */
if (Selector_mixed()==1 | Selector_delicate()==1 )
{
WASHER_Control_Detergent_Hatch(ON);
/* Ready to go to next state */
System_state_G = FILL_DRUM;
Time_in_state_G = 0;
}
else if (Selector_rinse_spine()==1)
{
System_state_G = FILL_DRUM;
Time_in_state_G = 0;
	
}

break;
}

case FILL_DRUM:
{

/* Remain in this state until drum is full
NOTE: Timeout facility included here */
if ((++Time_in_state_G == MAX_FILL_DURATION)  | (WASHER_Read_Water_Level() == 1))
{

/* Ready to go to next state */
System_state_G = MIXED;
Time_in_state_G = 0;
}

break;
}


case MIXED:
{

/* This is a normal wash with detergent */
WASHER_Control_Motor(ON);
if (++Time_in_state_G >= MIXED_DURATION)
{
System_state_G = RINSE_AND_SPINE;
Time_in_state_G = 0;
}
break;
}

case DELICATE:
{

/* This is a normal wash with detergent */
WASHER_Control_Motor(ON);
if (++Time_in_state_G >= DELICATE_DURATION)
{
System_state_G = RINSE_AND_SPINE;
Time_in_state_G = 0;
}
break;
}

case RINSE_AND_SPINE:
{

/* This is the rinse section */
WASHER_Control_Motor(ON);
//Detergent off
WASHER_Control_Detergent_Hatch(OFF);
if (++Time_in_state_G >= RINSE_AND_SPINE_DURATION)
{
System_state_G = END_WASHING;
Time_in_state_G = 0;
}
break;
}

case END_WASHING:
{

/* This is an end of washing */

/* Motor is off */
WASHER_Control_Motor(OFF);
/* Pump is off */
WASHER_Control_Pump(OFF);
/* Valve is closed */
WASHER_Control_Water_Valve(OFF);
/* Door Lock off. Now door can be opened */
WASHER_Control_Door_Lock(OFF);

break;
}
}
}

