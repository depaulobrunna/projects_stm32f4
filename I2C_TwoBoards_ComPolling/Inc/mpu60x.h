#ifndef __MPU60x_H__
#define __MPU60x_H__

#include "stm32f4xx_hal.h"

typedef enum mpu60x_states_t
{
	MPU60x_WAKE, 				// CYCLE == 0, SLEEP == 0
	MPU60x_WAKE_CYCLE, 	//  CYCLE == 1, SLEEP == 0
	MPU60x_SLEEP 				// CYCLE == 0, SLEEP == 1;
} MPU60x_States;

typedef enum mpu60x_available
{
	MPU60x_NOT_AVAILABLE,
	MPU60x_AVAILABLE,
	
} MPU60x_Available;

void mpu60x_set_i2c(I2C_HandleTypeDef *i2c);

uint8_t mpu60x_read_register(uint8_t register_to_read);
void mpu60x_write_register(uint8_t register_to_write, uint8_t *value_to_write);
MPU60x_States mpu60x_get_state(void);
MPU60x_Available mpu60x_available(void);
void mpu60x_set_sample_rate(uint8_t sample_rate_div, uint8_t dlpf_cfg);
void mpu60x_wake(void);
void mpu60x_temperature_sensor_disable(void);
void mpu60x_temperature_sensor_enable(void);
float mpu60x_get_temperature(void);
void mpu60x_set_gyro_cfg(void);
uint16_t mpu60x_get_gyro_z_data(void);
#endif
