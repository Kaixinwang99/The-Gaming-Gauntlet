#include "icm20948.h"
static const char could_not_open_i2c[] = "Could not open I2C.\n";

uint8_t icm20948::read(uint8_t reg){
    int fd = i2cOpen(bus,I2C_ADDR,0);
    if (fd < 0) {
        fprintf(stderr,"Could not open %02x.\n",I2C_ADDR);
        throw could_not_open_i2c;
    }
    int r;
    r = i2cReadByteData(fd,(unsigned int)reg);
    if (r < 0) {
        fprintf(stderr,"Could not read word from %02x. ret=%d.\n",I2C_ADDR,r);
        throw "Could not read from i2c.";
    }
    i2cClose(fd);
    return (uint8_t)r;
}

void icm20948::write(uint8_t reg,uint8_t value){
    int fd = i2cOpen(bus,I2C_ADDR,0);
    if (fd < 0) {
        fprintf(stderr,"Could not open %02x.\n",I2C_ADDR);
        throw could_not_open_i2c;
    }
    int r;
    r = i2cWriteByteData(fd,(unsigned int)reg,(unsigned int)value);
    if (r < 0) {
        fprintf(stderr,"Could not write byte to %02x. ret=%d.\n",I2C_ADDR,r);
        throw "Could not write to i2c.";
    }
    i2cClose(fd);
}

void icm20948::trigger_mag_io(){
    uint8_t user = read(ICM20948_USER_CTRL);
    write(ICM20948_USER_CTRL, user | 0x20);
    usleep(5);
    write(ICM20948_USER_CTRL, user);
}

void icm20948::read_bytes(uint8_t reg,uint8_t* bytes,int len){
    int fd = i2cOpen(bus,I2C_ADDR,0);
    if (fd < 0) {
        fprintf(stderr,"Could not open %02x.\n",I2C_ADDR);
        throw could_not_open_i2c;
    }
    int r;
    r=i2cReadI2CBlockData(fd,reg,(char*)bytes,len);
    if (r < 0) {
        fprintf(stderr,"Could not bulk read from %02x. ret=%d.\n",I2C_ADDR,r);
        throw "Could not read from i2c.";
    }
    i2cClose(fd);
}

void icm20948::bank(uint8_t value){
    if(_bank!=value){
        write(ICM20948_BANK_SEL,value<<4);
        _bank=value;
    }
}
void icm20948::mag_write(uint8_t reg,uint8_t value){
    bank(3);
    write(ICM20948_I2C_SLV0_ADDR, AK09916_I2C_ADDR);
    write(ICM20948_I2C_SLV0_REG, reg);
    write(ICM20948_I2C_SLV0_DO, value);
    bank(0);
    trigger_mag_io();
}

uint8_t icm20948::mag_read(uint8_t reg){
    bank(3);
    write(ICM20948_I2C_SLV0_ADDR, AK09916_I2C_ADDR | 0x80);
    write(ICM20948_I2C_SLV0_REG, reg);
    write(ICM20948_I2C_SLV0_DO, 0xff);
    write(ICM20948_I2C_SLV0_CTRL, 0x80 | 1);
    bank(0);
    trigger_mag_io();
    return read(ICM20948_EXT_SLV_SENS_DATA_00);
}

void icm20948::mag_read_bytes(uint8_t reg,uint8_t* bytes,int len){

    bank(3);
    write(ICM20948_I2C_SLV0_CTRL, 0x80 | 0x08 | len);
    write(ICM20948_I2C_SLV0_ADDR, AK09916_I2C_ADDR | 0x80);
    write(ICM20948_I2C_SLV0_REG, reg);
    write(ICM20948_I2C_SLV0_DO, 0xff);
    bank(0);
    trigger_mag_io();
    read_bytes(ICM20948_EXT_SLV_SENS_DATA_00,bytes,len);
}

bool icm20948::magnetometer_ready(){
    return mag_read(AK09916_ST1)&0x01 > 0;
}

void icm20948::read_magnetometer_data(float* x,float* y,float* z,int timeout){
    mag_write(AK09916_CNTL2, 0x01);
    std::chrono::steady_clock::time_point t_start = std::chrono::steady_clock::now();
    while(!magnetometer_ready()){
        std::chrono::steady_clock::time_point t_now = std::chrono::steady_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(t_now-t_start).count()>timeout){
            throw "Timeout reading magnetometer";
        }
        usleep(10);
    }
    uint8_t buff[6];
    int16_t _x,_y,_z;
    mag_read_bytes(AK09916_HXL,buff, 6);
    _x = buff[1]<<8|buff[0];
    _y = buff[3]<<8|buff[2];
    _z = buff[5]<<8|buff[4];

    *x = _x*0.15;
    *y = _y*0.15;
    *z = _z*0.15;
}

void icm20948::read_accelerometer_gyro_data(float* ax,float* ay,float* az,float* gx,float* gy,float* gz){
    bank(0);
    uint8_t buff[12];
    read_bytes(ICM20948_ACCEL_XOUT_H,buff, 12);
    int16_t _ax,_ay,_az,_gx,_gy,_gz;
    _ax = buff[0]<<8|buff[1];
    _ay = buff[2]<<8|buff[3];
    _az = buff[4]<<8|buff[5];

    _gx = buff[6]<<8|buff[7];
    _gy = buff[8]<<8|buff[9];
    _gz = buff[10]<<8|buff[11];

    bank(2);
    uint8_t acc_scale = read(ICM20948_ACCEL_CONFIG) & 0x06 >> 1;
    uint8_t gyro_scale = read(ICM20948_GYRO_CONFIG_1) & 0x06 >>1;

    float gs = g_scales[gyro_scale];
    float dps = dps_scales[acc_scale];

    *ax = (float)_ax / dps;
    *ay = (float)_ay / dps;
    *az = (float)_az / dps;

    *gx = (float)_gx / gs;
    *gy = (float)_gy / gs;
    *gz = (float)_gz / gs;

}

void icm20948::set_accelerometer_sample_rate(int rate){
    bank(2);
    int out_rate;
    out_rate = (int)((1125.0/rate)-1);
    write(ICM20948_ACCEL_SMPLRT_DIV_1, (out_rate >> 8) & 0xff);
    write(ICM20948_ACCEL_SMPLRT_DIV_2, out_rate & 0xff);
}

void icm20948::set_accelerometer_full_scale(uint8_t scale){
    bank(2);
    uint8_t val = read(ICM20948_ACCEL_CONFIG) & 0b11111001;
    val = val|(scale<<1);
    write(ICM20948_ACCEL_CONFIG, val);

}

void icm20948::set_accelerometer_low_pass(bool enabled,uint8_t mode){
    bank(2);
    uint8_t val = read(ICM20948_ACCEL_CONFIG) & 0b10001110;
    if(enabled){
        val = val | 1;
    }
    val = val|(mode&0x07)<<4;
    write(ICM20948_ACCEL_CONFIG,val);
}

void icm20948::set_gyro_sample_rate(int rate){
    bank(2);
    int out_rate;
    out_rate = (int)((1125.0/rate)-1);
    write(ICM20948_GYRO_SMPLRT_DIV, out_rate);
}

void icm20948::set_gyro_full_scale(uint8_t scale){
    bank(2);
    uint8_t val = read(ICM20948_GYRO_CONFIG_1) & 0b11111001;
    val = val| scale << 1;
    write(ICM20948_GYRO_CONFIG_1, val);
}

void icm20948::set_gyro_low_pass(bool enabled,uint8_t mode){
    bank(2);
    uint8_t val = read(ICM20948_GYRO_CONFIG_1) & 0b10001110;
    if(enabled) val|=1;
    val |=(mode&0x07)<<4;
    write(ICM20948_GYRO_CONFIG_1, val);
}

float icm20948::read_temp(){
    bank(0);
    uint8_t buff[2];
    read_bytes(ICM20948_TEMP_OUT_H,buff,2);
    unsigned int temp_raw = buff[0]<<8|buff[1];
    float temperature_deg_c = ((temp_raw - ICM20948_ROOM_TEMP_OFFSET) / ICM20948_TEMPERATURE_SENSITIVITY) + ICM20948_TEMPERATURE_DEGREES_OFFSET;
    return temperature_deg_c;
}

icm20948::icm20948(uint8_t addr){
    _addr=addr;
    bank(0);
    if(read(ICM20948_WHO_AM_I) != CHIP_ID){
        throw "Cannot find ICM20948";
    }
    write(ICM20948_PWR_MGMT_1, 0x80);
    usleep(1000);
    write(ICM20948_PWR_MGMT_1, 0x01);
    write(ICM20948_PWR_MGMT_2, 0x00);

    bank(2);
    set_gyro_sample_rate(100);
    set_gyro_low_pass(true,5);
    set_gyro_full_scale(0);
    set_accelerometer_sample_rate(125);
    set_accelerometer_low_pass(true, 5);
    set_accelerometer_full_scale(3);

    bank(0);
    write(ICM20948_INT_PIN_CFG, 0x30);

    bank(3);
    write(ICM20948_I2C_MST_CTRL, 0x4D);
    write(ICM20948_I2C_MST_DELAY_CTRL, 0x01);

    if(mag_read(AK09916_WIA) != AK09916_CHIP_ID){
        throw "unable to find Magnetometer chip";
    }

    mag_write(AK09916_CNTL3, 0x01);
    while(mag_read(AK09916_CNTL3) == 0x01){
        usleep(100);
    }
}