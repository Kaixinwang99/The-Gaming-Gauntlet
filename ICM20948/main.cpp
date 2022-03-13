#include <iostream>
#include <icm20948.h>


int main(int, char**) {
   icm20948 imu;
   float x,y,z;
   while(true){
   imu.read_magnetometer_data(&x,&y,&z);
   std::cout<<x<<" "<<y<<" "<<z<<"\n";
   }
}
