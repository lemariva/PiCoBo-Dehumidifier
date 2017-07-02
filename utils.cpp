#include <msp430.h>
#include "stdint.h"

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "utility/TI_Launchpads/MSP430G2/tprintf.h"
#include "utility/TI_Launchpads/MSP430G2/uart.h"
#include "utils.h"

bool changingName = false;

void wait(void)
{
    __delay_cycles(80000);

}

void Receive()
{

	if (changingName)
	{
//		changingName = false;
//		std::strcpy(_deviceName, RXBuff);
//		tprintf("\n\r------------------\n\r");
//		tprintf("sensor name changed: %s\n\r", _deviceName);
//		tprintf("\r------------------\n\r");
	}
	switch(RXBuff[0])					// Switch depending on command value received
	{
//		case VERBOSE:
//			if(_verbose)
//				_verbose = false;
//			else
//				_verbose = true;
//			tprintf("\n\r------------------\n\r");
//			tprintf("verbose status changed: %i\n\r", _verbose);
//			tprintf("\r------------------\n\r");
//			break;
//		case NAME:
//			changingName = true;
//			tprintf("\n\r------------------\n\r");
//			tprintf("Please type a 3 char size sensor name,\n\r");
//			tprintf("and press enter to confirm.\n\r");
//			tprintf("\r------------------\n\r");
//			break;
//		case STATUS:
//			tprintf("\n\r------------------\n\r");
//			tprintf("Payload status:\n\r");
//			tprintf("nodeId: %l\n\r", payload_sensor.nodeId);
//			tprintf("cStatus: %c\n\r", payload_sensor.cStatus);
//			tprintf("HardwareID: %s\n\r", payload_sensor.HardwareID);
//			tprintf("temperature: %x\n\r", payload_sensor.temperature);
//			tprintf("power: %i\n\r", payload_sensor.power);
//			tprintf("power: %i\n\r", payload_sensor.humidity);
//			tprintf("airQuality: %i\n\r", payload_sensor.airQuality);
//			tprintf("lux: %i\n\r", payload_sensor.lux);
//			tprintf("info: %s\n\r", payload_sensor.info);
//			tprintf("\r------------------\n\r");
//			//tprintf("Actual errors: %i\n\r", _errorCheck.errorNowGet());
//			///tprintf("Total errors: %l\n\r", _errorCheck.errorAcumGet());
//			tprintf("Channel: %i\n\r", _channel);
//			tprintf("Key: %x\n\r", _channel);
//			tprintf("\r------------------\n\r");
//			break;
//		case HELP:
//			tprintf("\n\r------------------\n\r");
//			tprintf("Options:\n\r");
//			tprintf("\r\r\r\r * type v to activate the verbose function.\n\r");
//			tprintf("\r\r\r\r * type n to change the sensor name.\n\r");
//			tprintf("\r\r\r\r * type s to plot the sensor status.\n\r");
//			tprintf("\r------------------\n\r");
//			break;
	}
}


/* vim: set sw=4 et: */
