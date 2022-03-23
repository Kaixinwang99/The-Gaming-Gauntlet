#ifndef _JOYLIB_H
#define _JOYLIB_H
#include <cstdint>
#include <iostream>
#include <fstream>

// Declare and include all the neccessary libs here 
/**
 * This class handles the button and joystick actions.
 * 
 */

class JoyLib {
    public:
        /**
         * @brief 
         * To open the file to which commands will be written
         * @param device 
         * @return true 
         * @return false 
         */
        bool begin(const char* device);
        /**
         * @brief 
         * Writes the command of the button pressed (3rd byte)
         * @param button 
         * @return true 
         * @return false 
         */
        bool press(int8_t button);
        /**
         * @brief 
         * Writes the command of the button beign released (3rd byte)
         * @param button 
         * @return true 
         * @return false 
         */
        bool release(int8_t button);
        /**
         * @brief 
         * Writes that all buttons have been released (3rd byte)
         * @return true 
         * @return false 
         */
        bool releaseAll();
        /**
         * @brief 
         * Writes the value of the X axis of the joystick between -127 and 127 (1st byte)
         * @param value 
         * @return true 
         * @return false 
         */
        bool xAxis(int8_t value);
        /**
         * @brief 
         * Writes the value of the Y axis of the Joystick between -127 and 127 (2nd byte)
         * @param value 
         * @return true 
         * @return false 
         */
        bool yAxis(int8_t value);
        /**
         * @brief Get the buttons object
         * 
         * @return uint8_t 
         */
        uint8_t get_buttons();
        /**
         * @brief Get the axis object
         * 
         * @return uint8_t 
         */
        uint16_t get_axis();
    private:
        std::ofstream fout;
        uint8_t out_bytes[3] = {0,0,0};
        /**
         * @brief 
         * Writes 3 bytes to the Interface file hidg0, 
         * where the first two bytes are the joystick position in X and Y and the third one the button pressed
         * @return true 
         * @return false 
         */
        bool write();


};

#endif
