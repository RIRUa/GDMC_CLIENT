//
//  Position.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/25.
//

#include "Position.hpp"

WN::Vec3::Vec3() {
}

WN::Vec3::Vec3(position posx, position posy, position posz) {
    this->x = posx;
    this->y = posy;
    this->z = posz;
}

std::string WN::facingDirection(const direction &angle){
    
    switch (angle) {
        case WN::direction::North :
            return "north";
            
        case WN::direction::East:
            return "east";
            
        case WN::direction::West:
            return "west";
            
        case WN::direction::South:
            return "south";
            
        case WN::direction::Up:
            return "up";
            
        case WN::direction::Down:
            return "down";
            
        default:
            break;
    }
    
    return "";
}
