#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "mainlib.cpp"
#include "../ICM20948/rpi_ICM20948/icm20948.cpp"
#include "../rpi_ads1115-main/ads1115rpi.cpp"
#include "../JoyController/JoyLib/JoyLib.cpp"
// We inherit ADS1115rpi, implement
// hasSample() and print the ADC reading.
class ADS1115Printer : public ADS1115rpi {
	public:
		unsigned current_channel=0;
		float latest_values[4]={0.0,0.0,0.0,0.0};
		uint8_t output;
		virtual void hasSample(float v) {
			current_channel = (unsigned)getChannel();
			latest_values[current_channel]=v;
			m.update_fingers(latest_values);
			output = m.match_button();
			if (output==8){
				joy.releaseALL();
			}
			else if(joy.get_buttons()!=output){
				joy.press(output);
			}
			std::cout<<"output button: "<<(int)output<<"\n";
			current_channel = (current_channel+1)%4;
			setChannel((ADS1115settings::Input) current_channel);
		}
};

int main(int, char**){
	icm20948 imu;
	float x,y,z;
	mainlib m;
	ADS1115Printer ads1115rpi;
	ADS1115settings s;
	s.samplingRate = ADS1115settings::FS64HZ;
	JoyLib joy;
	joy.begin("/dev/hidg0");
	ads1115rpi.start(s);
	getchar();
	ads1115rpi.stop();
	return 0;
	/*
	while(true){
		imu.read_magnetometer_data(&x,&y,&z);
		m.update_axis(x,y,z);
		std::array<uint8_t,2> output;
		output = m.getAxis();
		joy.xAxis((int8_t)(output[1]-128));
		joy.yAxis((int8_t)(output[0]-128));
		//std::cout<<"x: "<<(int)output[1]-128<<"y: "<<(int)output[0]-128<<"\n";
	}
	*/
}
