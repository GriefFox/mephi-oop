#ifndef GENERIC_H
#define GENERIC_H

#include <string>
#include <cmath>

namespace zasada{
    enum weapon_t{
        def_weap = 0,
        light,
        heavy,
    };

    enum plane_t{
        def_plane = 0,
        fighter,
        storm_trooper,
    };
    
    struct capitan_info{
        std::string name;
        std::string rank;
    };
    struct point{
        double x;
        double y;

        point(double _x, double _y) : x(_x), y(_y){}; 
    };

    double calculate_distace(point from, point to);
} // namespace zasada


#endif