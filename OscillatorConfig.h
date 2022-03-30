/**
 * @file	OscillatorConfig.h
 * 			Config file for the numerically controlled oscillator project.
 * 			Macros defined here should be used for compile time configuration of the module.
 *
 * @author	lee
 */

/* ========== Module Configuration ========== */ 
#define		ADC_REF_SELECT			(1u << 6u)
#define		ADC_CHANNEL_MAGIC		ADC0
#define		ADC_PRESCALE_MAGIC		(2)

/* ======== Macro Magic, Do Not Touch ======= */ 
#ifdef ADC_CHANNEL_MAGIC
	#if (ADC0 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x00u)
	#elif (ADC1 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x01u)
	#elif (ADC2 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x02u)
	#elif (ADC3 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x03u)
	#elif (ADC4 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x04u)
	#elif (ADC5 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x05u)
	#elif (ADC6 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x06u)
	#elif (ADC7 == ADC_CHANNEL_MAGIC)
		#define	ADC_CHANNEL_SELECT	(0x07u)
	#else
		#error "ADC_CHANNEL_MAGIC must be one of ADC[0-7]"
	#endif
#else
	#error "ADC_CHANNEL_MAGIC not defined"
#endif

#ifdef ADC_PRESCALE_MAGIC
	#if (2 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x00u)
	#elif (4 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x01u)
	#elif (8 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x02u)
	#elif (16 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x03u)
	#elif (32 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x04u)
	#elif (64 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x05u)
	#elif (128 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x06u)
	#elif (ADC7 == ADC_PRESCALE_MAGIC)
		#define	ADC_PRESCALE_SELECT	(0x07u)
	#else
		#error "ADC_PRESCALE_MAGIC must be one of 2, 4, 8, 16, 32, 64, or 128"
	#endif
#else
	#error "ADC_PRESCALE_MAGIC not defined"
#endif
