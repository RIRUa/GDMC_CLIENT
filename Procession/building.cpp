//
//  building.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/03/23.
//

#include "building.hpp"

void building::createHouse1(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction direction,
                            const WN::Vec3 &defaultPosi
                            ) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {30,30};
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // その位置が壁か角か判別するためのカウンター
    int wallCounter;
    
    /****/
    for (height = 0; height < 10; ++height) {
        /**　四方へのブロック配置処理　**/
        for (depth = 0; depth < size.depth; ++depth) {
            for (width = 0; width < size.width; ++width) {
                // カウンターを０に
                wallCounter = 0;
                
                if (depth <= 2) {
                    // 入口用ドアのスペースを開ける
                    if ((width == 15 || width == 16) && height < 3 ) {
                        continue;
                    }
                    wallCounter++;
                }
                if (width == 0) {
                    wallCounter++;
                }
                if (depth >= size.depth-1) {
                    wallCounter++;
                }
                if (width >= size.width-1) {
                    wallCounter++;
                }
                
                // ２階の床用
                if (height == 4 || height == 9) {
                    wallCounter == 0 ? wallCounter++: wallCounter;
                }
                
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;
                
                // 照明の追加
                if ( (height == 3 || height == 8) && posi.x%3 == 0 && posi.z%3 == 0) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
                }
                // 壁にブロックの挿入
                if (wallCounter == 2 && !(depth > 0 && depth <= 3)) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedBlackstoneBricks;
                } else if (wallCounter >= 1) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                }
                
            }
        }
    }
}

void building::createHouse2(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction direction,
                            const WN::Vec3 &defaultPosi
                            ) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {30,30};
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // その位置が壁か角か判別するためのカウンター
    int wallCounter;
    
    /****/
    for (height = 0; height < 10; ++height) {
        /**　四方へのブロック配置処理　**/
        for (depth = 0; depth < size.depth; ++depth) {
            for (width = 0; width < size.width; ++width) {
                // カウンターを０に
                wallCounter = 0;
                
                if (depth <= 2) {
                    // 入口用ドアのスペースを開ける
                    if ((width == 15 || width == 16) && height < 3 ) {
                        continue;
                    }
                    wallCounter++;
                }
                if (width == 0) {
                    wallCounter++;
                }
                if (depth >= size.depth-1) {
                    wallCounter++;
                }
                if (width >= size.width-1) {
                    wallCounter++;
                }
                
                // ２階の床用
                if (height == 4 || height == 9) {
                    wallCounter == 0 ? wallCounter++: wallCounter;
                }
                
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;
                
                // 照明の追加
                if ( (height == 3 || height == 8) && posi.x%3 == 0 && posi.z%3 == 0) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
                }
                // 壁にブロックの挿入
                if (wallCounter == 2 && !(depth > 0 && depth <= 3)) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedBlackstoneBricks;
                } else if (wallCounter >= 1) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                }
                
            }
        }
    }
}
