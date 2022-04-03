#include "mainlib.h"
std::vector<uint8_t> mainlib::update_axis(float x, float y, float z){
    uint8_t coord_x;
    uint8_t coord_y;

    coord_x = int(x*255);
    coord_y = int(y*255);

    std::vector<uint8_t> coord {coord_x, coord_y};
    return coord;
}
void setAxis (std::uint8_t[1] coord){
    axis[2]={coord[0],coord[1]};
}
std::vector<uint8_t> getAxis (){
    return axis;
}
