/*
*/

#include <msp430.h>
#include "DHT11_LIB.h"
#include "../utils.h"
#include "../utility/TI_Launchpads/MSP430G2/tprintf.h"

DHT11::DHT11(int PINSEL)
{
	// DHT11 Sensor
	TA1CCR0 	= 0xFFFF;							// Initialize the timer to count at 30Hz
	TA1CCTL0 	= CCIE;								// Enable interrupt
	TA1CTL 		= TASSEL_2 +  MC_1 + ID_3 + TACLR;			// SMCLK, div 8, up mode => 2MHz

	DPIN = PINSEL;
}

bool DHT11::read_sensorData()
{
	TA0CCTL0 &= ~CCIE;       // CCR0 interrupt disabled Timer A0

	read_Packet(Packet);

	TA0CCTL0 = CCIE;		// CCR0 interrupt enabled Timer A0

	if (check_Checksum(Packet))
	{
		TEMP_DHT11 =  (Packet[2]) + (Packet[3]);
		RH_DHT11   = (char)(Packet[0]);// + Packet[1] >> 8);
		return 1;
	}else
		return 0;
}

unsigned int DHT11::get_Temperature()
{
	return TEMP_DHT11;
}

char DHT11::get_Humidity()
{
	return RH_DHT11;
}

unsigned char DHT11::read_Byte(){
	TOUT = 0;
	unsigned char num = 0;
	unsigned char i;
	TA1CCTL0 &= ~CCIE;			  //Disable interruption

	for (i=8; i>0; i--){
		while(!(TST(P2IN,DPIN))); //Wait for signal to go high

		SET(TA1CTL,TACLR);		  //Reset timer
		SET(TA1CTL,0x10); 	  	  //Reenable timer
		SET(TA1CCTL0,CCIE); 	  //Enable timer interrupt

		while(TST(P2IN,DPIN)); 	  //Wait for signal to go low

		CLR(TA1CTL,0x30); 		  //Halt Timer

		if (TA1R > DHT11_40us)
		{
			num |= 1 << (i-1);
		}
	}
	return num;
}

unsigned char DHT11::read_Packet(unsigned char * data){
	start_Signal();
	if (check_Response()){
		//if(debug_dht11) tprintf("Reading \n\r");
		//Cannot be done with a for loop!
		data[0] = read_Byte();
		data[1] = read_Byte();
		data[2] = read_Byte();
		data[3] = read_Byte();
		data[4] = read_Byte();
		return 1;
	}
	else return 0;
}

unsigned char DHT11::check_Response(){
	TOUT=0;
	SET(TA1CTL,TACLR);			//Reset timer to 0;
	TA1CCR0 = DHT11_100us;		//Set timer to overflow in 100uS
	SET(TA1CCTL0,CCIE); 		//And enable timer interrupt
	while(!(TST(P2IN,DPIN)) && !TOUT);
	if (TOUT)
	{
		if(debug_dht11) tprintf("Time out \n\r");
		return 0;
	}
	else {
		SET(TA1CTL,TACLR);		//Reset timer to 0
		SET(TA1CCTL0,CCIE); 	//And enable timer interrupt
		while((TST(P2IN,DPIN)) && !TOUT);
		if(TOUT)
			return 0;
		else
		{
			TA1CCTL0 &= ~(CCIE);		// Disable timer interrupt
			return 1;
		}
	}
}

void DHT11::start_Signal(){
	SET(P2DIR, DPIN);					// Set Data pin to output direction
	CLR(P2OUT,DPIN); 					// Set output to low
	__delay_cycles(DELAY_CYCLES_20MS); 	// Low for at least 18ms
	SET(P2OUT,DPIN);
	__delay_cycles(DELAY_CYCLES_30US);	// High for at 20us-40us
	CLR(P2DIR,DPIN);					// Set data pin to input direction
}

//returns true if checksum is correct
unsigned char DHT11::check_Checksum(unsigned char *data){
	if (data[4] != (data[0] + data[1] + data[2] + data[3])){
		return 0;
	}
	else
	{
		return 1;
	}
}
