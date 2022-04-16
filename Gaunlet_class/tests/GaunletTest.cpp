#include <gtest/gtest.h>
#include <Gaunlet.h>

Gaunlet gg;

	float test_value[5]={-0.2,-0.25,0.08,0.11,0.16,0.2};
	bool right_value_Index[5] = {false,true,true,false,false};
	bool right_value_Thumb[5] = {false,true,false,false,false};
	bool right_value_Ring[5] = {false,true,true,false,false};
	bool right_value_Middle[5] = {false,true,false,false,false};
	
	TEST(BUTTONTEST, PRESS_AND_RELEASE_TEST)
	{	//Test Index finger
		for(uint8_t i=0; i<5; i++){
			gg.update_fingers({test_value[i],0,0,0});
			ASSERT_EQ(gg.fingers[1],right_value_Index[i]);
		}
		//Test Thumb finger
		for(uint8_t i=0; i<5; i++){
			gg.update_fingers({test_value[i],0,0});
			ASSERT_EQ(gg.fingers[1],right_value_Thumb[i]);
		}

		//Test Ring finger
		for(uint8_t i=0; i<5; i++){
			gg.update_fingers({0,0,{test_value[i],0});
			ASSERT_EQ(gg.fingers[1],right_value_Ring[i]);
		}

		//Test Middle finger
		for(uint8_t i=0; i<5; i++){
			gg.update_fingers({0,0,0,test_value[i]});
			ASSERT_EQ(gg.fingers[1],right_value_Middle[i]);
		}

	}
};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
