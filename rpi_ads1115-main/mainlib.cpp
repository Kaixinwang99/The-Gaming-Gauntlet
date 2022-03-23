#include "mainlib.h"
void mainlib::update_fingers(float flex_sensor[4]){
	if (flex_sensor[1]>5.0){
		fingers[0]=true;
	}
	else{
		fingers[0]=false;
	}
	if (flex_sensor[2]>5.0){
		fingers[1]=true;
	}
	else{
		fingers[1]=false;
	}
	if (flex_sensor[3]>6.0){
		fingers[2]=true;
	}
	else{
		fingers[2]=false;
	}
	if (flex_sensor[0]>5.0){
		fingers[3]=true;
	}
	else{
		fingers[3]=false;
	}
}
uint8_t mainlib::match_button(void){
	uint8_t button;
	std::array<bool,4> button0 {true,false,false,false};
	std::array<bool,4> button1 {false,true,false,false};
	std::array<bool,4> button2 {false,false,true,false};
	std::array<bool,4> button3 {false,false,false,true};
	std::array<bool,4> button4 {true,true,false,false};
	std::array<bool,4> button5 {true,false,true,true};
	std::array<bool,4> button6 {true,false,false,true};
	std::array<bool,4> button7 {true,true,true,true};
	if (fingers==button0) {
		button = 0;
	}
	else if (fingers==button1) {
		button = 1;
	}
	else if (fingers==button2) {
		button = 2;
	}
	else if (fingers==button3) {
		button = 3;
	}
	else if (fingers==button4) {
		button = 4;
	}
	else if (fingers==button5) {
		button = 5;
	}
	else if (fingers==button6) {
		button = 6;
	}
	else if (fingers==button7) {
		button = 7;
	}
	return button;
}
