/*
 * ADS1115 test/demo program for the Raspberry PI
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 * Copyright (c) 2013-2022  Bernd Porr <mail@berndporr.me.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ads1115rpi.h"
class ADS1115Printer : public ADS1115rpi {
	public:
		unsigned current_channel=0;
		float latest_values[4]={0.0,0.0,0.0,0.0};
		uint8_t output;
		virtual void hasSample(float v) {
			current_channel = (unsigned)getChannel();
			latest_values[current_channel]=v;
			std::cout<<"One: "<<latest_values[0]<<"2|: "<<latest_values[1]<<" | "<<latest_values[2]<<" | "<<latest_values[3]<<"\n";
			current_channel = (current_channel+1)%4;
			setChannel((ADS1115settings::Input) current_channel);
		}
};
// Creates an instance of the ADS1115Printer class.
// Prints data till the user presses a key.
int main(int argc, char *argv[]) {
	fprintf(stderr,"Press any key to stop.\n");
	ADS1115Printer ads1115rpi;
        ADS1115settings s;
	//mainlib m;
	s.samplingRate = ADS1115settings::FS64HZ;
	ads1115rpi.start(s);
	//m.update_fingers(ads1115rpi.latest_values);
	//uint8_t output= m.match_button();
	//std::cout<<"output: "<<output<<"\n";
	getchar();
	ads1115rpi.stop();
	return 0;
}
