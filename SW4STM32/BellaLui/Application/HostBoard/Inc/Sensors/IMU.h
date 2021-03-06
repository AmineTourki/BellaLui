/*
 * IMU.h
 *
 *  Created on: 6 Dec 2020
 *      Author: Arion
 */

#ifndef APPLICATION_HOSTBOARD_INC_SENSORS_IMU_H_
#define APPLICATION_HOSTBOARD_INC_SENSORS_IMU_H_


#include <Sensors/BNO055/bno055.h>
#include <Sensors/I2CDriver.h>
#include <Sensors/Sensor.h>


struct Vector {
	float x;
	float y;
	float z;
};

struct IMUData {
	Vector accel;
	Vector gyro;
};

class IMU : public Sensor<IMUData> {
public:
	IMU(const char* identifier, I2CDriver* driver, uint8_t address);

	bool load();
	bool reset();
	bool fetch(IMUData* data);

private:
	I2CDriver* driver;
	bno055_t dev;
};

#endif /* APPLICATION_HOSTBOARD_INC_SENSORS_IMU_H_ */
