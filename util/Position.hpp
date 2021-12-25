//
//  Position.h
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/20.
//

#ifndef Position_hpp
#define Position_hpp

namespace WN {
    using position = long long int;

    struct Vec3 {
        position x;
        position y;
        position z;
        
        Vec3();
        Vec3(position posx, position posy, position posz);
    };
}

#endif /* Position_hpp */
