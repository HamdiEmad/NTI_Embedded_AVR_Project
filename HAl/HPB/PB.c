// PB.c


#include "../../LIB/BitMath.h"
#include "../../LIB/STD_types.h"

#include "../../MCAL/MDIO/DIO.h"

#include "PB.h"

#include "util/delay.h"

static const u8 PB_arr[PB_NUM][2] =
{
    {DIO_PORTC , DIO_PIN0} ,
    {DIO_PORTC , DIO_PIN1} ,
    {DIO_PORTC , DIO_PIN2} ,
    {DIO_PORTC , DIO_PIN3} ,
    {DIO_PORTC , DIO_PIN4}
} ;


void HPB_voidInit  (void)
{
	u8 L_u8Index ;
	    for (L_u8Index = 0 ; L_u8Index < PB_NUM ; L_u8Index++)
	    {
	        MDIO_voidInitPin    (PB_arr[L_u8Index][0] , PB_arr[L_u8Index][1] , DIO_INPUT) ;
	        MDIO_voidSetPinValue(PB_arr[L_u8Index][0] , PB_arr[L_u8Index][1] , DIO_HIGH ) ;
	    }
}
u8   HPB_u8ReadPin (u8 A_u8pbId)
{
	u8 L_u8PbStatues = PB_NOT_PRESSED ;
	if (A_u8pbId < PB_NUM)
	{
		if (MDIO_u8ReadPin(PB_arr[A_u8pbId][0] , PB_arr[A_u8pbId][1]) == PB_PRESSED)
		{
			_delay_ms(50) ;
			if (MDIO_u8ReadPin(PB_arr[A_u8pbId][0] , PB_arr[A_u8pbId][1]) == PB_PRESSED)
			{
				L_u8PbStatues = PB_PRESSED ;
				while (MDIO_u8ReadPin(PB_arr[A_u8pbId][0] , PB_arr[A_u8pbId][1]) == PB_PRESSED) ;
				_delay_ms(50) ;
			}
			else
			{
				L_u8PbStatues = PB_NOT_PRESSED ;
			}
		}
	}
return  L_u8PbStatues ;
}
