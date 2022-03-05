#include <avr/io.h>
#include <avr/interrupt.h>

#include "../Prefs.h"
#include "Oscillator.h"
#include "OscillatorConfig.h"

#include "avr_debug/avr8-stub/avr8-stub.h"

/**
 * @brief	Perform setup of ADC peripheral for samplign 1v/Oct tuning voltage
 *
 * @return	Nothing
 */
void NCO_ADCSetup (void)
{
	/* Set ADC voltage reference, set ADLAR to allow for single byte ADC result, select channel
	 * TODO: check which reference is most correct for arduino nano */
	ADMUX	|= ADC_REF_SELECT | (1 << ADLAR) | ADC_CHANNEL_SELECT;

	/* Enable the ADC, begin a conversion, set prescaler */
	ADCSRA	|= (1 << ADEN) | (1 << ADSC) | ADC_PRESCALE_SELECT;

	/* Disable digital input on ADC pin to save power */
	DIDR0	|= (1 << ADC_CHANNEL_SELECT);
}

/**
 * @brief	Perform setup of Timer 1 peripheral for ISR usage
 *
 * @return 	Nothing
 */
static void NCO_Timer1Setup (void)
{
	/* Disable interrupts while setting up */
	cli();

	/* Disconnect timer output compare pins, set timer mode to counter compare,
	 * and apply prescaler macro */
	TCCR1A	|= 0x00u;
	TCCR1B	|= (1 << WGM12) | TIMER1_PRESCALE_SELECT;

	/* Enable Timer 1 count compare (A) ISR, and set count compare value */
	TIMSK1	|= (1 << OCIE1A);
	OCR1A 	= TIMER1_COMPARE_PERIOD;

	/* Finish setup and resume interrupts */
	sei();
}

/**
 * @brief	Setup timer 0 and 2 for outputting waveform samples
 *
 * @return Nothing
 */
static void NCO_Timer0Timer2Setup (void)
{
	/* Set both channels for toggling on compare, leave WGM0x at 0 */
	TCCR0A	|= (1 << COM0A0) | (1 << COM0B0);
	TCCR0B	|= TIMER0_PRESCALE_SELECT;
	/* TODO: Investigate output timer prescaling */
}

/**
 * @brief	Timer 1 Compare vector A
 * 			Output previous sample, read ADC tuning and program information and assemble next sample.
 *
 * @return Nothing
 */
ISR(TIMER1_COMPA_vect)
{
	/* TODO: Figure out general calculation for all waveforms, define wave data struct */
	/* Initialise ISR-only variables */
	static outputSample = 0x00u;

	uint8_t note_Voct = ADCH >> 2u;

	ADCSRA |= (1 << ADSC);
}

int main (void) 
{
	/* GDB stub init */
	debug_init();

	/* Set up - disable interrupts */
	NCO_Timer1Setup();
	NCO_ADCSetup();

	/* Do nothing outside ISR */
	while (TRUE)
	{
		asm("nop");
	}
	return 0;
}
