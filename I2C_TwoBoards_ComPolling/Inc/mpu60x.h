#ifndef __MPU60x_H__
#define __MPU60x_H__

#include "stm32f4xx_hal.h"

#define MPU60x_I2C_ADDRESS        0x68

void mpu60x_set_i2c(I2C_HandleTypeDef *i2c);

uint8_t mpu60x_read_register(uint8_t register_to_read);
void mpu60x_write_register(uint8_t register_to_write, uint8_t *value_to_write);


#endif
