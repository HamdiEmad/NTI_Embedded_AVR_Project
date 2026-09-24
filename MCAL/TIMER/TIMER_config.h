/*
 * TIMER_config.h
 *
 *  Created on: Sep 23, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_

/* TIMER0 OCR0 pin mode
    1.OC0_DISCONNECTED
    2.OC0_TOGGLE
    3.OC0_CLEAR
    4.OC0_SET
*/
#define TIMER0_OC0_PIN_MODE OC0_CLEAR

/* TIMER0 output compare match interrupt
    1.ENABLE
    2.DISABLE
*/
#define TIMER0_OCM_INTERRUPT ENABLE


/* TIMER2 OCR2 pin mode
    1.OC2_DISCONNECTED
    2.OC2_TOGGLE
    3.OC2_CLEAR
    4.OC2_SET
*/
#define TIMER2_OC2_PIN_MODE OC2_CLEAR

/* TIMER2 output compare match interrupt
    1.ENABLE
    2.DISABLE
*/
#define TIMER2_OCM_INTERRUPT ENABLE

#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */