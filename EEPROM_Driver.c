#include "EEPROM_Driver.h"

void EEPROM_writeByte(uint16_t uiAddress, uint8_t ucData)
{
    while ((EECR & (1U << EEWE)) != 0U)
    {
    }

    EEARH = (uint8_t)((uiAddress >> 8) & 0x03U);
    EEARL = (uint8_t)(uiAddress & 0xFFU);

    EEDR = ucData;

    EECR |= (1U << EEMWE);

    uint8_t ucSREG_backup = SREG;
    cli();

    EECR |= (1U << EEWE);

    SREG = ucSREG_backup;
}

uint8_t EEPROM_readByte(uint16_t uiAddress)
{
    while ((EECR & (1U << EEWE)) != 0U)
    {
    }

    EEARH = (uint8_t)((uiAddress >> 8) & 0x03U);
    EEARL = (uint8_t)(uiAddress & 0xFFU);

    EECR |= (1U << EERE);

    return EEDR;
}

void EEPROM_saveCurrentFloor(uint8_t floor)
{
    uint8_t ucStoredFloor;

    if (floor > ELEVATOR_FLOOR_MAX)
    {
        floor = ELEVATOR_FLOOR_MAX;
    }

    ucStoredFloor = EEPROM_readByte(EEPROM_ADDR_CURRENT_FLOOR);

    if (ucStoredFloor != floor)
    {
        EEPROM_writeByte(EEPROM_ADDR_CURRENT_FLOOR, floor);
    }
}

uint8_t EEPROM_getSavedFloor(void)
{
    uint8_t ucSavedFloor = EEPROM_readByte(EEPROM_ADDR_CURRENT_FLOOR);

    if ((ucSavedFloor == EEPROM_ERASED_VALUE) || (ucSavedFloor > ELEVATOR_FLOOR_MAX))
    {
        ucSavedFloor = ELEVATOR_FLOOR_DEFAULT;
    }

    return ucSavedFloor;
}
