#include "Gaunlet.h"
#include <math.h>
void Gaunlet::setAxis(std::array<int8_t,2> input_axis){
	axis = input_axis;
}
std::array<int8_t,2> Gaunlet::getAxis(void){
	return axis;
}
void Gaunlet::update_axis(float x, float y, float z){
   	float n,nx,ny;
	n = 1/sqrt(x*x+y*y+z*z);
	nx=n*x+1;
	ny=n*y+1;
    	int8_t coord_x;
    	int8_t coord_y;
    	coord_x = nx*127-128;
    	coord_y = ny*127-128;
    	axis = {coord_x,coord_y};
}
void Gaunlet::update_fingers(float flex_sensor[4]){
	if (flex_sensor[0]<-0.2 && abs(flex_sensor[0])<1){
		fingers[1]=true;
	}
	else if(flex_sensor[0]>0.15 && abs(flex_sensor[0])<1)
	{
		fingers[1]=false;
	}
	if (flex_sensor[1]<-0.2 && abs(flex_sensor[1])<1){
		fingers[0]=true;
	}
	else if(flex_sensor[1]>0.05 && abs(flex_sensor[1])<1){
		fingers[0]=false;
	}
	if (flex_sensor[3]<-0.2 && abs(flex_sensor[3])<1){
		fingers[2]=true;
	}
	else if (flex_sensor[3]>0.15 && abs(flex_sensor[3])<1){
		fingers[2]=false;
	}
	if (flex_sensor[2]<-0.2 && abs(flex_sensor[2])<1){
		fingers[3]=true;
	}
	else if(flex_sensor[2]>0.1 && abs(flex_sensor[2])<1){
		fingers[3]=false;
	}
}

uint8_t Gaunlet::match_button(void){
	uint8_t button;
	std::array<bool,4> button1 {true,false,false,false};
	std::array<bool,4> button2 {false,true,false,false};
	std::array<bool,4> button3 {false,false,true,false};
	std::array<bool,4> button4 {false,false,false,true};
	std::array<bool,4> button5 {true,true,false,false};
	std::array<bool,4> button6 {true,false,true,true};
	std::array<bool,4> button7 {true,true,true,true};
	if (fingers==button1) {
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
	else{
		button = 8;
	}
	return button;
}
