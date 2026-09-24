#include "EEPROM.h"

static uint8 EEPROM_waitForWriteComplete(void)
{
    uint32 L_u32Timeout = 100000UL;

    while (READ_BIT(EEPROM_EECR_REG, EEPROM_EEWE_BIT) != 0U)
    {
        if (L_u32Timeout == 0UL)
        {
            return 0U;
        }

        L_u32Timeout--;
    }

    return 1U;
}

static void EEPROM_setAddress(uint16 address)
{
    EEPROM_EEARH_REG = (uint8)(address >> 8);
    EEPROM_EEARL_REG = (uint8)address;
}

void EEPROM_writeByte(uint16 address, uint8 data)
{
    if (EEPROM_waitForWriteComplete() == 0U)
    {
        return;
    }

    EEPROM_setAddress(address);
    EEPROM_EEDR_REG = data;

    uint8 sregBackup = EEPROM_SREG_REG;
    CLR_BIT(EEPROM_SREG_REG, EEPROM_GLOBAL_INTERRUPT_BIT);

    __asm__ __volatile__(
        "sbi 0x1C, 2"
        "\n\t"
        "sbi 0x1C, 1"
        "\n\t" ::: "memory");

    EEPROM_SREG_REG = sregBackup;
}

uint8 EEPROM_readByte(uint16 address)
{
    if (EEPROM_waitForWriteComplete() == 0U)
    {
        return 0xFFU;
    }

    EEPROM_setAddress(address);

    SET_BIT(EEPROM_EECR_REG, EEPROM_EERE_BIT);

    return EEPROM_EEDR_REG;
}
