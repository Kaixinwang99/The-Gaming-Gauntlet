//-------------------------------MPU6050 Accelerometer and Gyroscope C++ library-----------------------------
//Copyright (c) 2019, Alex Mous
//Licensed under the CC BY-NC SA 4.0

//Include the header file for this class
#include "MPU6050.h"

MPU6050::MPU6050(int8_t addr, bool run_update_thread) {
	int status;

	MPU6050_addr = addr;
	dt = 0.009; //Loop time (recalculated with each loop)
	_first_run = 1; //Variable for whether to set gyro angle to acceleration angle in compFilter
	calc_yaw = false;

	f_dev = open("/dev/i2c-1", O_RDWR); //Open the I2C device file
	if (f_dev < 0) { //Catch errors
		std::cout << "ERR (MPU6050.cpp:MPU6050()): Failed to open /dev/i2c-1. Please check that I2C is enabled with raspi-config\n"; //Print error message
	}

	status = ioctl(f_dev, I2C_SLAVE, MPU6050_addr); //Set the I2C bus to use the correct address
	if (status < 0) {
		std::cout << "ERR (MPU6050.cpp:MPU6050()): Could not get I2C bus with " << addr << " address. Please confirm that this address is correct\n"; //Print error message
	}

	i2c_smbus_write_byte_data(f_dev, 0x6b, 0b00000001); //Take MPU6050 out of sleep mode - see Register Map

	i2c_smbus_write_byte_data(f_dev, 0x1a, 0b00000000); //Set DLPF (low pass filter) to 44Hz (so no noise above 44Hz will pass through)

	i2c_smbus_write_byte_data(f_dev, 0x19, 0b00000111); //Set sample rate divider (to 200Hz) - see Register Map

	i2c_smbus_write_byte_data(f_dev, 0x1b, GYRO_CONFIG); //Configure gyroscope settings - see Register Map (see MPU6050.h for the GYRO_CONFIG parameter)

	i2c_smbus_write_byte_data(f_dev, 0x1c, ACCEL_CONFIG); //Configure accelerometer settings - see Register Map (see MPU6050.h for the GYRO_CONFIG parameter)

	//Set offsets to zero
	i2c_smbus_write_byte_data(f_dev, 0x06, 0b00000000), i2c_smbus_write_byte_data(f_dev, 0x07, 0b00000000), i2c_smbus_write_byte_data(f_dev, 0x08, 0b00000000), i2c_smbus_write_byte_data(f_dev, 0x09, 0b00000000), i2c_smbus_write_byte_data(f_dev, 0x0A, 0b00000000), i2c_smbus_write_byte_data(f_dev, 0x0B, 0b00000000), i2c_smbus_write_byte_data(f_dev, 0x00, 0b10000001), i2c_smbus_write_byte_data(f_dev, 0x01, 0b00000001), i2c_smbus_write_byte_data(f_dev, 0x02, 0b10000001);

	if (run_update_thread){
		std::thread(&MPU6050::_update, this).detach(); //Create a seperate thread, for the update routine to run in the background, and detach it, allowing the program to continue
	}
}

MPU6050::MPU6050(int8_t addr) : MPU6050(addr, true){}

void MPU6050::getGyroRaw(int16_t *roll,int16_t *pitch, int16_t *yaw) {
	int16_t X = i2c_smbus_read_byte_data(f_dev, 0x43) << 8 | i2c_smbus_read_byte_data(f_dev, 0x44); //Read X registers
	int16_t Y = i2c_smbus_read_byte_data(f_dev, 0x45) << 8 | i2c_smbus_read_byte_data(f_dev, 0x46); //Read Y registers
	int16_t Z = i2c_smbus_read_byte_data(f_dev, 0x47) << 8 | i2c_smbus_read_byte_data(f_dev, 0x48); //Read Z registers
	
/*	if(X>32768)X=X-65536; // get signed values 
	if(Y>32768)Y=Y-65536;
	if(Z>32768)Z=Z-65536;
*/	// std::cout<<"Gyro Raw values:"<<"\n";
	*roll = X; //Roll on X axis
	*pitch = Y; //Pitch on Y axis
	*yaw = Z; //Yaw on Z axis
}

/*void MPU6050::getGyro(float *roll, float *pitch, float *yaw) {
	getGyroRaw(roll, pitch, yaw); //Store raw values into variables
	*roll = round((*roll - G_OFF_X) * 1000.0 / GYRO_SENS) / 1000.0; //Remove the offset and divide by the gyroscope sensetivity (use 1000 and round() to round the value to three decimal places)
	*pitch = round((*pitch - G_OFF_Y) * 1000.0 / GYRO_SENS) / 1000.0;
	*yaw = round((*yaw - G_OFF_Z) * 1000.0 / GYRO_SENS) / 1000.0;
}*/

void MPU6050::getAccelRaw(float *x, float *y, float *z) {
	int16_t X = i2c_smbus_read_byte_data(f_dev, 0x3b) << 8 | i2c_smbus_read_byte_data(f_dev, 0x3c); //Read X registers
	int16_t Y = i2c_smbus_read_byte_data(f_dev, 0x3d) << 8 | i2c_smbus_read_byte_data(f_dev, 0x3e); //Read Y registers
	int16_t Z = i2c_smbus_read_byte_data(f_dev, 0x3f) << 8 | i2c_smbus_read_byte_data(f_dev, 0x40); //Read Z registers
	*x = (float)X;
	*y = (float)Y;
	*z = (float)Z;
}

void MPU6050::getAccel(float *x, float *y, float *z) {
	getAccelRaw(x, y, z); //Store raw values into variables
	*x = round((*x - A_OFF_X) * 1000.0 / ACCEL_SENS) / 1000.0; //Remove the offset and divide by the accelerometer sensetivity (use 1000 and round() to round the value to three decimal places)
	*y = round((*y - A_OFF_Y) * 1000.0 / ACCEL_SENS) / 1000.0;
	*z = round((*z - A_OFF_Z) * 1000.0 / ACCEL_SENS) / 1000.0;
}

/*void MPU6050::getOffsets(float *ax_off, float *ay_off, float *az_off, float *gr_off, float *gp_off, float *gy_off) {
	float gyro_off[3]; //Temporary storage
	float accel_off[3];

	*gr_off = 0, *gp_off = 0, *gy_off = 0; //Initialize the offsets to zero
	*ax_off = 0, *ay_off = 0, *az_off = 0; //Initialize the offsets to zero

	for (int i = 0; i < 10000; i++) { //Use loop to average offsets
		getGyroRaw(&gyro_off[0], &gyro_off[1], &gyro_off[2]); //Raw gyroscope values
		*gr_off = *gr_off + gyro_off[0], *gp_off = *gp_off + gyro_off[1], *gy_off = *gy_off + gyro_off[2]; //Add to sum

		getAccelRaw(&accel_off[0], &accel_off[1], &accel_off[2]); //Raw accelerometer values
		*ax_off = *ax_off + accel_off[0], *ay_off = *ay_off + accel_off[1], *az_off = *az_off + accel_off[2]; //Add to sum
	}

	*gr_off = *gr_off / 10000, *gp_off = *gp_off / 10000, *gy_off = *gy_off / 10000; //Divide by number of loops (to average)
	*ax_off = *ax_off / 10000, *ay_off = *ay_off / 10000, *az_off = *az_off / 10000;

	*az_off = *az_off - ACCEL_SENS; //Remove 1g from the value calculated to compensate for gravity)
}*/

int MPU6050::getAngle(int axis, float *result) {
	if (axis >= 0 && axis <= 2) { //Check that the axis is in the valid range
		*result = _angle[axis]; //Get the result
		return 0;
	}
	else {
		std::cout << "ERR (MPU6050.cpp:getAngle()): 'axis' must be between 0 and 2 (for roll, pitch or yaw)\n"; //Print error message
		*result = 0; //Set result to zero
		return 1;
	}
}

void MPU6050::_update() { //Main update function - runs continuously
	//TODO: Update thread
}
