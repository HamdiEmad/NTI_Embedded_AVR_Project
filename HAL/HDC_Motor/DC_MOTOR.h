// Dc_Motor.h

#ifndef HAL_HDC_MOTOR_DC_MOTOR_H_
#define HAL_HDC_MOTOR_DC_MOTOR_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO.h"

void HDC_Motor_voidInit(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin);
void HDC_Motor_voidStop(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin);
void HDC_Motor_voidCW(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin);
void HDC_Motor_voidCCW(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin);

#endif /* HAL_HDC_MOTOR_DC_MOTOR_H_ */