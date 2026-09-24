#include "DC_MOTOR.h"

void HDC_Motor_voidInit(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin)
{
    DIO_enumInitializePin(A_u8Pin1Port, DIO_OUTPUT, A_u8Pin1Pin);
    DIO_enumInitializePin(A_u8Pin2Port, DIO_OUTPUT, A_u8Pin2Pin);
}
void HDC_Motor_voidStop(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin)
{
    DIO_enumSetPinValue(A_u8Pin1Port, A_u8Pin1Pin, DIO_LOW);
    DIO_enumSetPinValue(A_u8Pin2Port, A_u8Pin2Pin, DIO_LOW);
}
void HDC_Motor_voidCW(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin)
{
    DIO_enumSetPinValue(A_u8Pin1Port, A_u8Pin1Pin, DIO_HIGH);
    DIO_enumSetPinValue(A_u8Pin2Port, A_u8Pin2Pin, DIO_LOW);
}
void HDC_Motor_voidCCW(uint8 A_u8Pin1Port, uint8 A_u8Pin1Pin, uint8 A_u8Pin2Port, uint8 A_u8Pin2Pin)
{
    DIO_enumSetPinValue(A_u8Pin1Port, A_u8Pin1Pin, DIO_LOW);
    DIO_enumSetPinValue(A_u8Pin2Port, A_u8Pin2Pin, DIO_HIGH);
}