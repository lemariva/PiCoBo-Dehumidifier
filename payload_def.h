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

#ifndef PAYLOAD_DEF_H_
#define PAYLOAD_DEF_H_

// Network packaging

struct payload_commands_t
{
	unsigned long  nodeId;
	char command[10];
	char value[5];
};

struct payload_sensordata_t
{
	unsigned long 	nodeId;
	char			cStatus;		/**< Status configured or not */
	char			HardwareID[3];	/**< Hardware unique ID */
	unsigned int	ambientTemp;
	unsigned int 	nodePower;
	char   			ambientHumidity;
	char	 		airQuality;
	char	 		ambientlux;
	unsigned char	errorCount;
	char			nodeInfo[3];
};



#endif /* PAYLOAD_DEF_H_ */
