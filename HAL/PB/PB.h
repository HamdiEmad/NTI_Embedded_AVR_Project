#ifndef HAL_HPB_PB_H_
#define HAL_HPB_PB_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO.h"

#define PB_PORT DIO_PORTC
#define PB_FIRST_PIN DIO_PIN0
#define PB_NUM 5U

#define PB_1 0U
#define PB_2 1U
#define PB_3 2U
#define PB_4 3U
#define PB_5 4U

#define PB_PRESSED 0U
#define PB_NOT_PRESSED 1U
#define PB_DEBOUNCE_TIME_MS 20U

void HPB_voidInit(void);
uint8 HPB_u8ReadPin(uint8 A_u8ButtonId);

#endif /* HAL_HPB_PB_H_ */