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