#include <iostream>
#include <algorithm>
#include "bmp.h"
#include "pgHelpers.hpp"

unsigned char rgbconv(double a){
    if(a > 255){
        return 255;
    }

    return a;
}

struct rgb{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    rgb(double red = 0, double green = 0, double blue = 0) : red(rgbconv(red)), green(rgbconv(green)), blue(rgbconv(blue)){}
};

rgb operator+(const rgb& lhs, const rgb& rhs){
    return rgb(lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue);
}

const int IMAGE_SIZE = 2000;
double max_long = -10000, min_long = 100000, max_lat = -100000, min_lat = 10000;

std::pair<int,int> convertLongLatToCoords(double longitude, double lat){
    double one_long = IMAGE_SIZE / (max_long - min_long);
    double one_lat = IMAGE_SIZE / (max_lat - min_lat);

    int x = (longitude - min_long) * one_long;
    int y = (lat - min_lat) * one_lat;
    return {x,y};
}

int main(int argc, char *argv[]){
    /*for(int x = 0; x < 250; x++){
        for(int y = 0; y < 125; y++){
            b.set_pixel(x, y, rgb(120,120,120));
        }
    }
    b.save_image("testfile.bmp");*/

    const std::string from = argv[1];
    const std::string to = argv[2];
    pgconn conn;
    auto m = conn.find_flights(from, to);
    std::cout << "found: " << m.size() << " flights" << std::endl;
    for(auto &entry : m){
        for(auto pos : entry.second.positions){
            max_long = std::max(max_long, pos.longitude);
            max_lat = std::max(max_lat, pos.latitude);
            min_long = std::min(min_long, pos.longitude);
            min_lat = std::min(min_lat, pos.latitude);
        }
    }
    std::cout << "max long: " << max_long << ", max_lat: " << max_lat << ", min long: " << min_long << ", min lat: " << min_lat << std::endl;

    bitmap_image b(2000, 2000);
    for(int x = 0; x < 2000; x++){
        for(int y = 0; y < 2000; y++){
            b.set_pixel(x, y, rgb(0,0,0));
        }
    }

    for(auto & entry : m){
        for(auto pos : entry.second.positions){
            auto pixelpos = convertLongLatToCoords(pos.longitude, pos.latitude);
            rgb r;
            for(int x = -5; x <= 5; x++){
                for(int y = -5; y <= 5; y++){
                    if(pixelpos.first + x < 0 || pixelpos.first + x >= IMAGE_SIZE || pixelpos.second + y < 0 || pixelpos.second + y >= IMAGE_SIZE){
                        continue;
                    }
                    int xx = pixelpos.first + x;
                    int yy = pixelpos.second + y;
                    b.get_pixel<rgb>(xx, yy, r);
                    b.set_pixel(xx, yy,  r + rgb(100,100,100));
                }
            }
        }
    }

    b.save_image(from + "_to_" + to + ".bmp");
}