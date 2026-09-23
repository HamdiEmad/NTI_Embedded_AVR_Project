#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define EEPROM_ADDR_CURRENT_FLOOR   ((uint16_t)0x0000U)

#define ELEVATOR_FLOOR_MIN          ((uint8_t)0U)
#define ELEVATOR_FLOOR_MAX          ((uint8_t)4U)
#define ELEVATOR_FLOOR_DEFAULT      ((uint8_t)0U)
#define EEPROM_ERASED_VALUE         ((uint8_t)0xFFU)

void EEPROM_writeByte(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_readByte(uint16_t uiAddress);

void EEPROM_saveCurrentFloor(uint8_t floor);
uint8_t EEPROM_getSavedFloor(void);

#endif /* EEPROM_DRIVER_H_ */
