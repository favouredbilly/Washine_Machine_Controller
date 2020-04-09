/*------------------------------------------------------------------*-
Wash_Machine.H
------------------------------------------------------------------
- See Wash_Machine.C for details.
-*------------------------------------------------------------------*/
#ifndef _WASH_MACHINE_H
#define _WASH_MACHINE_H
/* ------ public data type declarations ---------------------- */
/* Possible system states */

typedef enum{AKOKO, START, FILL_DRUM, MIXED, DELICATE, RINSE_AND_SPINE, END_WASHING} eSystem_state;

void WASHER_Init(const eSystem_state);
void WASHER_Update(void);
/* ------ Private public prototypes ------------------------- */
bit WASHER_Read_Start_Switch(void);
bit WASHER_Read_Water_Level(void);
bit Selector_mixed(void);
bit Selector_delicate(void);
bit Selector_rinse_spine(void);


void WASHER_Control_Detergent_Hatch(bit);
void WASHER_Control_Door_Lock(bit);
void WASHER_Control_Motor(bit);
void WASHER_Control_Pump(bit);
void WASHER_Control_Water_Valve(bit);
#endif
/*------------------------------------------------------------------*-
---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/