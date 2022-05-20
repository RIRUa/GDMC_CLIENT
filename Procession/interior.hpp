//
//  interior.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/05/04.
//

#ifndef interior_hpp
#define interior_hpp

#include "../util/Minecraft.hpp"
#include "../util/Position.hpp"
#include "building.hpp"

namespace interior {
    void createHouse1(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                      const WN::Vec3 &center,
                      WN::direction facing,
                      const WN::Vec3 &defaultPosi,
                      const houseSize &size
                      );

    void createHouse2(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                      const WN::Vec3 &center,
                      WN::direction facing,
                      const WN::Vec3 &defaultPosi,
                      const houseSize &size
                      );

    void streetlight1(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                      const WN::Vec3 &center,
                      WN::direction facing,
                      const WN::Vec3 &defaultPosi,
                      const houseSize &size
                      );

    void streetlight2(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                      const WN::Vec3 &center,
                      WN::direction facing,
                      const WN::Vec3 &defaultPosi,
                      const houseSize &size
                      );

}

#endif /* interior_hpp */
