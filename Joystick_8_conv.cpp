#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>   
//TODO: 3-byte struct 
class Joystick_8(){
    public:
        int x_axis =0;
        int y_axis = 0;
        int my_buttons = 0;

    void begin(std::string devname){
        
        std::ofstream devhandle; //should I make this public? Look function end uses it.
        devhandle.open (devname, ios::out | ios::binary);
        x_axis =0;
        y_axis = 0;
        my_buttons = 0;
        devhandle.write(); 
        
    };
    void end(){
        devhandle.close();
        x_axis =0;
        y_axis = 0;
        my_buttons = 0;
        devhandle.write();
    };
    void write(){
        devhandle.write();// there is no built in serialization in cpp
        //
    };
    void press(int button_number){
        my_buttons |= (1<<button_number);
        devhandle.write();
        
    };
    void release(int button_number){
        my_buttons &= ~(1<<button_number);
        devhandle.write();
        
    };
    void releaseAll(){
        my_buttons=0;
        devhandle.write();
    };   
    void buttons (int buttons){
        my_buttons = buttons;
        devhandle.write();
    };
    void xAxis(int position){
        x_axis = position;
        devhandle.write();
    }
    void yAxis (int position){
        y_axis = position;
        devhandle.write();
    }
    
}
