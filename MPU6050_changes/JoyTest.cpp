
#include "MPU6050.h"
#include <math.h>
#include <time.h>

MPU6050 device(0x68,false);


int main() {
	float  gr, gp, gy; //Variables to store the accel, gyro and angle values
	bool first=true;
	float x=0,y=0;
        struct timespec now;
	long int prev,diff;
	//Calculate the offsets
/*	std::cout << "Calculating the offsets...\n    Please keep the accelerometer level and still\n    This could take a couple of minutes...";
	device.getOffsets(&ax, &ay, &az, &gr, &gp, &gy);
	std::cout << "Gyroscope R,P,Y: " << gr << "," << gp << "," << gy << "\nAccelerometer X,Y,Z: " << ax << "," << ay << "," << az << "\n";
*/

	//Read the current yaw angle
	device.calc_yaw = false;
	clock_gettime(CLOCK_REALTIME,&now);
	prev = now.tv_nsec;
	while(true) {
//		device.getAngle(0, &gr);
//		device.getAngle(1, &gp);
//		device.getAngle(2, &gy);
		device.getGyroRaw(&gr,&gp,&gy);
		
		
		
		//device.getAccel(&ax,&ay,&az);
/*		if(first){
		 x_offset=gr;
		 y_offset=gp;
		 first=false;
		}
		x = gr-x_offset;
		y = gp-y_offset;
		
		rn = 127*(x/abs(x));
		pn = 127*(y/abs(y));
*/
		gr=gr/131.0;
		gy=gy/131.0;
		gr=abs(gr)<0.5?0:gr;
		gy=abs(gy)<0.5?0:gy;

		clock_gettime(CLOCK_REALTIME,&now);
		diff = now.tv_nsec-prev;
		x=x+((float)diff/1000000000.0)*gr;
		y=y+((float)diff/1000000000.0)*gy;

		std::cout<<"time:"<<diff<<"\n";
//		std::cout<<"gr: "<<gr<<" gy: "<<gy<<"\n"<<"x: "<<x<<"y: "<<y<<"\n";

		prev = now.tv_nsec;

		usleep(10);
	}
	return 0;
}


