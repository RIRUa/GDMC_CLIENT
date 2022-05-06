//
//  interior.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/05/04.
//

#include "interior.hpp"


void interior::createHouse1(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size
                            ) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // 高さ用のデフォルト値
    const int heightDefault = defaultPosi.y + 1;
    
    // カウンター
    int counter;
    bool isStair = false;
    
    /**　階段の作成　**/
    for (height = 0; height < 5; ++height) {
        for (depth = 13; depth < 19; ++depth) {
            for (width = (size.width - 5); width < (size.width - 3); ++width) {
                
                counter = 0;
                isStair = false;
                
                if (height < 2) {
                    counter++;
                } else {
                    if (depth + height < 18) {
                        counter++;
                        if (depth + height == 17) {
                            isStair = true;
                        }
                    }
                }
                
                if (counter == 1) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;
                    
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                    
                    if (isStair) {
                        posi.z = depth + 1;
                        posi.x = width;
                        posi.rotation(facing);
                        posi.z += defaultPosi.z;
                        posi.x += defaultPosi.x;
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
                        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.front;
                    }
                }
                
            }
        }
    }
    
    height = 0;
    width = (size.width - 6);
    
    for (depth = 17; depth < 19; ++depth) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
        
        (*block3d)[heightDefault + height + 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
        (*block3d)[heightDefault + height + 1][posi.z][posi.x].angle = directions.right;
        
        posi.z = depth;
        posi.x = width - 1;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.right;
        
    }
    
    height = 3;
    width = (size.width - 7);
    depth = 18;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    
    
    // 玄関前の灯り
    height = 3;
    width = 15;
    depth = 9;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "hanging=true";
    
    height = 3;
    width = (size.width - 16);
    depth = 9;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "hanging=true";
    
}
