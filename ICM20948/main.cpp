#include "icm20948.h"
#include "../new_class/mainlib.cpp"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../JoyController/JoyLib/JoyLib.cpp"
#include "ads1115rpi.cpp"
class ADS1115Printer : public ADS1115rpi {
	public:
		unsigned current_channel=0;
		float latest_values[4]={0.0,0.0,0.0,0.0};
	
		virtual void hasSample(float v) {
			current_channel = (unsigned)getChannel();
			latest_values[current_channel]=v;
			current_channel = (current_channel+1)%4;
			setChannel((ADS1115settings::Input) current_channel);
		}
};
int main(int, char**){
	icm20948 imu;
	float x,y,z;
	uint8_t bout;
	mainlib m;
	JoyLib joy;
	
	ADS1115Printer buttons;
  	ADS1115settings s;
	s.samplingRate = ADS1115settings::FS64HZ;
	buttons.start(s);	

	joy.begin("/dev/hidg0");
	while(true){
		imu.read_magnetometer_data(&x,&y,&z);
		m.update_axis(x,y,z);
		std::array<uint8_t,2> output;
		output = m.getAxis();
		joy.xAxis((int8_t)output[1]);
		joy.yAxis((int8_t)output[0]);

			m.update_fingers(buttons.latest_values);
			bout = m.match_button();
			if (bout==8){
				joy.releaseAll();
			}
			else if(joy.get_buttons()!=bout){
				joy.press(bout);
			}
			std::cout<<"output button: "<<(int)bout<<"\n";


		std::cout<<"x: "<<(int)output[1]-128<<"y: "<<(int)output[0]-128<<"\n";
		//std::cout<<m.fingers[0]<<"/n";
		//std::cout<<"one: "<<buttons.latest_values[0]<<" | "<<buttons.latest_values[1]<<" | "<<buttons.latest_values[2]<<" | "<<buttons.latest_values[3]<<"\n";
	}
	buttons.stop();
}
