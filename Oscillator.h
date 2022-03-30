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
uint8_t const quarterSineTable[256] = {
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

/* Pre-calculated increment values that spans C0 to E6 */
uint16_t const tuningIncrementTable[256] = {
	48u,	49u,	50u,	50u,	51u,	52u,	53u,	53u,	54u,	55u,	56u,	57u,	57u,	58u,	59u,	60u,
	61u,	62u,	63u,	63u,	64u,	65u,	66u,	67u,	68u,	69u,	70u,	71u,	72u,	73u,	74u,	75u,
	77u,	78u,	79u,	80u,	81u,	82u,	83u,	85u,	86u,	87u,	88u,	90u,	91u,	92u,	94u,	95u,
	96u,	98u,	99u,	101u,	102u,	104u,	105u,	107u,	108u,	110u,	111u,	113u,	115u,	116u,	118u,	120u,
	122u,	123u,	125u,	127u,	129u,	131u,	133u,	134u,	136u,	138u,	140u,	142u,	144u,	147u,	149u,	151u,
	153u,	155u,	158u,	160u,	162u,	165u,	167u,	169u,	172u,	174u,	177u,	179u,	182u,	185u,	187u,	190u,
	193u,	196u,	199u,	201u,	204u,	207u,	210u,	213u,	217u,	220u,	223u,	226u,	229u,	233u,	236u,	240u,
	243u,	247u,	250u,	254u,	257u,	261u,	265u,	269u,	273u,	277u,	281u,	285u,	289u,	293u,	297u,	302u,
	306u,	311u,	315u,	320u,	324u,	329u,	334u,	339u,	344u,	349u,	354u,	359u,	364u,	369u,	375u,	380u,
	386u,	391u,	397u,	403u,	409u,	415u,	421u,	427u,	433u,	439u,	446u,	452u,	459u,	465u,	472u,	479u,
	486u,	493u,	500u,	508u,	515u,	522u,	530u,	538u,	546u,	553u,	562u,	570u,	578u,	586u,	595u,	604u,
	612u,	621u,	630u,	639u,	649u,	658u,	668u,	677u,	687u,	697u,	707u,	718u,	728u,	739u,	750u,	760u,
	772u,	783u,	794u,	806u,	817u,	829u,	841u,	854u,	866u,	879u,	891u,	904u,	918u,	931u,	944u,	958u,
	972u,	986u,	1001u,	1015u,	1030u,	1045u,	1060u,	1075u,	1091u,	1107u,	1123u,	1139u,	1156u,	1173u,	1190u,	1207u,
	1225u,	1243u,	1261u,	1279u,	1298u,	1316u,	1336u,	1355u,	1375u,	1395u,	1415u,	1436u,	1456u,	1478u,	1499u,	1521u,
	1543u,	1566u,	1588u,	1611u,	1635u,	1659u,	1683u,	1707u,	1732u,	1757u,	1783u,	1809u,	1835u,	1862u,	1889u,	1916u,
};

#endif /* OSCILLATOR_H */
