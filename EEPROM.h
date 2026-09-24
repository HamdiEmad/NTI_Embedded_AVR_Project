#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

#include "LIB/STD_TYPES.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#define EEPROM_EEARH_REG (*(volatile uint8 *)0x3FU)
#define EEPROM_EEARL_REG (*(volatile uint8 *)0x3EU)
#define EEPROM_EEDR_REG (*(volatile uint8 *)0x3DU)
#define EEPROM_EECR_REG (*(volatile uint8 *)0x3CU)
#define EEPROM_SREG_REG (*(volatile uint8 *)0x5FU)

#define EEPROM_EERE_BIT 0U
#define EEPROM_EEWE_BIT 1U
#define EEPROM_EEMWE_BIT 2U
#define EEPROM_GLOBAL_INTERRUPT_BIT 7U

void EEPROM_writeByte(uint16 address, uint8 data);
uint8 EEPROM_readByte(uint16 address);

#endif /* EEPROM_DRIVER_H_ */
