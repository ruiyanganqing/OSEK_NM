#ifndef CAN_H
#define CAN_H
#include "OSEKNM.h"
#include "Driver_Common.h"
int STM32_TX_CAN_Transmit(NMPDU_t* NMPDU);
void STM32_CAN1_Init(void);
#endif
