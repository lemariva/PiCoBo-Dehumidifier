/* 
 * File:   compatiblity.h
 * Author: lemariva
 *
*/

 /**
 * @file compatibility.h
 */

 /**
 * class declaration for timing functions
 *
 * @defgroup Porting_Timing Porting: Timing
 * 
 * @{
 */
 
#ifndef COMPATIBLITY_H
#define	COMPATIBLITY_H

#include <msp430.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

void __msleep(int milisec);
void __usleep(int milisec);
void __start_timer();
long __millis();

#ifdef	__cplusplus
}
#endif

#endif	/* COMPATIBLITY_H */

/*@}*/	
