#include <gtest/gtest.h>
#include <JoyLib.h>

JoyLib joy;


TEST(BUTTONTEST, PRESS_AND_RELEASE_TEST){
    for(uint8_t i=0;i<8;i++){
        joy.press(i+1);
        ASSERT_EQ((uint8_t)(1<<i),joy.get_buttons());
        joy.release(i+1);
        ASSERT_EQ((uint8_t)(0),joy.get_buttons());
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
