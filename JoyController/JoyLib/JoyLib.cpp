#include "JoyLib.h"
#include <iostream>

//define all the functions here

bool JoyLib::press(int8_t button){
    //TODO:update JoyLib::out_bytes[2] to press a button and call write
    // printf("%d",button); //CMake Env test
}

bool JoyLib::release(int8_t button){
    //TODO:update JoyLib::out_bytes[2] to release one button and call write
}

bool JoyLib::releaseAll(){
    //TODO:update JoyLib::out_bytes[2] to release all buttons and call write
}

bool JoyLib::xAxis(int8_t value){
    //TODO:update JoyLib::out_bytes[0] and call write
}

bool JoyLib::yAxis(int8_t value){
    //TODO:update JoyLib::out_bytes[2] and call write
}



bool JoyLib::write(){
    //TODO: write bytes in JoyLib::out_bytes to /dev/hidg0
}