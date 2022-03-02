#ifndef _JOYLIB_H
#define _JOYLIB_H
#include <cstdint>
#include <iostream>
#include <fstream>

// Declare and include all the neccessary libs here 

class JoyLib {
    public:
        bool begin(char* device);
        bool press(int8_t button);
        bool release(int8_t button);
        bool releaseAll();
        bool xAxis(int8_t value);
        bool yAxis(int8_t value);
        uint8_t get_buttons();
        uint16_t get_axis();
    private:
        std::ofstream fout;
        uint8_t out_bytes[3] = {0,0,0};
        bool write();


};

#endif
