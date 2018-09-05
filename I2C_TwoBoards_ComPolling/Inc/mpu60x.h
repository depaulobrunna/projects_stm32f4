#ifndef __MPU60x_H__
#define __MPU60x_H__

#include "stm32f4xx_hal.h"

typedef enum mpu60x_states_t
{
	MPU60x_WAKE, 				// CYCLE == 0, SLEEP == 0
	MPU60x_WAKE_CYCLE, 	//  CYCLE == 1, SLEEP == 0
	MPU60x_SLEEP 				// CYCLE == 0, SLEEP == 1;
} MPU60x_States;

typedef enum mpu60x_available_t
{
	MPU60x_NOT_AVAILABLE,
	MPU60x_AVAILABLE,
} MPU60x_Available;

typedef enum mpu60x_axis_t
{
	MPU60x_X_AXIS,
	MPU60x_Y_AXIS,
	MPU60x_Z_AXIS,
	MPU60x_NO_AXIS
} MPU60x_Axis;

typedef enum mpu60x_sensor_type_t
{
	MPU60x_GYROSCOPE,
	MPU60x_ACCELEROMETER,
	MPU60x_TEMPERATURE_SENSOR
} MPU60x_Sensor_Type;

void mpu60x_set_i2c(I2C_HandleTypeDef *i2c);

uint8_t mpu60x_read_register(uint8_t register_to_read);
void mpu60x_write_register(uint8_t register_to_write, uint8_t *value_to_write);
MPU60x_States mpu60x_get_state(void);
void mpu60x_wake(void);
MPU60x_Available mpu60x_available(void);
uint16_t mpu60x_get_sensor(MPU60x_Sensor_Type sensor, MPU60x_Axis axis);
#endif
