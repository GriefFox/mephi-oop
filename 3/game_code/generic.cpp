#include "game_headers/generic.hpp"

namespace zasada{
    double calculate_distace(point from, point to){
        return std::sqrt(std::pow(to.x - from.x, 2) + std::pow(to.y - from.y, 2));
    }
}