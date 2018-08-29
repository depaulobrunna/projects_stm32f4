#include "mpu60x.h"
#include "main.h"
#include "mpu60x_registers.h"

//#define MPU_DEBUG
#ifdef MPU_DEBUG
#define DEBUG_MPU(...) PRINTS(__VA_ARGS__)
#else
#define DEBUG_MPU(...)
#endif
#define CONST_TEMP 125.0f/65535.0f

const char* const mpu_available_table[] = {"Not available", "available"};

static I2C_HandleTypeDef *mpu60x_i2c;

static uint8_t mpu60x_get_register(uint8_t register_to_get);
static void mpu60x_set_register(uint8_t register_to_set, uint8_t *value_to_set);



static uint8_t mpu60x_get_register(uint8_t register_to_get)
{
	uint8_t register_get;
	HAL_StatusTypeDef status;
		
	status = HAL_I2C_Mem_Read(mpu60x_i2c,(uint16_t)MPU60x_I2C_DEVICE_ADDRESS << 1,
		register_to_get, I2C_MEMADD_SIZE_8BIT, &register_get, 1, 1000);
	
	DEBUG_MPU("HAL status: %s, in file %s at function %s() in line %i - ",
			hal_status_table[status], __FILE__, __FUNCTION__, __LINE__);
	DEBUG_MPU("HAL I2C error code: 0x%02X.\n",(uint8_t)mpu60x_i2c->ErrorCode);
	
	return register_get; 
}

static void mpu60x_set_register(uint8_t register_to_set, uint8_t *value_to_set)
{
	HAL_StatusTypeDef status;
	
	status = HAL_I2C_Mem_Write(mpu60x_i2c,(uint16_t)MPU60x_I2C_DEVICE_ADDRESS << 1,
		register_to_set, I2C_MEMADD_SIZE_8BIT, value_to_set, 1, 100);
	
	DEBUG_MPU("HAL status: %s, in file %s at function %s() in line %i - ",
			hal_status_table[status], __FILE__, __FUNCTION__, __LINE__);
	DEBUG_MPU("HAL I2C error code: 0x%02X.\n",(uint8_t)mpu60x_i2c->ErrorCode);

	return; 
}

static void mpu60x_set_sample_rate_div(uint8_t sample_rate_div)
{
	uint8_t temp = sample_rate_div;
	mpu60x_write_register(MPU60x_SMPLRT_DIV_ADDR, &temp);

}
static void mpu60x_set_dlpf(uint8_t dlpf)
{
	uint8_t temp = mpu60x_get_register(MPU60x_CONFIG_ADDR);
	temp = (temp & ~DLPF_CFG_MASK) | dlpf;
	mpu60x_write_register(MPU60x_CONFIG_ADDR, &temp);
}

void mpu60x_set_i2c(I2C_HandleTypeDef *i2c)
{
	mpu60x_i2c = i2c;
	return;
}

uint8_t mpu60x_read_register(uint8_t register_to_read)
{
	return mpu60x_get_register(register_to_read);
}

void mpu60x_write_register(uint8_t register_to_write, uint8_t *value_to_write)
{
	mpu60x_set_register(register_to_write, value_to_write);
	return;
}


MPU60x_States mpu60x_get_state(void)
{
	return (MPU60x_States)((mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR) & 0xC0) >> SLEEP_POS);
}

void mpu60x_set_sample_rate(uint8_t sample_rate_div, uint8_t dlpf_cfg)
{
	mpu60x_set_dlpf(dlpf_cfg);
	mpu60x_set_sample_rate_div(sample_rate_div);
	
	return;
}

void mpu60x_wake(void)
{
	uint8_t temp = mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR);
	temp = (temp & ~(SLEEP_MASK|CYCLE_MASK))|(SLEEP_DISABLE|CYCLE_DISABLE);
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	temp = (temp & ~CLK_SEL_MASK)|(0x00 << CLK_SEL_POS);
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	
	return;
}

void mpu60x_temperature_sensor_enable(void)
{
	uint8_t temp = mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR);
	temp = (temp & ~TEMP_DIS_MASK) | TEMP_ENABLE;
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	return;
}

void mpu60x_temperature_disable(void)
{
	uint8_t temp = mpu60x_get_register(MPU60x_PWR_MGMT_1_ADDR);
	temp = (temp & ~TEMP_DIS_MASK) | TEMP_DISABLE;
	mpu60x_set_register(MPU60x_PWR_MGMT_1_ADDR, &temp);
	return;
}

float mpu60x_get_temperature(void)
{
	uint8_t temp[2];
	uint16_t temperature;
	
	temp[0] = mpu60x_read_register(MPU60x_TEMP_OUT_L_ADDR);
	temp[1] = mpu60x_read_register(MPU60x_TEMP_OUT_H_ADDR);
	temperature = (temp[1] << 8)|temp[0];
#if 1
	//return (((float)temperature-(521.0f))/340.0f);
	//return ((float)temperature/340.0f) + 36.53f; 
	return ((125.0f / 65535.0f) * (float)temperature) - 40.0f;
#else
	return (CONST_TEMP*((float)temperature)-40.0f);
#endif
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
	DEBUG_MPU("MPU: %s.\n", mpu_available_table[status]);
	return status;
}	
