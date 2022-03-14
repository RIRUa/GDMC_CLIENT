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

namespace WN {
    using position = long long int;

    struct Vec3 {
        position x;
        position y;
        position z;
        
        Vec3();
        Vec3(position posx, position posy, position posz);
    };

    enum class direction{
        North = 0,
        West = 90,
        South = 180,
        East = 270,
        Down = 1000,
        Up = 1500
    };

    direction& operator++(direction &angle);

    std::string facingDirection(const direction &angle);


}

#endif /* Position_hpp */
