#include <stdint.h>
class mainlib{
	public:
		void update_axis(float x, float y, float z);
		/**
         * @brief 
         * turning the icm20948 output float xyz into int8_t x,y 
         * for the input of the joystick need to use porjection
         * @return void
         */
        void update_fingers(float flex_sensor[4]);
        /**
         * @brief 
         * turning rpi_ads1115 output into bool output for each finger
         * need to find the limit of bending value
         * @return void
         */
        uint8_t match_button(void);
        /**
         * @brief 
         * use bool fingers list to defind which button is being pressed
         * @return void
         */
	private:
		uint8_t axis[2]={0,0};
		/** unit x-axis, unit y-axit output for the joystick**/
		bool fingers[4]={false, false, false, false};
		/** record which finger is bending **/
	
};
