#include "JoyLib.h"
#include <iostream>
#include <fstream>

//define all the functions here
uint8_t JoyLib::get_buttons(){
    return out_bytes[2];
}

uint16_t JoyLib::get_axis(){
    return (out_bytes[0]<<8|out_bytes[1]);
}

bool JoyLib::press(int8_t button){
    //TODO:update JoyLib::out_bytes[2] to press a button and call write
    out_bytes[2]= out_bytes[2]|(1<<(button-1));
    write();
    return true;
}

bool JoyLib::release(int8_t button){
    //TODO:update JoyLib::out_bytes[2] to release one button and call write
    out_bytes[2]= out_bytes[2]&(~(1<<(button-1)));
    write();
    return true;
}

bool JoyLib::releaseAll(){
    //TODO:update JoyLib::out_bytes[2] to release all buttons and call write
    out_bytes[2]=0;
    write();
    return true;
}

bool JoyLib::xAxis(int8_t value){
    //TODO:update JoyLib::out_bytes[0] and call write
    write();
}

bool JoyLib::yAxis(int8_t value){
    //TODO:update JoyLib::out_bytes[1] and call write
    write();
}



bool JoyLib::write(){
    //TODO: write bytes in JoyLib::out_bytes to /dev/hidg0
    std::ofstream fout;
    fout.open("try.txt", std::ios::binary | std::ios::out);

    fout.write((char*) &out_bytes, sizeof(out_bytes));

    fout.close();
    return true;
}