//
//  building.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/03/23.
//

#ifndef building_hpp
#define building_hpp

#include "../util/Minecraft.hpp"
#include "../util/Position.hpp"

// 家の縦横のサイズを保存する構造体
struct houseSize {
    unsigned int width;
    unsigned int depth;
};

namespace building {
    void createHouse1(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                      const WN::Vec3 &center,
                      WN::direction direction,
                      const WN::Vec3 &defaultPosi
                      );

    void createHouse2(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                      const WN::Vec3 &center,
                      WN::direction direction,
                      const WN::Vec3 &defaultPosi
                      );
}

#endif /* building_hpp */
