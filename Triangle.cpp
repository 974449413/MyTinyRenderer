#include"Triangle.h"

_TRIANGLE::_TRIANGLE(){
    for(auto it = vertex.begin(); it != vertex.end(); ++it){
        *it << 0,0,0;
    }
    for(auto it = color.begin(); it != color.end(); ++it){
        *it << 0,0,0;
    }
    for(auto it = normal_vector.begin(); it != normal_vector.end(); ++it){
        *it << 0,0,0;
    }
    for(auto it = uv_coordinate.begin(); it != uv_coordinate.end(); ++it){
        *it << 0,0,0;
    }
}