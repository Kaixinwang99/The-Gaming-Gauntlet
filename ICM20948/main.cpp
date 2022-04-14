/*
#include <iostream>
#include <icm20948.h>
#include <math.h>

int main(int, char**) {
   icm20948 imu;
   float x,y,z,nx,ny,nz,n;
   while(true){
   imu.read_magnetometer_data(&x,&y,&z);
   n = 1/sqrt(x*x+y*y+z*z);
   nx=n*x;
   ny=n*y;
   nz=n*z;
   std::cout<<nx<<" "<<ny<<" "<<nz<<"\n";
   }
}
*/

#include "icm20948.h"
#include "mainlib.cpp"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../JoyController/JoyLib/JoyLib.cpp"
int main(int, char**){
	icm20948 imu;
	float x,y,z;
	mainlib m;
	JoyLib joy;
	joy.begin("/dev/hidg0");
	while(true){
		imu.read_magnetometer_data(&x,&y,&z);
		m.update_axis(x,y,z);
		std::array<uint8_t,2> output;
		output = m.getAxis();
		joy.xAxis((int8_t)(output[1]-128));
		joy.yAxis((int8_t)(output[0]-128));
		std::cout<<"x: "<<(int)output[1]-128<<"y: "<<(int)output[0]-128<<"\n";
	}
}
