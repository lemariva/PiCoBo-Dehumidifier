/**
 * Copyright [2017] [Mauro Riva <lemariva@mail.com> <lemariva.com>]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *
 */

#include <msp430.h>
#include "stdint.h"

//#include <stdlib.h>
#include <stdio.h>

//#include <string.h>

#include "utility/TI_Launchpads/MSP430G2/tprintf.h"
#include "utility/TI_Launchpads/MSP430G2/uart.h"

#include "payload_def.h"

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

#include "config.h"

#include "utils.h"

#define _DEF_HARDWAREID	"0A0"
#define nodeID			03
// nrf24 nodes
unsigned char 				_node_status;
char 						_deviceName[3];

#if defined(mDHT11)
	#include "dht11_lib/DHT11_LIB.h"
#endif

#if defined(mADC)
	#include "adc_lib/adc.h"
#endif

#if defined(mDHT11) // DHT11
	DHT11 sensorDHT11(BIT4);
	unsigned char TOUT;			//REQUIRED for library
#endif

#if defined(mADC) // ADC
	adc sensorVoltage(BIT4);
	uint16_t  ADCValue_volts;
#endif

bool waterTankReady;
bool waterTankFull;
bool processStart;
int humidityLimit;

payload_commands_t 		commands_input;
payload_sensordata_t 	payload_sensor;

// Hardware layer
RF24 radio(nrfCEpin, nrfCSNpin);
// Network layer
RF24Network network(radio);
// Mesh layer
RF24Mesh mesh(radio,network);

RF24NetworkHeader header_receive;
RF24NetworkHeader header_send;


#if defined(mDHT11) // DHT11
	void read_dht()
	{
		// read temperatur and humidity
		sensorDHT11.read_sensorData();

		// Setting timer to initial counting!
		SET (TA1CTL, TACLR);
		SET (TA1CTL, 0x10);
		TA1CCR0 = 0xFFFF;		//Initialize the timer to count at 30Hz
	}
#endif

void fillingData()
{
	payload_sensor.nodeId  = mesh.getNodeID();
	payload_sensor.cStatus = _node_status;
	payload_sensor.ambientHumidity = sensorDHT11.get_Humidity();
	payload_sensor.ambientTemp = sensorDHT11.get_Temperature();
	payload_sensor.nodePower   = ADCValue_volts;
	payload_sensor.nodeInfo[0] = processStart;
	payload_sensor.nodeInfo[1] = waterTankReady;
	payload_sensor.nodeInfo[2] = waterTankFull;
}

void main()
	{
	// address initialization and status
	_node_status = 0x53; // => S

    WDTCTL = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;

	BCSCTL2 = DIVS_1;			// SPI (USCI) uses SMCLK, prefer SMCLK < 10MHz (SPI speed limit for nRF24 = 10MHz)

	// Led
	P3DIR |= BIT1; P3OUT |= BIT1;

	// Water Tank
	P2DIR &= ~BIT3;
	P2REN &= ~BIT3;
	P2OUT &= ~BIT3;
	// Water Tank Status
	P3DIR &= ~BIT4;
	P3REN &= ~BIT4;
	P3OUT &= ~BIT4;
	// Start
	P1DIR &= ~BIT3;
	P1REN &= ~BIT3;
	P1OUT &= ~BIT3;

	waterTankReady = P2IN&BIT3;
	waterTankFull  = P3IN&BIT4;
	processStart   = P1IN&BIT3;

	// Mosfets
	P3DIR |= BIT0; P3OUT &= ~BIT0;
	P3DIR |= BIT2; P3OUT &= ~BIT2;
	P3DIR |= BIT3; P3OUT &= ~BIT3;


	tprintf("\n\r- Sensor init -\n\r");

	// UART initialization
	// Enable interruptions for uart!
	uart_init();

	//Defining HardwareID
	std::strcpy(_deviceName, _DEF_HARDWAREID);

	// Communication timers
	__start_timer();

	tprintf("Application starting...\n\r");

	// interruptions enabled
	_BIS_SR(GIE);
	tprintf("done.\n\r");

	/********************************************************************************/

	uint32_t sendTimer=0;

	// Set the nodeID
	mesh.setNodeID(nodeID);

	// Connect to the node mesh
	tprintf("Starting nodeID: %u\n", mesh.getNodeID());

	mesh.begin();

	// Setting humidity limit
	humidityLimit = 30;

	while(1)
	{
		// Call mesh.update to keep the network updated
		mesh.update();

		// update status
		_node_status = 0x53; // => S

		// Send the current millis() to the master node every second
		if(millis() - sendTimer >= 5000){
			fillingData();
			sendTimer = millis();

			// reading temperature & humidity
			read_dht();
			// reading node voltage
			sensorVoltage.initReadValue();

			// reporting status over UART
			tprintf("Temperature:  %i \r\n", sensorDHT11.get_Temperature());
			tprintf("Humidity:  %u \r\n", sensorDHT11.get_Humidity());
			tprintf("Ready:  %u \r\n", waterTankReady);
			tprintf("Water tank full:  %u \r\n", waterTankFull);
			tprintf("Start process:  %u \r\n", processStart);

			if(!mesh.write(&payload_sensor,'G',sizeof(payload_sensor))){

			  // If a write fails, check connectivity to the mesh network
			  if( ! mesh.checkConnection() ){
				// The address could be refreshed per a specified timeframe or only when sequential writes fail, etc.
				tprintf("Renewing Address\n");
				mesh.renewAddress();
			  }else{
				  tprintf("Send fail, Test OK\n");
			  }
			}else{
				tprintf("Send OK: %u\n",sendTimer);
			}


			// Status Led
			P3OUT ^= BIT1;
		}

		// reading humidifier status
	    waterTankReady = P2IN&BIT3;
		waterTankFull  = P3IN&BIT4;
		processStart   = P1IN&BIT3;

		if(sensorDHT11.get_Humidity() > humidityLimit && waterTankReady && !waterTankFull & processStart)
		{
			P3OUT |= BIT0 + BIT2 + BIT3;
		}
		else
		{
			P3OUT &= ~(BIT0 + BIT2 + BIT3);
		}

		delay(1000);
	}
}


/*      -       -       Interrupt vectors       -       -       */
#if defined(mDHT11)// DHT11
	// Timer1 A0 for DHT11
	#pragma vector = TIMER1_A0_VECTOR
	__interrupt void Timer1_A0_ISR(void){
		TOUT=1;
		CLR (TA1CCTL0, CCIFG);
	}
#endif

#if defined(mADC)
	// ADC interrupt routine. Pulls CPU out of sleep mode for the main loop.
	#pragma vector=ADC10_VECTOR
	__interrupt void ADC10_ISR (void)
	{
		ADCValue_volts = sensorVoltage.getValue();
	}
#endif

