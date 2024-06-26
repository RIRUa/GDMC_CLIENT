//
//  Position.h
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/20.
//

#ifndef Position_hpp
#define Position_hpp

#include <cmath>
#include <iostream>
#include <memory>

namespace WN {
    using position = long long int;

    /** 方角 **/
    enum class direction{
        North = 0,
        West = 90,
        South = 180,
        East = 270,
        Down = 1000,
        Up = 1500
    };

    /** ３次ベクトル **/
    struct Vec3 {
        position x;
        position y;
        position z;
        
        Vec3();
        Vec3(position posx, position posy, position posz);
        
        Vec3 rotation(direction facing);
    };

    
    direction& operator++(direction &angle);

    std::string facingDirection(const direction &angle);

    struct EveryDirection {
        std::shared_ptr<direction> front;
        std::shared_ptr<direction> left;
        std::shared_ptr<direction> right;
        std::shared_ptr<direction> behind;
        
        EveryDirection();
        EveryDirection(direction facing);
    };
}

#endif /* Position_hpp */
