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

int main(int, char**){
	icm20948 imu;
	float x,y,z;
	mainlib m;
	while(true){
		imu.read_magnetometer_data(&x,&y,&z);
		m.update_axis(x,y,z);
		std::array<uint8_t,2> output;
		output = m.getAxis();
		std::cout<<"x: "<<output[0]<<"y: "<<output[1]<<"\n";
	}
}
