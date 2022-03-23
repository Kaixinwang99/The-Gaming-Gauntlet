#ifndef __ICM20948__
#define __ICM20948__

#define CHIP_ID  0xEA
#define I2C_ADDR  0x68
#define I2C_ADDR_ALT  0x69
#define ICM20948_BANK_SEL  0x7f

#define ICM20948_I2C_MST_ODR_CONFIG  0x00
#define ICM20948_I2C_MST_CTRL  0x01
#define ICM20948_I2C_MST_DELAY_CTRL  0x02
#define ICM20948_I2C_SLV0_ADDR  0x03
#define ICM20948_I2C_SLV0_REG  0x04
#define ICM20948_I2C_SLV0_CTRL  0x05
#define ICM20948_I2C_SLV0_DO  0x06
#define ICM20948_EXT_SLV_SENS_DATA_00  0x3B

#define ICM20948_GYRO_SMPLRT_DIV  0x00
#define ICM20948_GYRO_CONFIG_1  0x01
#define ICM20948_GYRO_CONFIG_2  0x02

//Bank 0
#define ICM20948_WHO_AM_I  0x00
#define ICM20948_USER_CTRL  0x03
#define ICM20948_PWR_MGMT_1  0x06
#define ICM20948_PWR_MGMT_2  0x07
#define ICM20948_INT_PIN_CFG  0x0F

#define ICM20948_ACCEL_SMPLRT_DIV_1  0x10
#define ICM20948_ACCEL_SMPLRT_DIV_2  0x11
#define ICM20948_ACCEL_INTEL_CTRL  0x12
#define ICM20948_ACCEL_WOM_THR  0x13
#define ICM20948_ACCEL_CONFIG  0x14
#define ICM20948_ACCEL_XOUT_H  0x2D
#define ICM20948_GRYO_XOUT_H  0x33

#define ICM20948_TEMP_OUT_H  0x39
#define ICM20948_TEMP_OUT_L  0x3A

// Offset and sensitivity - defined in electrical characteristics, and TEMP_OUT_H/L of datasheet
#define ICM20948_TEMPERATURE_DEGREES_OFFSET  21
#define ICM20948_TEMPERATURE_SENSITIVITY  333.87
#define ICM20948_ROOM_TEMP_OFFSET  21

#define AK09916_I2C_ADDR  0x0c
#define AK09916_CHIP_ID  0x09
#define AK09916_WIA  0x01
#define AK09916_ST1  0x10
#define AK09916_ST1_DOR  0b00000010   # Data overflow bit
#define AK09916_ST1_DRDY  0b00000001  # Data ready bit
#define AK09916_HXL  0x11
#define AK09916_ST2  0x18
#define AK09916_ST2_HOFL  0b00001000  # Magnetic sensor overflow bit
#define AK09916_CNTL2  0x31
#define AK09916_CNTL2_MODE  0b00001111
#define AK09916_CNTL2_MODE_OFF  0
#define AK09916_CNTL2_MODE_SINGLE  1
#define AK09916_CNTL2_MODE_CONT1  2
#define AK09916_CNTL2_MODE_CONT2  4
#define AK09916_CNTL2_MODE_CONT3  6
#define AK09916_CNTL2_MODE_CONT4  8
#define AK09916_CNTL2_MODE_TEST  16
#define AK09916_CNTL3  0x32

#include <cstdint>
#include<pigpio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>

/**
 * @brief 
 * Class for ICM20948 accelerometer, magnetometer and gyroscope 
 */

class icm20948{
    
    public:
        /**
         * @brief Construct a new icm20948 object
         * 
         * @param addr 
         */
        icm20948(uint8_t addr=0x68);//done
        ~icm20948(){gpioTerminate();}
        /**
         * @brief 
         * Initialize sensor 
         * @return true 
         * @return false 
         */
        bool magnetometer_ready();//done
        /**
         * @brief 
         * Reads the data from the magnetometer
         * @param x pointer to a float where X values of the magnetometer will be stored  
         * @param y pointer to a float where Y values of the magnetometer will be stored 
         * @param z pointer to a float where Z values of the magnetometer will be stored  
         * @param timeout set to 1000 by default 
         */
        void read_magnetometer_data(float* x,float* y,float* z,int timeout=1000);//done
        /**
         * @brief 
         * Read accelerometer and gyroscope data
         * @param ax pointer to a float where X values of the accelerometer will be stored 
         * @param ay pointer to a float where Y values of the accelerometer will be stored
         * @param az pointer to a float where Z values of the accelerometer will be stored
         * @param gx pointer to a float where X values of the gyroscope will be stored
         * @param gy pointer to a float where Y values of the gyroscope will be stored
         * @param gz pointer to a float where Z values of the gyroscope will be stored
         */
        void read_accelerometer_gyro_data(float* ax,float* ay,float* az,float* gx,float* gy,float* gz);//done
        /**
         * @brief Set the accelerometer sample rate 
         * 
         * @param rate set to 125 by default
         */
        void set_accelerometer_sample_rate(int rate=125);//done
        /**
         * @brief Set the accelerometer full scale 
         * 
         * @param scale set to 3 by default
         */
        void set_accelerometer_full_scale(uint8_t scale=3);//done
        /**
         * @brief Set the accelerometer low pass filter
         * 
         * @param enabled set to True by default 
         * @param mode set to 5 by default
         */
        void set_accelerometer_low_pass(bool enabled=true,uint8_t mode=5);//done
        /**
         * @brief Set the gyro sample rate 
         * 
         * @param rate set to 125 by default 
         */
        void set_gyro_sample_rate(int rate=125);//done
        /**
         * @brief Set the gyro full scale 
         * 
         * @param scale set to 0 by default 
         */
        void set_gyro_full_scale(uint8_t scale=0);//done
        /**
         * @brief Set the gyro low pass 
         * 
         * @param enabled set to True to default 
         * @param mode set to 5 by default
         */
        void set_gyro_low_pass(bool enabled=true,uint8_t mode=5);//done
        /**
         * @brief read temperature
         * 
         * @return float 
         */
        float read_temp();//done
        int bus=1;

    private:
        /**
         * @brief 
         * 
         */
        uint8_t _bank=-1,_addr=I2C_ADDR;
        /**
         * @brief 
         * 
         */
        float g_scales[4] = {16384.0, 8192.0, 4096.0, 2048.0};
        /**
         * @brief 
         * 
         */
        float dps_scales[4] = {131.0, 65.5, 32.8, 16.40};
        /**
         * @brief 
         * 
         * @param reg 
         * @param bytes 
         * @param len 
         */
        void mag_read_bytes(unsigned int reg,uint8_t* bytes,int len);//done
        /**
         * @brief 
         * 
         * @param reg 
         * @return uint8_t 
         */
        uint8_t mag_read(unsigned int reg); //done
        /**
         * @brief 
         * 
         * @param reg 
         * @param value 
         */
        void mag_write(unsigned int reg,uint8_t value);//done
        /**
         * @brief 
         * 
         * @param value 
         */
        void bank(uint8_t value);//done
        /**
         * @brief 
         * 
         * @param reg 
         * @param bytes 
         * @param len 
         */
        void read_bytes(unsigned int reg,uint8_t* bytes,int len);//done
        /**
         * @brief 
         * 
         */
        void trigger_mag_io();//done
        /**
         * @brief 
         * 
         * @param reg 
         * @return uint8_t 
         */
        uint8_t read(unsigned int reg);//done
        /**
         * @brief 
         * 
         * @param reg 
         * @param value 
         */
        void write(unsigned int reg,unsigned int value); //done
};







#endif