#include "PB.h"
#include "MCAL/DIO/DIO.h"

#include "util/delay.h"

void HPB_voidInit(void)
{
    uint8 L_u8ButtonId;

    for (L_u8ButtonId = 0U; L_u8ButtonId < PB_NUM; L_u8ButtonId++)
    {
        DIO_enumInitializePin(PB_PORT, DIO_INPUT_PULLUP, PB_FIRST_PIN + L_u8ButtonId);
    }
}

uint8 HPB_u8ReadPin(uint8 A_u8ButtonId)
{
    sint8 L_s8FirstReading;
    sint8 L_s8SecondReading;

    if (A_u8ButtonId >= PB_NUM)
    {
        return PB_NOT_PRESSED;
    }

    DIO_enumReadPinValue(PB_PORT, PB_FIRST_PIN + A_u8ButtonId, &L_s8FirstReading);
    _delay_ms(PB_DEBOUNCE_TIME_MS);
    DIO_enumReadPinValue(PB_PORT, PB_FIRST_PIN + A_u8ButtonId, &L_s8SecondReading);

    if (L_s8FirstReading == L_s8SecondReading && L_s8SecondReading == PB_PRESSED)
    {
        return PB_PRESSED;
    }

    return PB_NOT_PRESSED;
}
