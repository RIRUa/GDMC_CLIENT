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

/***
 *
 *X = x*cos(D*pi/180) - y*sin(D*pi/180)
 *Y = x*sin(D*pi/180) + y*cos(D*pi/180)
 *
 **/





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

WN::direction& operator++(WN::direction &angle) {
    switch (angle) {
        case WN::direction::North:
            return angle = WN::direction::West;
            
        case WN::direction::West:
            return angle = WN::direction::South;
            
        case WN::direction::South:
            return angle = WN::direction::East;
            
        case WN::direction::East:
            return angle = WN::direction::North;
            
        case WN::direction::Up:
            return angle = WN::direction::Down;
            
        case WN::direction::Down:
            return angle = WN::direction::Up;
            
        default:
            return angle = WN::direction::North;
    }
}

WN::EveryDirection::EveryDirection() {
    this->front = std::make_shared<WN::direction>(WN::direction::North);
    this->right = std::make_shared<WN::direction>(WN::direction::East);
    this->left = std::make_shared<WN::direction>(WN::direction::West);
    this->behind = std::make_shared<WN::direction>(WN::direction::South);
}
