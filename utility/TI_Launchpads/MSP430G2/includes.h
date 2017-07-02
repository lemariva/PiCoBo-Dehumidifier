/*
 * 	MODIFIED by lemariva
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

/**
* @file includes.h
* Configuration defines for RF24/MSP430F5529
*/

/**
* includes.h for RF24 MSP430F5529 portability
*
* @defgroup Porting_Includes Porting: Includes
*
* @{
*/
  
#ifndef __RF24_INCLUDES_H__
#define __RF24_INCLUDES_H__


	// Saves memory --heap-size: 150  --stack-size: 150
	#define DISABLE_FRAGMENTATION
	#define MINIMAL

	/**
	* Load the correct configuration for this platform
	*/
	#include "RF24_arch_config.h"
  
#endif

/*@}*/	

