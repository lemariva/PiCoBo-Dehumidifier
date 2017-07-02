
/*
* @file RF24_arch_config.h
*/

/**
* RF24_arch_config.h: RF24 portability on launchpad msp430g2
*
* @defgroup Porting_General Porting: General
*
*
* @{
*/
 
 
#ifndef __TEXAS_MSP430G2_H__
#define __TEXAS_MSP430G2_H__

#include <stdint.h>

#include <string.h>

#include "compatibility.h"
#include "gpio.h"
#include "spi.h"
#include "uart.h"
#include "tprintf.h"


#define _BV(x) (1<<(x))
#define _SPI spi

#undef SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#define IF_SERIAL_DEBUG(x) ({x;})
#else
#define IF_SERIAL_DEBUG(x)
#endif


typedef uint16_t prog_uint16_t;
#define PSTR(x) (x)
#define printf_P tprintf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(p)) 
#define PRIPSTR "%s"
#define pgm_read_byte(p) (*(p))


// Function, constant map as a result of migrating from Arduino
#define LOW GPIO::OUTPUT_LOW
#define HIGH GPIO::OUTPUT_HIGH
#define INPUT GPIO::DIRECTION_IN
#define OUTPUT GPIO::DIRECTION_OUT

#define digitalWrite(pin, value) GPIO::write(pin, value)
#define pinMode(pin, direction) GPIO::open(pin, direction)

#define delay(milisec) __msleep(milisec)

#define delayMicroseconds(usec) __usleep(usec)

#define millis() __millis()


#endif // __TEXAS_MSP430G2_H__


/*@}*/	
