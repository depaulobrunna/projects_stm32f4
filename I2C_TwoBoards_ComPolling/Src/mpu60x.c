#include "mpu60x.h"
#include "main.h"
#include "mpu60x_registers.h"

const char* const mpu_available_table[] = {"Not available", "available"};

static I2C_HandleTypeDef *mpu60x_i2c;

static void mpu60x_get_register(uint8_t register_to_get, uint8_t *register_get, uint8_t size);
static void mpu60x_set_register(uint8_t register_to_set, uint8_t *value_to_set);
static void mpu60x_set_sample_rate_div(uint8_t sample_rate_div);
static void mpu60x_set_dlpf(uint8_t dlpf);
static void mpu60x_get_gyro_axis(MPU60x_Axis axis, uint8_t *gyroscope);
static void mpu60x_get_accel_axis(MPU60x_Axis axis, uint8_t *accelerometer);
static void mpu60x_get_temperature(uint8_t *temperature);

static void mpu60x_get_register(uint8_t register_to_get, uint8_t *register_get, uint8_t size)
{
	HAL_I2C_Mem_Read(mpu60x_i2c,(uint16_t)MPU60x_I2C_DEVICE_ADDRESS << 1,
		register_to_get, I2C_MEMADD_SIZE_8BIT, register_get, size, 1000);
	return;
}

static void mpu60x_set_register(uint8_t register_to_set, uint8_t *value_to_set)
{
	HAL_I2C_Mem_Write(mpu60x_i2c,(uint16_t)MPU60x_I2C_DEVICE_ADDRESS << 1,
		register_to_set, I2C_MEMADD_SIZE_8BIT, value_to_set, 1, 100);
	
	return; 
}

static void mpu60x_set_sample_rate_div(uint8_t sample_rate_div)
{
	uint8_t temp = sample_rate_div;
	mpu60x_write_register(MPU60x_SMPLRT_DIV_ADDR, &temp);
	return;
}
static void mpu60x_set_dlpf(uint8_t dlpf)
{
	uint8_t temp;
	mpu60x_get_register(MPU60x_CONFIG_ADDR, &temp, 1);
	temp = (temp & ~DLPF_CFG_MASK) | dlpf;
	mpu60x_write_register(MPU60x_CONFIG_ADDR, &temp);
	return;
}

static void mpu60x_get_gyro_axis(MPU60x_Axis axis, uint8_t *gyroscope)
{
	uint8_t temp[2];
	
	switch (axis)
	{
		case (MPU60x_X_AXIS):
		{
			mpu60x_get_register(MPU60x_GYRO_XOUT_H_ADDR, &temp[0], 2);
			gyroscope[0] = temp[1];
			gyroscope[1] = temp[0];
			break;
		}
		case (MPU60x_Y_AXIS):
		{
			mpu60x_get_register(MPU60x_GYRO_YOUT_H_ADDR, &temp[0], 2);
			gyroscope[0] = temp[1];
			gyroscope[1] = temp[0];
			break;
		}
		case(MPU60x_Z_AXIS):
		{
			mpu60x_get_register(MPU60x_GYRO_ZOUT_H_ADDR, &temp[0], 2);
			gyroscope[0] = temp[1];
			gyroscope[1] = temp[0];
			break;
		}
		case(MPU60x_NO_AXIS):
		{
			break;
		}
	}
	return;
}

static void mpu60x_get_accel_axis(MPU60x_Axis axis, uint8_t *accelerometer)
{
	uint8_t temp[2];
	
	switch (axis)
	{
		case (MPU60x_X_AXIS):
		{
			mpu60x_get_register(MPU60x_ACCEL_XOUT_H_ADDR, &temp[0], 2);
			accelerometer[0] = temp[1];
			accelerometer[1] = temp[0];
			break;
		}
		case (MPU60x_Y_AXIS):
		{
			mpu60x_get_register(MPU60x_ACCEL_YOUT_H_ADDR, &temp[0], 2);
			accelerometer[0] = temp[1];
			accelerometer[1] = temp[0];
			break;
		}
		case(MPU60x_Z_AXIS):
		{
			mpu60x_get_register(MPU60x_ACCEL_ZOUT_H_ADDR, &temp[0], 2);
			accelerometer[0] = temp[1];
			accelerometer[1] = temp[0];
			break;
		}
		case(MPU60x_NO_AXIS):
		{
			break;
		}
	}
	return;
}

static void mpu60x_get_temperature(uint8_t *temperature)
{
	uint8_t temp[2];
	
	mpu60x_get_register(MPU60x_TEMP_OUT_H_ADDR, &temp[0], 2);
	temperature[0] = temp[1];
	temperature[1] = temp[0];
	return;
}

//------------------------------------------------------------------------------------//
void mpu60x_set_i2c(I2C_HandleTypeDef *i2c)
{
	mpu60x_i2c = i2c;
	return;
}

void mpu60x_read_register(uint8_t register_to_read, uint8_t *register_get, uint8_t size)
{
	mpu60x_get_register(register_to_read, register_get, size);
	return;
}

void mpu60x_write_register(uint8_t register_to_write, uint8_t *value_to_write)
{
	mpu60x_set_register(register_to_write, value_to_write);
	return;
}


MPU60x_States mpu60x_get_state(void)
{
	uint8_t temp;
	mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR, &temp, 1);
	return (MPU60x_States)((temp & 0xC0) >> SLEEP_POS);
}

void mpu60x_wake(void)
{
	uint8_t temp;
	mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR, &temp, 1);
	temp = (temp & ~(SLEEP_MASK|CYCLE_MASK))|(SLEEP_DISABLE|CYCLE_DISABLE);
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	temp = (temp & ~CLK_SEL_MASK)|(0x00 << CLK_SEL_POS);
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	
	return;
}

MPU60x_Available mpu60x_available(void)
{
	MPU60x_Available status;
	
	if (HAL_I2C_IsDeviceReady(mpu60x_i2c, (uint16_t)MPU60x_I2C_DEVICE_ADDRESS << 1, 1, 10) != HAL_OK)
	{
		status = MPU60x_NOT_AVAILABLE;
	}
	else
	{
		status = MPU60x_AVAILABLE;
	}
	return status;
}

void mpu60x_set_gyro_cfg(MPU60x_Gyroscope_Range range)
{ 
	mpu60x_set_register(MPU60x_GYRO_CONFIG_ADDR, (uint8_t *)&range);
	return;
}

void mpu60x_set_accel_cfg(MPU60x_Accelerometer_Range range)
{
	mpu60x_set_register(MPU60x_ACCEL_CONFIG_ADDR, (uint8_t *)&range);
	return;
}

void mpu60x_set_sample_rate(uint8_t sample_rate_div, uint8_t dlpf_cfg)
{
	mpu60x_set_dlpf(dlpf_cfg);
	mpu60x_set_sample_rate_div(sample_rate_div);
	return;
}

void mpu60x_temperature_sensor_enable(void)
{
	uint8_t temp;
	mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR, &temp, 1);
	temp = (temp & ~TEMP_DIS_MASK) | TEMP_ENABLE;
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	return;
}

void mpu60x_temperature_sensor_disable(void)
{
	uint8_t temp; 
	mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR, &temp, 1);
	temp = (temp & ~TEMP_DIS_MASK) | TEMP_DISABLE;
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	return;
}

uint16_t mpu60x_get_sensor(MPU60x_Sensor_Type sensor, MPU60x_Axis axis)
{
	uint8_t data[2];
	switch(sensor)
	{
		case(MPU60x_GYROSCOPE):
		{
			mpu60x_get_gyro_axis(axis, &data[0]);
			break;
		}
		case(MPU60x_ACCELEROMETER):
		{
			mpu60x_get_accel_axis(axis, &data[0]);
			break;
		}
		case(MPU60x_TEMPERATURE_SENSOR):
		{
			mpu60x_get_temperature(&data[0]);
			break;
		}
	}
	return ((data[1] << 8)|data[0]);
}
