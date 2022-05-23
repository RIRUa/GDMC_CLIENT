//
//  gimmick.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/03/18.
//

#ifndef gimmick_hpp
#define gimmick_hpp

#include <algorithm>

#include "../util/Minecraft.hpp"
#include "../util/Position.hpp"
#include "building.hpp"

namespace gimmick {

    void automaticDoor(std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                       const WN::Vec3 &center,
                       WN::direction facing,
                       const WN::Vec3 &defaultPosi,
                       const houseSize &size,
                       WN::Vec3 doorLeftPosi,
                       Minecraft::MinecraftBlock blockType
                       );

    void waterElevator(
                            std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            WN::Vec3 elePosi,
                            int elevatorHeight,
                            const std::vector< int > &floor
                            );

    void automaticWaterField(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            std::string &commands
                            );
}


#endif /* gimmick_hpp */
