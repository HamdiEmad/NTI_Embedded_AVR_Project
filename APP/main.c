#include "HAL/PB/PB.h"
#include "HAL/DC_MOTOR/DC_MOTOR.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/EEPROM/EEPROM.h"
#include <util/delay.h>

#define FLOOR_COUNT 5U
#define FIRST_FLOOR 1U
#define EEPROM_FLOOR_ADDRESS 0x0050U

#define MOTOR_PORT DIO_PORTC
#define MOTOR_CW_PIN DIO_PIN5
#define MOTOR_CCW_PIN DIO_PIN6

#define FLOOR_LED_PORT DIO_PORTD

static void APP_voidSetFloorLed(uint8 A_u8Floor)
{
    DIO_enumSetPortValue(FLOOR_LED_PORT, DIO_LOW);
    DIO_enumSetPinValue(FLOOR_LED_PORT, A_u8Floor - FIRST_FLOOR, DIO_HIGH);
}

static void APP_voidDisplayFloor(uint8 A_u8Floor)
{
    HLCD_voidClrDisplay();
    HLCD_voidSendStr((uint8 *)"CURRENT FLOOR");
    HLCD_voidSetCursor(LCD_ROW1, LCD_COL0);

    switch (A_u8Floor)
    {
    case 1U:
        HLCD_voidSendStr((uint8 *)"FLOOR 1");
        break;
    case 2U:
        HLCD_voidSendStr((uint8 *)"FLOOR 2");
        break;
    case 3U:
        HLCD_voidSendStr((uint8 *)"FLOOR 3");
        break;
    case 4U:
        HLCD_voidSendStr((uint8 *)"FLOOR 4");
        break;
    default:
        HLCD_voidSendStr((uint8 *)"FLOOR 5");
        break;
    }
}

static void APP_voidDisplayMoving(uint8 A_u8TargetFloor, uint8 A_u8GoingUp)
{
    HLCD_voidClrDisplay();
    HLCD_voidSendStr(A_u8GoingUp ? (uint8 *)"GOING UP" : (uint8 *)"GOING DOWN");
    HLCD_voidSetCursor(LCD_ROW1, LCD_COL0);
    HLCD_voidSendStr((uint8 *)"TARGET FLOOR ");
    HLCD_voidSendData('0' + A_u8TargetFloor);
}

static uint8 APP_u8ReadRequestedFloor(void)
{
    uint8 L_u8ButtonId;

    for (L_u8ButtonId = 0U; L_u8ButtonId < PB_NUM; L_u8ButtonId++)
    {
        if (HPB_u8ReadPin(L_u8ButtonId) == PB_PRESSED)
        {
            return L_u8ButtonId + FIRST_FLOOR;
        }
    }

    return 0U;
}

int main(void)
{
    uint8 L_u8CurrentFloor;
    uint8 L_u8TargetFloor;
    uint8 L_u8RequestedFloor;

    HPB_voidInit();
    DIO_enumInitializePort(FLOOR_LED_PORT, DIO_OUTPUT);
    HDC_Motor_voidInit(MOTOR_PORT, MOTOR_CW_PIN, MOTOR_PORT, MOTOR_CCW_PIN);
    HLCD_voidInit();

    L_u8CurrentFloor = EEPROM_readByte(EEPROM_FLOOR_ADDRESS);
    if (L_u8CurrentFloor < FIRST_FLOOR || L_u8CurrentFloor > FLOOR_COUNT)
    {
        L_u8CurrentFloor = FIRST_FLOOR;
        EEPROM_writeByte(EEPROM_FLOOR_ADDRESS, L_u8CurrentFloor);
    }

    APP_voidSetFloorLed(L_u8CurrentFloor);
    APP_voidDisplayFloor(L_u8CurrentFloor);

    while (1)
    {
        L_u8RequestedFloor = APP_u8ReadRequestedFloor();
        if (L_u8RequestedFloor == 0U || L_u8RequestedFloor == L_u8CurrentFloor)
        {
            continue;
        }

        L_u8TargetFloor = L_u8RequestedFloor;
        while (L_u8CurrentFloor != L_u8TargetFloor)
        {
            if (L_u8TargetFloor > L_u8CurrentFloor)
            {
                HDC_Motor_voidCW(MOTOR_PORT, MOTOR_CW_PIN, MOTOR_PORT, MOTOR_CCW_PIN);
                APP_voidDisplayMoving(L_u8TargetFloor, 1U);
                _delay_ms(1000);
                L_u8CurrentFloor++;
            }
            else
            {
                HDC_Motor_voidCCW(MOTOR_PORT, MOTOR_CW_PIN, MOTOR_PORT, MOTOR_CCW_PIN);
                APP_voidDisplayMoving(L_u8TargetFloor, 0U);
                _delay_ms(1000);
                L_u8CurrentFloor--;
            }

            HDC_Motor_voidStop(MOTOR_PORT, MOTOR_CW_PIN, MOTOR_PORT, MOTOR_CCW_PIN);
            EEPROM_writeByte(EEPROM_FLOOR_ADDRESS, L_u8CurrentFloor);
            APP_voidSetFloorLed(L_u8CurrentFloor);
        }

        HDC_Motor_voidStop(MOTOR_PORT, MOTOR_CW_PIN, MOTOR_PORT, MOTOR_CCW_PIN);
        APP_voidSetFloorLed(L_u8CurrentFloor);
        APP_voidDisplayFloor(L_u8CurrentFloor);
    }
}
