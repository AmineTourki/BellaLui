/* telemetry_handling.h
 *
 *  Created on: 10 Jun 2019
 *      Author: Alexandre Devienne
 */

#ifndef TELEMETRY_HANDLING_H_
#define TELEMETRY_HANDLING_H_

#include <stdbool.h>

#include "../../../HostBoard/Inc/misc/datastructs.h"

#ifdef __cplusplus
extern "C" {
#endif

bool telemetrySendGPS(uint32_t timestamp, GPS_data data);
bool telemetrySendIMU(uint32_t timestamp, IMU_data data);
bool telemetrySendBaro(uint32_t timestamp, BARO_data data);
bool telemetrySendState(uint32_t timestamp, bool id, float value, uint8_t av_state);
bool telemetrySendMotorPressure(uint32_t timestamp, uint32_t pressure);
bool telemetrySendAirbrakesAngle(uint32_t timestamp, int32_t angle);
bool telemetrySendPropulsionData(uint32_t timestamp, PropulsionData* payload);

bool telemetryReceivePropulsionCommand(uint32_t timestamp, uint8_t* payload);

#ifdef __cplusplus
}
#endif


#endif /* TELEMETRY_HANDLING_H_ */
