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
