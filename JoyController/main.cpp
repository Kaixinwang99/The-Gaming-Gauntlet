#include <iostream>
#include <JoyLib.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

int main(int, char**) {
    JoyLib joy;
    const char* device = "/dev/hidg0";
    std::cout<<"\nStarting joy with device:"<<device<<"\n";
    joy.begin(device);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"\nPressing button 8"<<"\n";
    joy.press(8);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());

    std::cout<<"\nReleasing button 8"<<"\n";
    joy.release(8);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());


    std::cout<<"\nPressing buttons 1,2,3"<<"\n";
    joy.press(1);
    joy.press(2);
    joy.press(3);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());

    std::cout<<"\nReleasing all buttons"<<"\n";
    joy.releaseAll();
    // printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());

    std::cout<<"\nExiting..\n";
}
