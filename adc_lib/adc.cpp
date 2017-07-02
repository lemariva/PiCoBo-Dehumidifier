/*
 * adc.cpp
 *
 *  Created on: 11.05.2015
 *      Author: MauroHernán
 */
#include <msp430.h>
#include "adc.h"

adc::adc(int dummy) {
	ADCLowRef = 1;
}

/**
* Reads ADC 'chan' once using AVCC as the reference.
**/
void adc::Single_Measure(unsigned int chan)
{
	ADC10CTL0 &= ~ENC;							// Disable ADC
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;	// 16 clock ticks, ADC On, enable ADC interrupt
	ADC10CTL1 = ADC10SSEL_3 + chan;				// Set 'chan', SMCLK
	ADC10CTL0 |= ENC + ADC10SC;             	// Enable and start conversion
}

/**
* Reads ADC 'chan' once using an internal reference, 'ref' determines if the
*   2.5V or 1.5V reference is used.
**/
void adc::Single_Measure_REF(unsigned int chan, unsigned int ref)
{
	ADC10CTL0 &= ~ENC;							// Disable ADC
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ref + ADC10IE;	// Use reference,
																		//   16 clock ticks, internal reference on
																		//   ADC On, enable ADC interrupt, Internal  = 'ref'
	ADC10CTL1 = ADC10SSEL_3 + chan;				// Set 'chan', SMCLK
	__delay_cycles (128);						// Delay to allow Ref to settle
	ADC10CTL0 |= ENC + ADC10SC; 				// Enable and start conversion
}

unsigned int adc::getValue()
{
	ADCValue = ADC10MEM;			// Saves measured value.

	if(ADCLowRef == 1) {
		ADCValue_volts = ((unsigned long)ADCValue * 3000) / 1024; // convert value to mV
	} else {
		ADCValue_volts = ((unsigned long)ADCValue * 5000) / 1024; // convert value to mV
	}

	if(ADCValue == 0x3ff)
		ADCLowRef = 0;
	if(ADCValue == 0)
		ADCLowRef = 1;

	return ADCValue_volts;
}

void adc::initReadValue()
{
	//	start conversion internal voltage
	if(ADCLowRef == 1){
		Single_Measure_REF(INCH_11, 0);		//  measure Vcc/2 with 1.5V reference (Vcc < 3V )
	} else {
		Single_Measure_REF(INCH_11, REF2_5V);	// measure Vcc/2 with 2.5V reference (Vcc > 3V )
	}
}



