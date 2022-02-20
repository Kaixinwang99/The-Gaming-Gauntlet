#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>   
//TODO: 3-byte struct 
class Joystick_8(){
    public:
        std::thread thread_lock();// what does this do? is this the same comand as in the py code?
        int x_axis =0; // should I put them to zero in public?
        int y_axis = 0;
        int my_buttons = 0;

    void begin(std::string devname){
        //there is no 'with' command in cpp
        std::ofstream devhandle; //should I make this public? Look function end uses it.
        devhandle.open (devname, ios::out | ios::binary);
        x_axis =0;
        y_axis = 0;
        my_buttons = 0;
        devhandle.write (); //What do I write here
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
        //Missing 'with'
    };
    void release(int button_number){
        my_buttons &= ~(1<<button_number);
        devhandle.write();
        //missing 'with'
    };
    void releaseAll(){
        my_buttons=0;
        devhandle.write();
    };   //missing 'with'
    void buttons (int buttons){
        my_buttons = buttons;
        devhandle.write(my_buttons);
    };
    void xAxis(int position){
        x_axis = position;
        devhandle.write(x_axis);
    }
    void yAxis (int position){
        y_axis = position;
        devhandle.write(y_axis);
    }
    
}