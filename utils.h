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

#ifndef __UTILS_H
#define __UTILS_H

#include <inttypes.h>
#include "payload_def.h"
//#include "errorHandler.h"
/* CPU clock cycles for the specified amounts of time--accurate minimum delays
 * required for reliable operation of the nRF24L01+'s state machine.
 */
/* Settings for 1MHz MCLK.
#define DELAY_CYCLES_5MS       5000
#define DELAY_CYCLES_130US     130
#define DELAY_CYCLES_15US      15
 */

/* Settings for 8MHz MCLK.
#define DELAY_CYCLES_5MS       40000
#define DELAY_CYCLES_130US     1040
#define DELAY_CYCLES_15US      120
 */

/* Settings for 16MHz MCLK */
#define DELAY_CYCLES_5MS       80000
#define DELAY_CYCLES_130US     2080
#define DELAY_CYCLES_15US      240
#define DELAY_CYCLES_30US      480
#define DELAY_CYCLES_20MS	   320000


/* Settings for 24MHz MCLK.
#define DELAY_CYCLES_5MS       120000
#define DELAY_CYCLES_130US     3120
#define DELAY_CYCLES_15US      360
 */

//// ASCII values for the commands
//#define		HELP			0x68
//#define		VERBOSE			0x76
//#define		NAME			0x6e
//#define		STATUS			0x73
//
//void wait(void);
//
//extern char 				_deviceName[3];
//extern bool					_verbose;
//
//extern payload_sensordata_t payload_sensor;
//
////void error_checking(uint8_t ui_states);

#endif

/* vim: set sw=4 et: */
