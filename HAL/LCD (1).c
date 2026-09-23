/*
 * LCD.c
 *
 *  Created on: Sep 21, 2026
 *      Author: win 10
 */
#include "LCD.h"
#include <util/delay.h>
void HLCD_voidInit(void)
{
#if LCD_MODE == 8
    _delay_ms(40);
    DIO_enumInitializePort(LCD_DATA_PORT, DIO_OUTPUT);
    DIO_enumInitializePin(LCD_RS_PORT, DIO_OUTPUT, LCD_RS_PIN);
    DIO_enumInitializePin(LCD_RW_PORT, DIO_OUTPUT, LCD_RW_PIN);
    DIO_enumInitializePin(LCD_E_PORT, DIO_OUTPUT, LCD_E_PIN);
    HLCD_voidSendCmd(0x38);
    _delay_ms(1);
    HLCD_voidSendCmd(0x0E);
    _delay_ms(1);
    HLCD_voidSendCmd(0x01);
    _delay_ms(4);
    HLCD_voidSendCmd(0x06);
    _delay_ms(1);
#elif LCD_MODE == 4
    _delay_ms(40);
    DIO_enumInitializePin(LCD_DATA_PORT, DIO_OUTPUT, DIO_PIN4);
    DIO_enumInitializePin(LCD_DATA_PORT, DIO_OUTPUT, DIO_PIN5);
    DIO_enumInitializePin(LCD_DATA_PORT, DIO_OUTPUT, DIO_PIN6);
    DIO_enumInitializePin(LCD_DATA_PORT, DIO_OUTPUT, DIO_PIN7);
    DIO_enumInitializePin(LCD_RS_PORT, DIO_OUTPUT, LCD_RS_PIN);
    DIO_enumInitializePin(LCD_RW_PORT, DIO_OUTPUT, LCD_RW_PIN);
    DIO_enumInitializePin(LCD_E_PORT, DIO_OUTPUT, LCD_E_PIN);
    HLCD_voidSendCmd(0x02);
    _delay_ms(1);
    HLCD_voidSendCmd(0x28);
    _delay_ms(1);
    HLCD_voidSendCmd(0x0E);
    _delay_ms(1);
    HLCD_voidSendCmd(0x01);
    _delay_ms(4);
    HLCD_voidSendCmd(0x06);
    _delay_ms(1);

#else
#error "invalid LCD_MODE"
#endif
}
void HLCD_voidSendData(uint8 A_u8Data)
{
#if LCD_MODE == 8
    DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH);
    DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_enumSetPortValue(LCD_DATA_PORT, A_u8Data);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(1);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(1);
#elif LCD_MODE == 4
    DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH);
    DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN4, READ_BIT(A_u8Data, 4));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN5, READ_BIT(A_u8Data, 5));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN6, READ_BIT(A_u8Data, 6));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN7, READ_BIT(A_u8Data, 7));
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(1);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(1);

    DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH);
    DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN4, READ_BIT(A_u8Data, 0));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN5, READ_BIT(A_u8Data, 1));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN6, READ_BIT(A_u8Data, 2));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN7, READ_BIT(A_u8Data, 3));
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(1);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(1);
#endif
}
void HLCD_voidSendCmd(uint8 A_u8Cmd)
{
#if LCD_MODE == 8
    DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW);
    DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_enumSetPortValue(LCD_DATA_PORT, A_u8Cmd);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(1);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(1);
#elif LCD_MODE == 4
    DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW);
    DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN4, READ_BIT(A_u8Cmd, 4));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN5, READ_BIT(A_u8Cmd, 5));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN6, READ_BIT(A_u8Cmd, 6));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN7, READ_BIT(A_u8Cmd, 7));
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(1);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(1);

    DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW);
    DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN4, READ_BIT(A_u8Cmd, 0));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN5, READ_BIT(A_u8Cmd, 1));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN6, READ_BIT(A_u8Cmd, 2));
    DIO_enumSetPinValue(LCD_DATA_PORT, DIO_PIN7, READ_BIT(A_u8Cmd, 3));
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(1);
    DIO_enumSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(1);
#endif
}
void HLCD_voidSendStr(uint8 *AP_u8str)
{
    uint8 L_u8Iterator = 0;
    while (AP_u8str[L_u8Iterator] != '\0')
    {
        HLCD_voidSendData(AP_u8str[L_u8Iterator]);
        L_u8Iterator++;
    }
}
void HLCD_voidClrDisplay(void)
{
    HLCD_voidSendCmd(0x01);
    _delay_ms(4);
}
void HLCD_voidShiftLeft(void)
{
    HLCD_voidSendCmd(0x18);
    _delay_ms(1);
}
void HLCD_voidShiftRight(void)
{
    HLCD_voidSendCmd(0x1C);
    _delay_ms(1);
}
void HLCD_voidSetCursor(uint8 A_u8Row, uint8 A_u8Col)
{
    uint8 L_u8AC;
    if (A_u8Row == LCD_ROW0)
    {
        L_u8AC = A_u8Col;
    }
    else if (A_u8Row == LCD_ROW1)
    {
        L_u8AC = 0x40 + A_u8Col;
    }
    HLCD_voidSendCmd(L_u8AC + 0x80);
}
void HLCD_voidSendCustomChar(uint8 arr[], uint8 A_u8BlockNumber, uint8 A_u8Row, uint8 A_u8Col)
{
    uint8 L_u8Iterator;
    HLCD_voidSendCmd(A_u8BlockNumber * 8 + 0x40);
    for (L_u8Iterator = 0; L_u8Iterator < 8; L_u8Iterator++)
    {
        HLCD_voidSendData(arr[L_u8Iterator]);
    }
    HLCD_voidSetCursor(A_u8Row, A_u8Col);
    HLCD_voidSendData(A_u8BlockNumber);
}