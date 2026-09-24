/*
 * TIMER.c
 *
 *  Created on: Sep 21, 2026
 *      Author: Hamdi
 */

#include "TIMER.h"

static uint16 timer_prescaler[] = {0, 0, 0};
static uint32 desired_count[] = {0, 0, 0};

void (*TIMER_ptr[])(void) = {NULL, NULL, NULL};

TIMER_errorStatus TIMER0_init(uint8 mode)
{
    TIMER_errorStatus ret_val = TIMER_OK;
    switch (mode)
    {
    case TIMER0_NORMAL_MODE:
        CLR_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
#if TIMER0_OCM_INTERRUPT == ENABLE
        SET_BIT(SREG, GIE);
        SET_BIT(TIMSK, TOIE0);
#elif TIMER0_OCM_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, TOIE0);
#else
#error "Invalid NORMAL_MODE TIMER0_OCM_INTERRUPT value"
#endif
        break;
    case TIMER0_PHASE_CORRECT_MODE:
        SET_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
#if TIMER0_OC0_PIN_MODE == OC0_DISCONNECTED
        CLR_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
#elif TIMER0_OC0_PIN_MODE == OC0_CLEAR
        if (DIO_enumInitializePin(DIO_PORTB, DIO_OUTPUT, DIO_PIN3))
        {
            ret_val = TIMER_NOK;
        }
        CLR_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
#elif TIMER0_OC0_PIN_MODE == OC0_SET
        if (DIO_enumInitializePin(DIO_PORTB, DIO_OUTPUT, DIO_PIN3))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
#else
#error "Invalid PHASE_CORRECT MODE TIMER0_OC0_PIN_MODE value"
#endif
        break;
    case TIMER0_CTC_MODE:
        CLR_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
#if TIMER0_OC0_PIN_MODE == OC0_DISCONNECTED
        CLR_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
#elif TIMER0_OC0_PIN_MODE == OC0_TOGGLE
        if (DIO_enumInitializePin(DIO_PORTB, DIO_OUTPUT, DIO_PIN3))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
#elif TIMER0_OC0_PIN_MODE == OC0_CLEAR
        if (DIO_enumInitializePin(DIO_PORTB, DIO_OUTPUT, DIO_PIN3))
        {
            ret_val = TIMER_NOK;
        }
        CLR_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
#elif TIMER0_OC0_PIN_MODE == OC0_SET
        if (DIO_enumInitializePin(DIO_PORTB, DIO_OUTPUT, DIO_PIN3))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
#else
#error "Invalid CTC_MODE TIMER0_OC0_PIN_MODE value"
#endif
#if TIMER0_OCM_INTERRUPT == ENABLE
        SET_BIT(SREG, GIE);
        SET_BIT(TIMSK, OCIE0);
#elif TIMER0_OCM_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, OCIE0);
#else
#error "Invalid TIMER0_OCM_INTERRUPT value"
#endif
        break;
    case TIMER0_FAST_PWM_MODE:
        SET_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
#if TIMER0_OC0_PIN_MODE == OC0_DISCONNECTED
        CLR_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
#elif TIMER0_OC0_PIN_MODE == OC0_CLEAR
        if (DIO_enumInitializePin(DIO_PORTB, DIO_OUTPUT, DIO_PIN3))
        {
            ret_val = TIMER_NOK;
        }
        CLR_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
#elif TIMER0_OC0_PIN_MODE == OC0_SET
        if (DIO_enumInitializePin(DIO_PORTB, DIO_OUTPUT, DIO_PIN3))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
#else
#error "Invalid FAST_PWM_MODE TIMER0_OC0_PIN_MODE value"
#endif
        break;
    default:
        ret_val = TIMER_INVALID_MODE;
        break;
    }
    return ret_val;
}

TIMER_errorStatus TIMER0_setPrescaler(uint16 prescaler)
{
    TIMER_errorStatus ret_val = TIMER_OK;
    timer_prescaler[0] = prescaler;

    switch (prescaler)
    {
    case TIMER0_NO_SOURCE:
        CLR_BIT(TCCR0, CS00);
        CLR_BIT(TCCR0, CS01);
        CLR_BIT(TCCR0, CS02);
        break;
    case TIMER0_PRESCALER_1:
        SET_BIT(TCCR0, CS00);
        CLR_BIT(TCCR0, CS01);
        CLR_BIT(TCCR0, CS02);
        break;
    case TIMER0_PRESCALER_8:
        CLR_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        CLR_BIT(TCCR0, CS02);
        break;
    case TIMER0_PRESCALER_64:
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        CLR_BIT(TCCR0, CS02);
        break;
    case TIMER0_PRESCALER_256:
        CLR_BIT(TCCR0, CS00);
        CLR_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    case TIMER0_PRESCALER_1024:
        SET_BIT(TCCR0, CS00);
        CLR_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    case TIMER0_EXTERNAL_SOURCE_FALLING:
        CLR_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    case TIMER0_EXTERNAL_SOURCE_RISING:
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    default:
        ret_val = TIMER_INVALID_PRESCALER;
        break;
    }
    return ret_val;
}

TIMER_errorStatus TIMER0_setTimeMicroseconds(uint32 time, void (*fptr)(void))
{
    TIMER_errorStatus ret_val = TIMER_OK;

    if (time <= 0)
    {
        ret_val = TIMER_NOK;
    }
    else
    {
        uint32 overflow_time = 32 * timer_prescaler[0];
        float32 overflow_count = (float32)time / overflow_time;
        uint32 preload;

        if (NULL == fptr)
        {
            ret_val = TIMER_NULLPTR;
        }
        else
        {
            TIMER_ptr[0] = fptr;
            if (overflow_count < 1.0)
            {
                desired_count[0] = 1;
                preload = 256 - 256 * overflow_count;
                TCNT0 = preload;
            }
            else if (overflow_count == 1.0)
            {
                desired_count[0] = 1;
            }
            else
            {
                desired_count[0] = overflow_count;
                if ((overflow_count - (uint32)overflow_count) != 0.0)
                {
                    desired_count[0]++;
                    preload = 256 - 256 * (overflow_count - (uint32)overflow_count);
                    TCNT0 = preload;
                }
            }
        }
    }
    return ret_val;
}

TIMER_errorStatus TIMER0_setPreload(uint8 value)
{
    TIMER_errorStatus ret_val = TIMER_OK;
    if (value > 255 || value < 0)
    {
        ret_val = TIMER_NOK;
    }
    else
    {
        TCNT0 = value;
    }
    return ret_val;
}

TIMER_errorStatus TIMER0_setCompareValue(uint8 value)
{
    TIMER_errorStatus ret_val = TIMER_OK;
    if (value > 255 || value < 0)
    {
        ret_val = TIMER_NOK;
    }
    else
    {
        OCR0 = value;
    }
    return ret_val;
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    static uint32 counter = 0;
    counter++;
    if (counter == desired_count[0])
    {
        TIMER_ptr[0]();
        counter = 0;
    }
}

TIMER_errorStatus TIMER2_init(uint8 mode)
{
    TIMER_errorStatus ret_val = TIMER_OK;

    switch (mode)
    {
    case TIMER2_NORMAL_MODE:
        CLR_BIT(TCCR2, WGM20);
        CLR_BIT(TCCR2, WGM21);
#if TIMER2_OCM_INTERRUPT == ENABLE
        SET_BIT(SREG, GIE);
        SET_BIT(TIMSK, TOIE2);
#elif TIMER2_OCM_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, TOIE2);
#else
#error "Invalid NORMAL_MODE TIMER2_OCM_INTERRUPT value"
#endif
        break;
    case TIMER2_PHASE_CORRECT_MODE:
        SET_BIT(TCCR2, WGM20);
        CLR_BIT(TCCR2, WGM21);
#if TIMER2_OC2_PIN_MODE == OC2_DISCONNECTED
        CLR_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
#elif TIMER2_OC2_PIN_MODE == OC2_CLEAR
        if (DIO_enumInitializePin(DIO_PORTD, DIO_OUTPUT, DIO_PIN7))
        {
            ret_val = TIMER_NOK;
        }
        CLR_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
#elif TIMER2_OC2_PIN_MODE == OC2_SET
        if (DIO_enumInitializePin(DIO_PORTD, DIO_OUTPUT, DIO_PIN7))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
#else
#error "Invalid PHASE_CORRECT MODE TIMER2_OC0_PIN_MODE value"
#endif
        break;
    case TIMER2_CTC_MODE:
        CLR_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);
#if TIMER2_OC2_PIN_MODE == OC2_DISCONNECTED
        CLR_BIT(TCCR2, COM20);
        CLR_BIT(TCCR2, COM21);
#elif TIMER2_OC2_PIN_MODE == OC2_TOGGLE
        if (DIO_enumInitializePin(DIO_PORTD, DIO_OUTPUT, DIO_PIN7))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR2, COM20);
        CLR_BIT(TCCR2, COM21);
#elif TIMER2_OC2_PIN_MODE == OC2_CLEAR
        if (DIO_enumInitializePin(DIO_PORTD, DIO_OUTPUT, DIO_PIN7))
        {
            ret_val = TIMER_NOK;
        }
        CLR_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
#elif TIMER2_OC2_PIN_MODE == OC2_SET
        if (DIO_enumInitializePin(DIO_PORTD, DIO_OUTPUT, DIO_PIN7))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
#else
#error "Invalid CTC_MODE TIMER2_OC0_PIN_MODE value"
#endif
#if TIMER2_OCM_INTERRUPT == ENABLE
        SET_BIT(SREG, GIE);
        SET_BIT(TIMSK, TOIE2);
#elif TIMER2_OCM_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, TOIE2);
#else
#error "Invalid TIMER2_OCM_INTERRUPT value"
#endif
        break;
    case TIMER2_FAST_PWM_MODE:
        SET_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);
#if TIMER2_OC2_PIN_MODE == OC2_DISCONNECTED
        CLR_BIT(TCCR2, COM20);
        CLR_BIT(TCCR2, COM21);
#elif TIMER2_OC2_PIN_MODE == OC2_CLEAR
        if (DIO_enumInitializePin(DIO_PORTD, DIO_OUTPUT, DIO_PIN7))
        {
            ret_val = TIMER_NOK;
        }
        CLR_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
#elif TIMER2_OC2_PIN_MODE == OC2_SET
        if (DIO_enumInitializePin(DIO_PORTD, DIO_OUTPUT, DIO_PIN7))
        {
            ret_val = TIMER_NOK;
        }
        SET_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
#else
#error "Invalid FAST_PWM_MODE TIMER2_OC0_PIN_MODE value"
#endif
        break;
    default:
        ret_val = TIMER_INVALID_MODE;
        break;
    }

    return ret_val;
}

TIMER_errorStatus TIMER2_setPrescaler(uint16 prescaler)
{
    TIMER_errorStatus ret_val = TIMER_OK;
    timer_prescaler[2] = prescaler;

    switch (prescaler)
    {
    case TIMER2_NO_SOURCE:
        CLR_BIT(TCCR2, CS20);
        CLR_BIT(TCCR2, CS21);
        CLR_BIT(TCCR2, CS22);
        break;
    case TIMER2_PRESCALER_1:
        SET_BIT(TCCR2, CS20);
        CLR_BIT(TCCR2, CS21);
        CLR_BIT(TCCR2, CS22);
        break;
    case TIMER2_PRESCALER_8:
        CLR_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        CLR_BIT(TCCR2, CS22);
        break;
    case TIMER2_PRESCALER_32:
        SET_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        CLR_BIT(TCCR2, CS22);
        break;
    case TIMER2_PRESCALER_64:
        CLR_BIT(TCCR2, CS20);
        CLR_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    case TIMER2_PRESCALER_128:
        SET_BIT(TCCR2, CS20);
        CLR_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    case TIMER2_PRESCALER_256:
        CLR_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    case TIMER2_PRESCALER_1024:
        SET_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    default:
        ret_val = TIMER_INVALID_PRESCALER;
        break;
    }
    return ret_val;
}

TIMER_errorStatus TIMER2_setTimeMicroseconds(uint32 time, void (*fptr)(void))
{
    TIMER_errorStatus ret_val = TIMER_OK;

    if (time <= 0)
    {
        return TIMER_NOK;
    }
    else
    {
        uint32 overflow_time = 32 * timer_prescaler[2];
        float32 desired_overflow_count = (float32)time / overflow_time;
        uint32 preload;

        if (NULL == fptr)
        {
            ret_val = TIMER_NULLPTR;
        }
        else
        {
            TIMER_ptr[2] = fptr;
            if (desired_overflow_count < 1.0)
            {
                desired_count[2] = 1;
                preload = 256 - 256 * desired_overflow_count;
                TCNT2 = preload;
            }
            else if (desired_overflow_count == 1.0)
            {
                desired_count[2] = 1;
            }
            else
            {
                desired_count[2] = desired_overflow_count;
                if ((desired_overflow_count - (uint32)desired_overflow_count) != 0.0)
                {
                    desired_count[2]++;
                    preload = 256 - 256 * (desired_overflow_count - (uint32)desired_overflow_count);
                    TCNT2 = preload;
                }
            }
        }
    }
    return ret_val;
}

TIMER_errorStatus TIMER2_setCompareValue(uint8 value)
{
    TIMER_errorStatus ret_val = TIMER_OK;

    if (value > 255 || value < 0)
    {
        ret_val = TIMER_NOK;
    }
    else
    {
        OCR2 = value;
    }
    
    return ret_val;
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
    static uint32 counter = 0;
    counter++;
    if (counter == desired_count[2])
    {
        TIMER_ptr[2]();
        counter = 0;
    }
}
