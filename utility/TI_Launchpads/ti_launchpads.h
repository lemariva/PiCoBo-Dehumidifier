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

#ifndef __RF24_TI_LAUNCHPADS_H__
#define __RF24_TI_LAUNCHPADS_H__

/*** USER DEFINES:  ***/
#define MSP430G2553
//#define MSP430F5529
//#define TM4C1294XL  // -> needs TivaWare_C_Series
/**********************/

#if defined(MSP430G2553)
	#include "MSP430G2/includes.h"
#elif defined(MSP430F5529)
	#include "MSP430F5529/includes.h"
#elif defined(TM4C1294XL)
	#include "TM4C1294xl/includes.h"   // needs TivaWare_C_Series
#endif

#endif  // __RF24_TI_LAUNCHPADS_H__
