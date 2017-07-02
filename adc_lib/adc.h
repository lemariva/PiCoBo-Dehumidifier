/*
 * adc.h
 *
 *  Created on: 11.05.2015
 *      Author: MauroHernán
 */

#ifndef ADC_H_
#define ADC_H_

class adc {

public:
	adc(int dummy);
	unsigned int getValue();
	void initReadValue();
private:
	void Single_Measure_REF (unsigned int chan, unsigned int ref);
	void Single_Measure (unsigned int chan);
	unsigned int  ADCValue;
	bool ADCLowRef;
	unsigned int ADCValue_volts;
};


#endif /* ADC_H_ */
