/*
	Copyright [2016] [Mauro Riva -lemariva@gmail.com- <http://lemariva.com>]

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#include "gpio.h"

#define CSN_EN nrfCSNportout &= ~nrfCSNpin
#define CSN_DIS nrfCSNportout |= nrfCSNpin
#define CE_EN nrfCEportout |= nrfCEpin
#define CE_DIS nrfCEportout &= ~nrfCEpin

#define PORT_CSN_CE P2OUT
//
void GPIO::open(int pin, int DDR)
{
//	// Setup IRQ port - not used -
//	#if nrfIRQport == 1
//		P1DIR &= ~nrfIRQpin;  // IRQ line is input
//		P1OUT |= nrfIRQpin;   // Pull-up resistor enabled
//		P1REN |= nrfIRQpin;
//		P1IES |= nrfIRQpin;   // Trigger on falling-edge
//		P1IFG &= ~nrfIRQpin;  // Clear any outstanding IRQ
//		P1IE |= nrfIRQpin;    // Enable IRQ interrupt
//	#elif nrfIRQport == 2
//		P2DIR &= ~nrfIRQpin;  // IRQ line is input
//		P2OUT |= nrfIRQpin;   // Pull-up resistor enabled
//		P2REN |= nrfIRQpin;
//		P2IES |= nrfIRQpin;   // Trigger on falling-edge
//		P2IFG &= ~nrfIRQpin;  // Clear any outstanding IRQ
//		P2IE |= nrfIRQpin;    // Enable IRQ interrupt
//	#endif

	if(pin == nrfCSNpin)
	{
		// Setup CSN
		#if nrfCSNport == 1
			P1DIR |= nrfCSNpin;
		#elif nrfCSNport == 2
			P2DIR |= nrfCSNpin;
		#elif nrfCSNport == 3
			P3DIR |= nrfCSNpin;
		#elif nrfCSNport == J
			PJDIR |= nrfCSNpin;
		#endif
		CSN_DIS;
	}else
	{
		#if nrfCEport == 1
			P1DIR |= nrfCEpin;
		#elif nrfCEport == 2
			P2DIR |= nrfCEpin;
		#elif nrfCEport == 3
			P3DIR |= nrfCEpin;
		#elif nrfCEport == J
			PJDIR |= nrfCEpin;
		#endif
		CE_DIS;
	}

//	uint8_t pin;
//	PORT_t * p = GPIO_getPort(port,&pin);
//	if (DDR==0)
//	{
//		p->DIRCLR=pin;
//	}else if (DDR==1)
//	{
//		p->DIRSET = pin;
//	}
}
////
////void GPIO::close(int port)
////{
////	// Nothing to do with close;
////}
////
////int read(int port)
////{
////	uint8_t pin;
////	PORT_t * p = GPIO_getPort(port,&pin);
////	return p->IN;
////}
////
//
void GPIO::write(int pin, int value)
{
	if(pin == nrfCEpin)
	{
		if (value==OUTPUT_LOW)
			nrfCEportout &= ~pin;
		else
			nrfCEportout |= pin;
	}

	if(pin == nrfCSNpin)
	{
		if (value==OUTPUT_LOW)
			nrfCSNportout &= ~pin;
		else
			nrfCSNportout |= pin;
	}
}
