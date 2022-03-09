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