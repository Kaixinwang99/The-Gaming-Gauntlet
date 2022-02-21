#include <iostream>
#include <JoyLib.h>

int main(int, char**) {
    JoyLib joy;
    std::cout<<"\nPressing button 8"<<"\n";
    joy.press(8);
    printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());

    std::cout<<"\nReleasing button 8"<<"\n";
    joy.release(8);
    printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());


    std::cout<<"\nPressing buttons 1,2,3"<<"\n";
    joy.press(1);
    joy.press(2);
    joy.press(3);
    printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());

    std::cout<<"\nReleasing all buttons"<<"\n";
    joy.releaseAll();
    printf("[BUTTONS][HEX]:0x%02x\n",joy.get_buttons());

    std::cout<<"\nExiting..\n";
}
