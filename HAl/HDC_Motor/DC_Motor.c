// DC_Motor.c

#include "../../LIB/BitMath.h"
#include "../../LIB/STD_types.h"

#include "../../MCAL/MDIO/DIO.h"

void HDC_Motor_voidInit (u8 A_u8Pin1Port , u8 A_u8Pin1Pin , u8 A_u8Pin2Port , u8 A_u8Pin2Pin)
{
	MDIO_voidInitPin(A_u8Pin1Port , A_u8Pin1Pin , DIO_OUTPUT) ;
	MDIO_voidInitPin(A_u8Pin2Port , A_u8Pin2Pin , DIO_OUTPUT) ;
}
void HDC_Motor_voidStop (u8 A_u8Pin1Port , u8 A_u8Pin1Pin , u8 A_u8Pin2Port , u8 A_u8Pin2Pin)
{
	MDIO_voidSetPinValue(A_u8Pin1Port , A_u8Pin1Pin , DIO_LOW) ;
	MDIO_voidSetPinValue(A_u8Pin2Port , A_u8Pin2Pin , DIO_LOW) ;
}
void HDC_Motor_voidCW (u8 A_u8Pin1Port , u8 A_u8Pin1Pin , u8 A_u8Pin2Port , u8 A_u8Pin2Pin)
{
	MDIO_voidSetPinValue(A_u8Pin1Port , A_u8Pin1Pin , DIO_HIGH) ;
	MDIO_voidSetPinValue(A_u8Pin2Port , A_u8Pin2Pin , DIO_LOW) ;
}
void HDC_Motor_voidCCW (u8 A_u8Pin1Port , u8 A_u8Pin1Pin , u8 A_u8Pin2Port , u8 A_u8Pin2Pin)
{
	MDIO_voidSetPinValue(A_u8Pin1Port , A_u8Pin1Pin , DIO_LOW) ;
	MDIO_voidSetPinValue(A_u8Pin2Port , A_u8Pin2Pin , DIO_HIGH) ;
}
