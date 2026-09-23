/*
 * TIMER.h
 *
 *  Created on: Sep 21, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include <stdlib.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO.h"
#include "TIMER_config.h"

typedef enum
{
    TIMER_OK = 0,
    TIMER_NOK,
    TIMER_INVALID_MODE,
    TIMER_INVALID_PRESCALER,
    TIMER_NULLPTR
} TIMER_errorStatus;

// TIMER interrupts
#define DISABLE 0
#define ENABLE 1

// TIMER0 modes
#define TIMER0_NORMAL_MODE 0
#define TIMER0_PHASE_CORRECT_MODE 1
#define TIMER0_CTC_MODE 2
#define TIMER0_FAST_PWM_MODE 3

// TIMER0 pin (OC0)
#define OC0_DISCONNECTED 0
#define OC0_TOGGLE 1
#define OC0_CLEAR 2
#define OC0_SET 3

// TIMER2 pin (OC2)
#define OC2_DISCONNECTED 0
#define OC2_TOGGLE 1
#define OC2_CLEAR 2
#define OC2_SET 3

// TCCR0 bits
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 7

// TIMER0 prescalers
#define TIMER0_NO_SOURCE 0
#define TIMER0_PRESCALER_1 1
#define TIMER0_PRESCALER_8 8
#define TIMER0_PRESCALER_64 64
#define TIMER0_PRESCALER_256 256
#define TIMER0_PRESCALER_1024 1024
#define TIMER0_EXTERNAL_SOURCE_FALLING 2
#define TIMER0_EXTERNAL_SOURCE_RISING 3

// TIMSK bits
#define TOIE0 0
#define OCIE0 1
#define TOIE2 6
#define OCIE2 7

// TIFR bits
#define TOV0 0
#define OCF0 0
#define TOV2 6
#define OCF2 7

// SFIOR bit
#define PSR10 0
#define PSR2 1

#define GIE 7

// TCCR2 bits
#define CS20 0
#define CS21 1
#define CS22 2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6

// TIMER2 prescalers
#define TIMER2_NO_SOURCE 0
#define TIMER2_PRESCALER_1 1
#define TIMER2_PRESCALER_8 8
#define TIMER2_PRESCALER_32 32
#define TIMER2_PRESCALER_64 64
#define TIMER2_PRESCALER_128 128
#define TIMER2_PRESCALER_256 256
#define TIMER2_PRESCALER_1024 1024

// TIMER2 modes
#define TIMER2_NORMAL_MODE 0
#define TIMER2_PHASE_CORRECT_MODE 1
#define TIMER2_CTC_MODE 2
#define TIMER2_FAST_PWM_MODE 3

#define TCCR0 *((volatile uint8 *)0x53)
#define TCNT0 *((volatile uint8 *)0x52)
#define OCR0 *((volatile uint8 *)0x5C)

#define TCCR2 *((volatile uint8 *)0x45)
#define TCNT2 *((volatile uint8 *)0x44)
#define OCR2 *((volatile uint8 *)0x43)

#define TIMSK *((volatile uint8 *)0x59)
#define SREG *((volatile uint8 *)0x5F)

TIMER_errorStatus TIMER0_init(uint8 mode);
TIMER_errorStatus TIMER0_setPrescaler(uint16 prescaler);
TIMER_errorStatus TIMER0_setPreload(uint8 value);
TIMER_errorStatus TIMER0_setTimeMicroseconds(uint32 time, void (*fptr)(void));
TIMER_errorStatus TIMER0_setCompareValue(uint8 value);

TIMER_errorStatus TIMER2_init(uint8 mode);
TIMER_errorStatus TIMER2_setPrescaler(uint16 prescaler);
TIMER_errorStatus TIMER2_setPreload(uint8 value);
TIMER_errorStatus TIMER2_setTimeMicroseconds(uint32 time, void (*fptr)(void));
TIMER_errorStatus TIMER2_setCompareValue(uint8 value);

#endif /* MCAL_TIMER_TIMER_H_ */
