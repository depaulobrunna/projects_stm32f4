#include "mpu60x.h"
#include "main.h"

I2C_HandleTypeDef *mpu60x_i2c;

static uint8_t mpu_get_register(uint8_t register_to_get);
static void mpu_set_register(uint8_t register_to_set, uint8_t *value_to_set);

static uint8_t mpu_get_register(uint8_t register_to_get)
{
	uint8_t register_get;
	HAL_I2C_Mem_Read(mpu60x_i2c,(uint16_t)MPU60x_I2C_ADDRESS << 1, register_to_get, I2C_MEMADD_SIZE_8BIT, &register_get, 1, 100);
	
	return register_get; 
}

static void mpu_set_register(uint8_t register_to_set, uint8_t *value_to_set)
{
	HAL_I2C_Mem_Write(mpu60x_i2c,(uint16_t)MPU60x_I2C_ADDRESS << 1, register_to_set, I2C_MEMADD_SIZE_8BIT, value_to_set, 1, 100);
	
	return; 
}

void mpu60x_set_i2c(I2C_HandleTypeDef *i2c)
{
	mpu60x_i2c = i2c;
	return;
}

uint8_t mpu60x_read_register(uint8_t register_to_read)
{
	return mpu_get_register(register_to_read);
}

void mpu60x_write_register(uint8_t register_to_write, uint8_t *value_to_write)
{
	mpu_set_register(register_to_write, value_to_write);
	return;
}
