/*
 	Copyright [2016] [Mauro Riva -lemariva@gmail.com- (http://lemariva.com)]

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

#include "compatibility.h"

volatile uint32_t _millis;

/**********************************************************************/
/**
 * This function is added in order to simulate arduino delay() function
 * @param milisec
 */
void __msleep(int milisec)
{
	int useconds = milisec * 1000;
	__usleep(useconds);
}

void __usleep(int usec)
{
	// aprox DELAY_CYCLES_15US  ->  __delay_cycles(240)

	int i;
	for (i=usec*16; i>0; i--)
		__delay_cycles(1);
}

/**
 * This function is added in order to simulate arduino millis() function
 */
void __start_timer()
{
	// Data sending nRF24
	TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
	TA0CCR0 = 8000;
	TA0CTL = TASSEL_2 + MC_1 + TACLR;            // SMCLK, upmode

	_millis = 0;
}

long __millis()
{
	return _millis;
}


// Timer1 A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer0_A0 (void) {
	   _millis++;
	   TA0CCTL0 &= ~CCIFG;
}

