#include "main.h"

#include "tick.h"
#include "mpu60x.h"
#include "mpu60x_registers.h"
#include "string.h"

#define REGISTERS_NUM        118
	
static void SystemClock_Config(void);
//static void Error_Handler(void);

static void i2c_init(void);
static void get_all_registers(uint8_t *vector);

const char* const hal_status_table[] = {"OK", "ERROR", "BUSY", "TIMEOUT"};

static I2C_HandleTypeDef I2cHandle;
//static MPU60x_States mpu_state;
//static MPU60x_Available mpu_available;

uint16_t test;
//static uint8_t aTxBuffer;
static uint8_t aRxBuffer[REGISTERS_NUM];
static uint8_t all[REGISTERS_NUM];

//static uint8_t sample_rate_div = 0xFF;
//static uint8_t dlpf = 0x01;

int main(void)
{    
  HAL_Init();
	SystemClock_Config();
	
	debug_init();
	i2c_init();	
	mpu60x_set_i2c(&I2cHandle);
	
	memset(&aRxBuffer[0], 0xFF, REGISTERS_NUM);
	memset(&all[0], 0xFF, REGISTERS_NUM);
	
	mpu60x_available();
	mpu60x_wake();
	
	while (1)
	{
		test = mpu60x_get_sensor( MPU60x_TEMPERATURE_SENSOR, MPU60x_Z_AXIS);
		PRINTS("accel axisx: %d.\n", test);
		HAL_Delay(1000);
	}
}

static void get_all_registers(uint8_t *vector)
{
	for(uint8_t i = 0; i <= REGISTERS_NUM; i++)
	{
		PRINTS("Getting register %d: ", i);
		vector[i] = mpu60x_read_register(i);
	}
}

static void i2c_init(void)
{
	HAL_StatusTypeDef status;
	
	I2cHandle.Instance             = I2C1;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.ClockSpeed      = 400000;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  I2cHandle.Init.OwnAddress1     = 0;
  I2cHandle.Init.OwnAddress2     = 0;
  
	status = HAL_I2C_Init(&I2cHandle);

	PRINTS("HAL status: %s, in file %s at function %s() in line %i.\n",
			hal_status_table[status], __FILE__, __FUNCTION__, __LINE__);
	
	return;
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  if (HAL_GetREVID() == 0x1001)
  {
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

//void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
//{
//  /* Turn LED5 on: Transfer error in reception/transmission process */
////  BSP_LED_On(LED5); 
//}

//static void Error_Handler(void)
//{
//  while(1);
//}
