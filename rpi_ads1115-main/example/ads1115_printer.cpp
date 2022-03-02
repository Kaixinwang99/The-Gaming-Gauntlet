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

#include "ads1115rpi.h"

// We inherit ADS1115rpi, implement
// hasSample() and print the ADC reading.
class ADS1115Printer : public ADS1115rpi {
	public:
		int current_channel=0;
		float latest_values[4];

		virtual void hasSample(float v) {
			latest_values[current_channel]=v;
			printf("Channel[%d]:%f\n",current_channel,latest_values[current_channel]);
			printf("------\n")
			current_channel = (current_channel+1)%4;
			setChannel((ADS1115settings::Input)current_channel);
		}
};

// Creates an instance of the ADS1115Printer class.
// Prints data till the user presses a key.
int main(int argc, char *argv[]) {
	fprintf(stderr,"Press any key to stop.\n");
	ADS1115Printer ads1115rpi;
        ADS1115settings s;
	s.samplingRate = ADS1115settings::FS64HZ;
	ads1115rpi.start(s);
	getchar();
	ads1115rpi.stop();
	return 0;
}
