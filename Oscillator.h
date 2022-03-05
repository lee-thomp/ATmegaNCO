/**
 * @file	Oscillator.h
 * 			Header file for main module, should serve to keep main module code tidy along with OscillatorConfig.h
 *
 * @author	lee
 */
#ifndef OSCILLATOR_H
#define OSCILLATOR_H


/* ============== Module Macros ============= */ 

/* Targeting 44.1kHz output sample rate 
 * TODO: See if we really need 44.1kHz ISR */
#define TIMER1_COMPARE_PERIOD        (362u)
#define TIMER1_PRESCALE_SELECT       (0x01u)


/* ============= Module Typedefs ============ */ 


/* =============== Lookup Data ============== */ 

/* Pre-calculated quarter-sine lookup table 
 * Could be formatted as a single column list, but this makes navigation easier*/
uint8_t const QuarterSineTable[256] = {
	0u,		1u,		3u,		4u,		6u,		7u,		9u,		10u, 	12u,	14u,	15u,	17u,	18u,	20u,	21u,	23u,
	25u,	26u,	28u,	29u,	31u,	32u,	34u,	36u, 	37u,	39u,	40u,	42u,	43u,	45u,	46u,	48u,
	49u,	51u,	53u,	54u,	56u,	57u,	59u,	60u, 	62u,	63u,	65u,	66u,	68u,	69u,	71u,	72u,
	74u,	75u,	77u,	78u,	80u,	81u,	83u,	84u, 	86u,	87u,	89u,	90u,	92u,	93u,	95u,	96u,
	97u,	99u,	100u,	102u,	103u,	105u,	106u,	108u, 	109u,	110u,	112u,	113u,	115u,	116u,	117u,	119u,
	120u,	122u,	123u,	124u,	126u,	127u,	128u,	130u, 	131u,	132u,	134u,	135u,	136u,	138u,	139u,	140u,
	142u,	143u,	144u,	146u,	147u,	148u,	149u,	151u, 	152u,	153u,	155u,	156u,	157u,	158u,	159u,	161u,
	162u,	163u,	164u,	166u,	167u,	168u,	169u,	170u, 	171u,	173u,	174u,	175u,	176u,	177u,	178u,	179u,
	181u,	182u,	183u,	184u,	185u,	186u,	187u,	188u, 	189u,	190u,	191u,	192u,	193u,	194u,	195u,	196u,
	197u,	198u,	199u,	200u,	201u,	202u,	203u,	204u, 	205u,	206u,	207u,	208u,	209u,	210u,	211u,	211u,
	212u,	213u,	214u,	215u,	216u,	217u,	217u,	218u, 	219u,	220u,	221u,	221u,	222u,	223u,	224u,	225u,
	225u,	226u,	227u,	227u,	228u,	229u,	230u,	230u, 	231u,	232u,	232u,	233u,	234u,	234u,	235u,	235u,
	236u,	237u,	237u,	238u,	238u,	239u,	239u,	240u, 	241u,	241u,	242u,	242u,	243u,	243u,	244u,	244u,
	244u,	245u,	245u,	246u,	246u,	247u,	247u,	247u, 	248u,	248u,	249u,	249u,	249u,	250u,	250u,	250u,
	251u,	251u,	251u,	251u,	252u,	252u,	252u,	252u, 	253u,	253u,	253u,	253u,	254u,	254u,	254u,	254u,
	254u,	254u,	255u,	255u,	255u,	255u,	255u,	255u, 	255u,	255u,	255u,	255u,	255u,	255u,	255u,	255u
}; 

#endif /* OSCILLATOR_H */
