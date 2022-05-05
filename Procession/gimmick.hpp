//
//  gimmick.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/03/18.
//

#ifndef gimmick_hpp
#define gimmick_hpp

#include "../util/Minecraft.hpp"
#include "../util/Position.hpp"

namespace gimmick {

    /**
     * @brief
     * 
     * @param block3d area that is written block infomations.
     * @param doorPosi door's left position when you see outside
     * @param angle building facing direction
     * @param blockType Door's material
     * @param defaultPosi
     * x:The position where writing started
     * y:The height at which the door is in block3d
     * z:The position where writing started
     */
    void automaticDoor(
                       std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                       int doorPosi,
                       WN::direction angle,
                       Minecraft::MinecraftBlock blockType,
                       WN::Vec3 defaultPosi
                       );



    void waterElevator(
                        std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                        int elePosi,
                        WN::direction angle,
                        Minecraft::MinecraftBlock blockType,
                        WN::Vec3 defaultPosi
                        );

}

#endif /* gimmick_hpp */
