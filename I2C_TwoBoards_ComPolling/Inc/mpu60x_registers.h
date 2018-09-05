#ifndef __MPU60x_REGISTERS_H__
#define __MPU60x_REGISTERS_H__
// ADDRESSES
#define MPU60x_I2C_DEVICE_ADDRESS			   0x68

#define MPU60x_WHO_AM_I_ADDR				     0x75
#define MPU60x_WHO_AM_I_EVEL				     0x68

#define MPU60x_SELF_TEST_X_ADDR          0x0D
#define MPU60x_SELF_TEST_Y_ADDR          0x0E
#define MPU60x_SELF_TEST_Z_ADDR          0x0F
#define MPU60x_SELF_TEST_A_ADDR          0x10
#define MPU60x_SMPLRT_DIV_ADDR           0x19
#define MPU60x_CONFIG_ADDR               0x1A
#define MPU60x_GYRO_CONFIG_ADDR          0x1B
#define MPU60x_ACCEL_CONFIG_ADDR         0x1C
#define MPU60x_FIFO_EN_ADDR              0x23
#define MPU60x_I2C_MST_CTRL_ADDR         0x24
#define MPU60x_I2C_SLV0_ADDR_ADDR        0x25
#define MPU60x_I2C_SLV0_REG_ADDR         0x26
#define MPU60x_I2C_SLV0_CTRL_ADDR        0x27
#define MPU60x_I2C_SLV1_ADDR_ADDR        0x28
#define MPU60x_I2C_SLV1_REG_ADDR         0x29
#define MPU60x_I2C_SLV1_CTRL_ADDR        0x2A   
#define MPU60x_I2C_SLV2_ADDR_ADDR        0x2B
#define MPU60x_I2C_SLV2_REG_ADDR         0x2C
#define MPU60x_I2C_SLV2_CTRL_ADDR        0x2D
#define MPU60x_I2C_SLV3_ADDR_ADDR        0x2E
#define MPU60x_I2C_SLV3_REG_ADDR         0x2F
#define MPU60x_I2C_SLV3_CTRL_ADDR        0x30
#define MPU60x_I2C_SLV4_ADDR_ADDR        0x31
#define MPU60x_I2C_SLV4_REG_ADDR         0x32
#define MPU60x_I2C_SLV4_DO_ADDR          0x33
#define MPU60x_I2C_SLV4_CTRL_ADDR        0x34
#define MPU60x_I2C_SLV4_DI_ADDR          0x35
#define MPU60x_I2C_MST_STATUS_ADDR       0x36
#define MPU60x_INT_PIN_CFG_ADDR          0x37
#define MPU60x_INT_ENABLE_ADDR           0x38
#define MPU60x_INT_STATUS_ADDR           0x3A
#define MPU60x_ACCEL_XOUT_H_ADDR         0x3B
#define MPU60x_ACCEL_XOUT_L_ADDR         0x3C
#define MPU60x_ACCEL_YOUT_H_ADDR         0x3D
#define MPU60x_ACCEL_YOUT_L_ADDR         0x3E
#define MPU60x_ACCEL_ZOUT_H_ADDR         0x3F
#define MPU60x_ACCEL_ZOUT_L_ADDR         0x40
#define MPU60x_TEMP_OUT_H_ADDR           0x41
#define MPU60x_TEMP_OUT_L_ADDR           0x42
#define MPU60x_GYRO_XOUT_H_ADDR          0x43
#define MPU60x_GYRO_XOUT_L_ADDR          0x44
#define MPU60x_GYRO_YOUT_H_ADDR          0x45
#define MPU60x_GYRO_YOUT_L_ADDR          0x46
#define MPU60x_GYRO_ZOUT_H_ADDR          0x47
#define MPU60x_GYRO_ZOUT_L_ADDR          0x48
#define MPU60x_EXT_SENS_DATA_00_ADDR     0x49
#define MPU60x_EXT_SENS_DATA_01_ADDR     0x4A
#define MPU60x_EXT_SENS_DATA_02_ADDR     0x4B
#define MPU60x_EXT_SENS_DATA_03_ADDR     0x4C
#define MPU60x_EXT_SENS_DATA_04_ADDR     0x4D
#define MPU60x_EXT_SENS_DATA_05_ADDR     0x4E
#define MPU60x_EXT_SENS_DATA_06_ADDR     0x4F
#define MPU60x_EXT_SENS_DATA_07_ADDR     0x50
#define MPU60x_EXT_SENS_DATA_08_ADDR     0x51
#define MPU60x_EXT_SENS_DATA_09_ADDR     0x52
#define MPU60x_EXT_SENS_DATA_10_ADDR     0x53
#define MPU60x_EXT_SENS_DATA_11_ADDR     0x54
#define MPU60x_EXT_SENS_DATA_12_ADDR     0x55
#define MPU60x_EXT_SENS_DATA_13_ADDR     0x56
#define MPU60x_EXT_SENS_DATA_14_ADDR     0x57
#define MPU60x_EXT_SENS_DATA_15_ADDR     0x58
#define MPU60x_EXT_SENS_DATA_16_ADDR     0x59
#define MPU60x_EXT_SENS_DATA_17_ADDR     0x5A
#define MPU60x_EXT_SENS_DATA_18_ADDR     0x5B
#define MPU60x_EXT_SENS_DATA_19_ADDR     0x5C
#define MPU60x_EXT_SENS_DATA_20_ADDR     0x5D
#define MPU60x_EXT_SENS_DATA_21_ADDR     0x5E
#define MPU60x_EXT_SENS_DATA_22_ADDR     0x5F
#define MPU60x_EXT_SENS_DATA_23_ADDR     0x60
#define MPU60x_I2C_SLV0_DO_ADDR          0x63
#define MPU60x_I2C_SLV1_DO_ADDR          0x64
#define MPU60x_I2C_SLV2_DO_ADDR          0x65
#define MPU60x_I2C_SLV3_DO_ADDR          0x66
#define MPU60x_I2C_MST_DELAY_CTRL_ADDR   0x67
#define MPU60x_SIGNAL_PATH_RESET_ADDR    0x68
#define MPU60x_USER_CTRL_ADDR            0x6A
#define MPU60x_PWR_MGMT_1_ADDR				   0x6B
#define MPU60x_PWR_MGMT_2_ADDR				   0x6C
#define MPU60x_FIFO_COUNTH_ADDR          0x72
#define MPU60x_FIFO_COUNTL_ADDR          0x73
#define MPU60x_FIFO_R_W_ADDR             0x74

//REGISTERS

//MPU60x_CONFIG
#define DLPF_CFG_POS                     0U
#define DLPF_CFG_MASK                    (7U << DLPF_CFG_POS)
#define DLPF   DLPF_CFG_MASK

#define EXT_SYNC_SET_POS                 3U
#define EXT_SYNC_SET_MASK                (7U << EXT_SYNC_SET_POS)

//MPU60x_GYRO_CONFIG
#define FS_SEL_POS                       3U
#define FS_SEL_MASK                      (3U << FS_SEL_POS)

#define ZG_ST_POS                        5U
#define ZG_ST_MASK                       (1U << ZG_ST_POS)

#define YG_ST_POS                        6U
#define YG_ST_MASK                       (1U << YG_ST_POS)

#define XG_ST_POS                        7U
#define XG_ST_MASK                       (1U << XG_ST_POS)

//MPU60x_ACCEL_XOUT
#define MPU60x_ACCEL_XOUT_H_POS              0U
#define MPU60x_ACCEL_XOUT_L              8U

//MPU60x_PWR_MGMT_2
#define CLK_SEL_POS   			             0U
#define CLK_SEL_MASK   			             (7U << CLK_SEL_POS)

#define TEMP_DIS_POS   			             3U
#define TEMP_DIS_MASK   		             (1U << TEMP_DIS_POS)
#define TEMP_ENABLE		                   (0U << TEMP_DIS_POS)
#define TEMP_DISABLE			               (1U << TEMP_DIS_POS)

#define CYCLE_POS                        5U
#define CYCLE_MASK		                   (1U << CYCLE_POS)
#define CYCLE_DISABLE                    (0U << CYCLE_POS)
#define CYCLE_ENABLE                     (1U << CYCLE_POS)

#define SLEEP_POS                        6U
#define SLEEP_MASK                       (1U << SLEEP_POS)
#define SLEEP_DISABLE                    (0U << SLEEP_POS)
#define SLEEP_ENABLE                     (1U << SLEEP_POS)

#define DEVICE_RESET_POS                 7U
#define DEVICE_RESET_MASK                (1U << DEVICE_RESET_POS)
#define DEVICE_RESET_DISABLE             (0U << DEVICE_RESET_POS)
#define DEVICE_RESET_ENABLE              (1U << DEVICE_RESET_POS)

#endif
