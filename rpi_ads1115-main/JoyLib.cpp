#include "JoyLib.h"


//define all the functions here
uint8_t JoyLib::get_buttons(){
    return out_bytes[2];
}

uint16_t JoyLib::get_axis(){
    return (out_bytes[0]<<8|out_bytes[1]);
}

bool JoyLib::begin(const char* device){
  fout.open(device, std::ios::binary | std::ios::out);
  write();

}

bool JoyLib::press(int8_t button){
    //to press a button and call write
    out_bytes[2]= out_bytes[2]|(1<<(button-1));
    write();
    return true;
}

bool JoyLib::release(int8_t button){
    // to release one button and call write
    out_bytes[2]= out_bytes[2]&(~(1<<(button-1)));
    write();
    return true;
}

bool JoyLib::releaseAll(){
    //to release all buttons and call write
    out_bytes[2]=0;
    write();
    return true;
}

bool JoyLib::xAxis(int8_t value){
    //set X-Axis and call write
    out_bytes[0]=value;
    write();
}

bool JoyLib::yAxis(int8_t value){
    //set Y-Axis and call write
    out_bytes[1]=value;
    write();
}



bool JoyLib::write(){

    fout.write((char*) &out_bytes, sizeof(out_bytes));
    fout.flush();

    return true;
}