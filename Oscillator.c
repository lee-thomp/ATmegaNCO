#include <avr/io.h>
#include <avr/interrupt.h>

#include "Prefs.h"
#include "Oscillator.h"
#include "OscillatorConfig.h"

#include "avr_debug/avr8-stub/avr8-stub.h"

/* ============= Module Typedefs ============ */ 


/* ============ Module Functions ============ */ 

/**
 * @brief	Perform setup of ADC peripheral for samplign 1v/Oct tuning voltage
 *
 * @return	Nothing
 */
void NCO_ADCSetup (void)
{
	/* Set ADC voltage reference, set ADLAR to allow for single byte ADC result, select channel */
	ADMUX	|= ADC_REF_SELECT | (1u << ADLAR) | ADC_CHANNEL_SELECT;

	/* Enable the ADC, begin a conversion, set prescaler */
	ADCSRA	|= (1u << ADEN) | (1u << ADSC) | ADC_PRESCALE_SELECT;

	/* Disable digital input on ADC pin to save power */
	DIDR0	|= (1u << ADC_CHANNEL_SELECT);
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
	TCCR1B	|= (1u << WGM12) | TIMER1_PRESCALE_SELECT;

	/* Enable Timer 1 count compare (A) ISR, and set count compare value */
	TIMSK1	|= (1u << OCIE1A);
	OCR1A 	= TIMER1_COMPARE_PERIOD;

	/* Finish setup and resume interrupts */
	sei();
}

/**
 * @brief	Setup timer 0 for outputting waveform samples
 * 			Currently configured for channel A output on pin D6
 *
 * @return Nothing
 */
static void NCO_Timer0Setup (void)
{
	/* Enable pin toggle output for PWM timers */
	DDRD |= (1u << PD6);

	/* Set both channels for toggling on compare, 
	 * set WGM01, WGM00 for fast PWM
	 * set compare mode for non-inverting PWM
	 * set prescaler to 1 (no prescaling) */
	TCCR0A	|= (1u << WGM00) | (1u << WGM01)
				| (1u << COM0A1);
	TCCR0B	|= (1u << CS00);
}

/**
 * @brief	Timer 1 Compare vector A
 * 			Read ADC tuning, increment oscillator phase, and output the phase sample
 *
 * @return Nothing
 */
ISR(TIMER1_COMPA_vect)
{
	/* Initialise oscillator */
	static uint16_t oscillatorPhase = 0u;

	/* Sample ADC tuning voltage, scan lookup table to convert to musical tones */
	oscillatorPhase += tuningIncrementTable[ADCH];

	/* Increment oscillator phase index */
	OCR0A = (uint8_t)(oscillatorPhase >> 8u);

	/* Enable ADC for next sample period */
	ADCSRA |= (1u << ADSC);
}

int main (void) 
{
	/* GDB stub init */
	debug_init();

	/* Set up peripherals */
	NCO_Timer1Setup();
	NCO_Timer0Setup();
	NCO_ADCSetup();

	/* Do nothing outside ISR */
	while (TRUE)
	{
		asm("nop");
	}
	return 0;
}
