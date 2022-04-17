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
    
    const houseSize size = {40,40};
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // カウンター
    int counter;
    // ガラスを使うか
    bool isGlassBlock = false;
    
    /**　四方への塀の配置処理　**/
    for (depth = 0; depth < size.depth; ++depth) {
        for (width = 0; width < size.width; ++width) {
            counter = 0;
            if (depth == 0 && !((width >= size.width/2-1) && (width <= size.width/2))) {
                counter++;
            }
            if (width == 0) {
                counter++;
            }
            if (depth == (size.depth - 1)) {
                counter++;
            }
            if (width == (size.width - 1)) {
                counter++;
            }
            
            if (counter > 0) {
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;
                
                (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::prismarineWall;
            }
        }
    }
    
    /**　１階部分の作成　**/
    for (height = 0; height < 5; ++height) {
        for (depth = 7; depth < size.depth-15; ++depth) {
            for (width = 2; width < size.width-2; ++width) {
                // 玄関前の凹みを作成（一階の天井以下を凹ませる）
                if (height < 4 &&
                    (depth < 10 &&
                     (width > 14 &&
                      width < (size.width - 15)
                      )
                     )
                    ) {
                    continue;
                }
                
                // 階段用の穴
                if (height <= 4 &&
                    height >= 3 &&
                    width <= (size.width - 4) &&
                    width >= (size.width - 5) &&
                    depth <= 18 &&
                    depth >= 13
                    ) {
                    continue;
                }
                
                counter = 0;
                if (height == 4) {
                    counter++;
                }
                // 壁を作成
                if (depth == 7) {
                    counter++;
                }
                if (width == 2) {
                    counter++;
                }
                // TODO: 後で高さ制限をつける
                if (depth == (size.depth - 16)) {
                    if ((width >= size.width/2-1) && (width <= size.width/2)) {
                        if (height >= 2) {
                            counter++;
                        }
                        counter--;
                    }
                    counter++;
                }
                if (width == (size.width - 3)) {
                    counter++;
                }
                if (depth < 13) {
                    if (width <= 13 || width >= 26) {
                        counter--;
                    }
                    counter++;
                }
                if (depth == 12) {
                    if ((width >= 11 && width <= 12) ||
                        (width >= (size.width - 13) &&
                         width <= (size.width - 12))
                        ) {
                        if (height >= 2) {
                            counter++;
                        }
                        counter--;
                    }
                    counter++;
                }
                if (depth >= (size.depth - 21)) {
                    if (width != 15 && width != (size.width - 17)) {
                        counter--;
                    }
                    counter++;
                }
                if (depth == (size.depth - 21)) {
                    if (width > 12 && width < (size.width - 14)) {
                        if (height >= 2 &&
                            !(width >= 15 && width <= (size.width - 17))
                            ) {
                            counter++;
                        }
                        counter--;
                    }
                    counter++;
                }
                
                
                if (counter > 0) {
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                        
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                } else if (height == 3 && (width%3 == 0 && depth%3 == 0)) {
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "hanging=true";
                }
            }
        }
    }
    
    /**　２階部分の作成　**/
    for (; height < 10; ++height) {
        for (depth = 7; depth < size.depth-15; ++depth) {
            for (width = 2; width < size.width-2; ++width) {
                
                if (width < (size.width / 2) &&
                    width % 2 == 1 &&
                    depth > 7 &&
                    depth < (size.depth - 16) &&
                    height == 9) {
                    continue;
                }
                
                counter = 0;
                isGlassBlock = false;
                // 天井
                if (height == 9) {
                    counter++;
                }
                // 壁
                if (width == (size.width - 3)) {
                    counter++;
                }
                if (width > (size.width / 2) &&
                    depth == (size.depth - 16)
                    ) {
                    counter++;
                }
                if (width < (size.width - 3) &&
                    width > (size.width / 2) &&
                    (depth == 7 ||
                     depth == (size.depth - 16)
                    )&&
                    height < 9
                    ) {
                    counter++;
                    isGlassBlock = true;
                }
                if (width == (size.width / 2) &&
                    height < 9) {
                    counter++;
                    isGlassBlock = true;
                }
                // 柱
                if (width == 2 &&
                    (depth == 7 ||
                     depth == (size.depth - 16))
                    ) {
                    counter++;
                }
                
                
                if (counter > 0) {
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    
                    if (isGlassBlock) {
                        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                    } else {
                        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                    }
                }
                
            }
        }
    }
    
}
