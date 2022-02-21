
#include "MPU6050.h"
#include <math.h>
#include <time.h>

MPU6050 device(0x68,false); //Initialize MPU 


int main() {
	float  gr, gp, gy; //Varaibles to store gyro values
	bool first=true;
	float x=0,y=0,prev_gr=0,prev_gp=0;
        struct timespec now;
	long int prev,dt;

	clock_gettime(CLOCK_REALTIME,&now); //record start time 
	prev = now.tv_nsec;
	while(true) {

		device.getGyroRaw(&gr,&gp,&gy); //read gyro values
		
		gr=gr/131.0; //convert raw gyro values into approx deg/sec
		gy=gy/131.0;

		gr=abs(gr)<0.5?0:gr; //filter to reduce low level noise
		gy=abs(gy)<0.5?0:gy;

		clock_gettime(CLOCK_REALTIME,&now); //get time elapsed
		dt = now.tv_nsec-prev;

		x=x+((float)dt/1000000000.0)*((gr-prev_gr)/2.0); //Numerically Integrate over dt(nsec)
		y=y+((float)dt/1000000000.0)*((gy-prev_gp)/2.0);

		std::cout<<"time:"<<dt<<"\n\n";
		printf("[Gr]:%0.2f [Gy]:%0.2f\n[x]:%.2f  [y]:%0.2f\n\n",gr,gy,x,y);

		prev = now.tv_nsec; //update strat time

		usleep(10);
	}
	return 0;
}


