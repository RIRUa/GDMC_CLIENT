//
//  Position.h
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/20.
//

#ifndef Position_hpp
#define Position_hpp

#include <cmath>

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
        East = 90,
        South = 180,
        West = 270
    };


}

#endif /* Position_hpp */
