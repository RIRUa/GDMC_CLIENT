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
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            const WN::Vec3 &sendPosition,
                            std::string &commands
                            ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // 高さ用のデフォルト値
    const int heightDefault = defaultPosi.y + 1;
    
    // カウンター
    int counter;
    // ガラスを使うか
    bool isGlassBlock = false;
    
    for (depth = 1; depth < size.depth - 1; ++depth) {
        for (width = 1; width < size.width - 1; ++width) {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            
            if (depth < size.depth - 15) {
                (*block3d)[defaultPosi.y - 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedBlackstoneBricks;
            }else {
                (*block3d)[defaultPosi.y - 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::grassBlock;
            }
            
        }
    }

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
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::prismarineWall;
            } else if (depth == 0 && (width >= size.width/2-1) && (width <= size.width/2)) {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;

                (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedFenceGate;
                (*block3d)[defaultPosi.y][posi.z][posi.x].angle = directions.front;

                posi.z = 1 + depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;

                (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedBlackstonePressurePlate;
            }
        }
    }

    /**　基礎の作成　**/
    for (depth = 7; depth < size.depth-15; ++depth) {
        for (width = 2; width < size.width-2; ++width) {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
        }
    }


    /**　玄関前の階段の作成　**/
    depth = 6;
    for (width = 15; width < (size.width - 15); ++width) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
        (*block3d)[defaultPosi.y][posi.z][posi.x].angle = directions.behind;
    }

    // ドアを入れるか
    bool isDoor = false;
    // ドアの種類
    Minecraft::MinecraftBlock doorType;
    // ドアの向き
    std::shared_ptr<WN::direction> doorFacing;
    // 蝶番の位置
    bool hinge = false;

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

                // 追加するブロックを決定するために初期化
                counter = 0;
                isGlassBlock = false;
                isDoor = false;

                if (height == 4) {
                    counter++;
                }
                // 壁を作成
                if (depth == 7) {
                    if (height >= 1 && height <=2) {
                        isGlassBlock = true;
                    }
                    counter++;
                }
                if (width == 2) {
                    if (height >= 1 && height <=2) {
                        isGlassBlock = true;
                    }
                    counter++;
                }
                if (depth == (size.depth - 16)) {
                    // 裏口の扉用のIF分
                    if ((width >= size.width/2-1) && (width <= size.width/2)) {
                        if (height >= 2) {
                            counter++;
                        }
                        isDoor = true;
                        doorType = Minecraft::MinecraftBlock::jungleDoor;
                        hinge = !hinge;
                        doorFacing = directions.front;

                        counter--;
                    }
                    if (height >= 1 && height <=2) {
                        isGlassBlock = true;
                    }
                    // サンルーム用
                    if (width > 2 && width < 15) {
                        counter--;
                    }

                    counter++;
                }
                if (width == (size.width - 3)) {
                    if (height >= 1 && height <=2) {
                        isGlassBlock = true;
                    }
                    counter++;
                }
                // 玄関前の凹みの作成
                if (depth < 13) {
                    if (width <= 13 || width >= 26) {
                        counter--;
                    }
                    counter++;
                }
                // 部屋割りの作成
                if (depth == 12) {
                    if ((width >= 11 && width <= 12) ||
                        (width >= (size.width - 13) &&
                         width <= (size.width - 12))
                        ) {
                        if (height >= 2) {
                            counter++;
                        }
                        isDoor = true;
                        doorType = Minecraft::MinecraftBlock::acaciaDoor;
                        hinge = !hinge;
                        doorFacing = directions.front;

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
                        if (width < 15 || width > (size.width - 17)) {
                            if (height >= 2) {
                                counter++;
                            } else {
                                isDoor = true;
                                doorType = Minecraft::MinecraftBlock::acaciaDoor;
                                hinge = !hinge;
                                doorFacing = directions.behind;
                            }
                        }
                        counter--;
                    }
                    counter++;
                }


                if (counter > 0) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    if (isGlassBlock && counter == 1) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                    }
                } else if (height == 3 && (width%3 == 0 && depth%3 == 0)) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
                    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "hanging=true";
                } else if (isDoor) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    (*block3d)[heightDefault + height][posi.z][posi.x].block = doorType;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = doorFacing;
                    if (height == 1) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition = "half=upper";
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition = "half=lower";
                    }

                    if (hinge ^
                        !(doorFacing == directions.front ||
                         doorFacing == directions.right)
                        ) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition += ",hinge=left";
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition += ",hinge=right";
                    }
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
                isDoor = false;
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

                    if (depth >= 10 && depth <= 11 && height < 7) {
                        counter = 0;
                        isDoor = true;
                        doorType = Minecraft::MinecraftBlock::acaciaDoor;
                        hinge = !hinge;
                        doorFacing = directions.right;
                    } else {
                        isGlassBlock = true;
                    }
                }
                // 柱
                if (width == 2 &&
                    (depth == 7 ||
                     depth == (size.depth - 16))
                    ) {
                    counter++;
                }


                if (counter > 0) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    if (isGlassBlock) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                    } else {
                        if (height == 9 &&
                            (width%3 == 0 && depth%3 == 0)
                            ) {
                            (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;
                        } else {
                            (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                        }
                    }
                } else if (isDoor) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    (*block3d)[heightDefault + height][posi.z][posi.x].block = doorType;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = doorFacing;
                    if (height == 6) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition = "half=upper";
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition = "half=lower";
                    }

                    if (hinge) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition += ",hinge=left";
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition += ",hinge=right";
                    }
                }

            }
        }
    }

    /**　サンルームの作成　**/
    for (height = 0; height < 6; ++height) {
        for (depth = size.depth-15; depth < size.depth-10; ++depth) {
            for (width = 2; width < 16; ++width) {
                // ブロックを置くカウンターの初期化
                counter = 0;

                // サンルームの壁の作成
                if (width == 2) {
                    counter++;
                }
                if (width == 15) {
                    counter++;
                }
                if (depth == size.depth-15) {
                    counter++;
                }
                if (depth == size.depth-11) {
                    counter++;
                }
                if (height == 0) {
                    counter += 2;
                }
                if (height == 5) {
                    counter++;
                }


                if (counter == 1 && depth != size.depth-15) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                } else if (counter >= 2) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;
                    
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                }

            }
        }
    }
    
    // 地下１階を作成
    bool isUseBookshelf;
    for (height = -5; height < -2; ++height) {
        for (depth = size.depth / 2 - 6; depth < size.depth/2 - 1; ++depth) {
            for (width = size.width / 2 - 2; width < size.width / 2 + 3; ++width) {
                
                counter = 0;
                isUseBookshelf = false;
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                if (depth == size.depth / 2 - 6) {
                    counter++;
                    
                    if (height >= -5 && height <= -4 && width < size.width / 2 + 2) {
                        isUseBookshelf = true;
                    }
                }
                
                if (depth == size.depth/2 - 2) {
                    counter++;
                    
                    if (height >= -5 && height <= -4 && width < size.width / 2 + 2) {
                        isUseBookshelf = true;
                    }
                }
                
                if (width == size.width / 2 - 2) {
                    counter++;
                    
                    if (height >= -5 && height <= -4) {
                        isUseBookshelf = true;
                    }
                }
                
                if (counter == 0) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
                } else if (counter == 1) {
                    
                    if (isUseBookshelf) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::bookshelf;
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::blueGlazedTerracotta;
                        (*block3d)[heightDefault + height][posi.z][posi.x].angle = Minecraft::glazedTerracottaFacing(width, depth, height);
                    }
                }
            }
        }
    }
    
    height = -5;
    depth = size.depth / 2 - 4;
    width = size.width / 2;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::enchantingTable;
    
    for (height = -6; height < -2; ++height) {
        for (depth = size.depth / 2 - 5; depth < size.depth / 2 - 2; ++depth) {
            for (width = size.width / 2 + 3; width < size.width - 4; ++width) {
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                if (depth == size.depth / 2 - 4
                    && height == -6
                    ) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;
                    
                }else if (depth == size.depth / 2 - 4
                          && height >= -5
                          && height <= -4
                          ) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = nullptr;
                } else {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::blueGlazedTerracotta;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = Minecraft::glazedTerracottaFacing(width, depth, height);
                }
                
            }
        }
    }
    
    for (height = -6; height < -2; ++height) {
        for (width = size.width - 6; width < size.width - 3; ++width) {
            for (depth = size.depth / 2 - 7; depth < size.depth / 2 - 3; ++depth) {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                if (height == -6) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = nullptr;
                } else if (width == size.width - 5
                    && height >= -5
                    && height <= -4
                    ) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = nullptr;
                } else if (depth != size.depth / 2 - 4
                           || width != size.width - 6
                           ){
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::blueGlazedTerracotta;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = Minecraft::glazedTerracottaFacing(width, depth, height);
                }
                
            }
        }
    }
    
    height = -4;
    width = size.width - 5;
    depth = size.depth / 2 - 7;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakWallSign;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.behind;

    // TODO: ２階に鉄格子

}

void building::createHouse2(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            const WN::Vec3 &sendPosition,
                            std::string &commands
                            ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    int i;
    
    // その位置が壁か角か判別するためのカウンター
    int wallCounter;
    
    /****/
    for (height = 0; height < 5; ++height) {
        /**　四方へのブロック配置処理　**/
        for (depth = 5; depth < 36; ++depth) {
            for (width = 5; width < 36; ++width) {
                // カウンターを０に
                wallCounter = 0;
                
                if (depth <= 5 ){
                     // 入口用ドアのスペースを開ける
                    if ((width == 20 || width == 21) && height < 3 ) {
                        continue;
                    } 
                    wallCounter++;
                }

                if (width == 5) {
                    wallCounter++;
                }
                if (depth >= 35) {
                    wallCounter++;
                }
                if (width >= 35) {
                    wallCounter++;
                }
                
                // ２階の床用
                if (height == 4 || height == 9) {
                    wallCounter == 0 ? wallCounter++: wallCounter;
                }
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                
                // 壁にブロックの挿入
                if (wallCounter == 2 && !(depth > 5 && depth <= 8)) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }else if (wallCounter >= 1) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
                
            }
        }
    }

//一階の部屋分け
    width = 24;
    for(height = 0; height < 5; ++height){
        for(depth  = 6; depth  < 8; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;    
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(height = 2; height < 5; ++height){
        for(depth  = 8; depth  < 10; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;    
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height = 0; depth = 8; 
    for(i = 0; i < 2; i++){
        if(i == 0){
            posi.z = depth + i;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;    
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = lower";
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition += ",hinge = right";

            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].angle = directions.left;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition = "half = upper";
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition += ",hinge = right";
        } else {
            posi.z = depth + i;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = lower";
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition += ",hinge = left";

            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].angle = directions.left;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition = "half = upper";
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition += ",hinge = left";
        }
    }

    for(height = 0; height < 5; ++height){
        for(depth  = 10; depth  < 33; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;    
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(height = 2; height < 5; ++height){
        for(depth  = 33; depth  < 35; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;    
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height = 0; depth = 33;
    for(int i = 0; i < 2; i++){
        if(i == 0){
            posi.z = depth +i;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;    
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = lower";
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition += ",hinge = left";

            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].angle = directions.right;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition = "half = upper";
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition += ",hinge = left";
        } else {
            posi.z = depth + i;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = lower";
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition += ",hinge = right";

            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakDoor;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].angle = directions.right;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition = "half = upper";
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition += ",hinge = right";
        }
    }

    depth = 20;
    for(height = 0; height < 5; ++height){
        for(width  = 5; width  < 24; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;    
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

//warped_fence
    height = 0; depth = 0;
    for (width = 0; width < size.width +1; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedFence;
        if(width == 20 || width == 21){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

    height = 0; depth = 39;
    for(width = 0; width < size.width ; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedFence;
        
        }

    height = 0; width = 40;
    for(depth = 0; depth < size.depth ; ++depth){

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;    

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedFence;
        }
    
    height = 0; width = 0;
    for(depth = 0; depth < size.depth ; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedFence;
        }


//floor
    height = -1;
    for(width = 20; width < 22; ++width){
        for(depth = 0; depth < 6; ++depth){ 
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(width = 5; width < size.width -4; ++width){
        for(depth = 6; depth < size.depth -5; ++depth){ 
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

//floor stairs

    for (width = 20; width < 22; ++width){
        for (i = 0; i < 5; ++i){
            height = 4 - i; depth = 9 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for (width = 6; width < 8; ++width){
        for (i = 0; i < 5; ++i){
            height = 4 - i; depth = 9 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

// second floor
    for(width = 22; width < size.width -4; ++width){
        for(height = 5; height < 10; ++height){
            for(depth = 5; depth < size.depth -4; ++depth){
                if(depth == 5 || depth == 35){
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
            }
        }
    }

    for(height = 5; height < 10; ++height){
        for(depth = 5; depth < size.depth -4; ++depth){
            for(width = 22; width < size.width -4; ++width){
                if(width == 22 || width == 35){
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;

                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
            }
        }
    }   

    height = 10;
    for(depth = 5; depth < size.depth -4; ++depth){
        for(width = 22; width < size.width -4; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    } 

    for(width = 5; width < 22; ++width){
        for(height = 5; height < 11; ++height){
            for(depth = 15; depth < size.depth -4; ++depth){
                if(depth == 15 || depth == 35){
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
            }
        }
    }

    width = 5;
    for(height = 5; height < 10; ++height){
        for(depth = 16; depth < size.depth -5; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    height = 10;
    for(width = 5; width < 22; ++width){
        for(depth = 16; depth < size.depth -5; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

// root to go up second floor
    height = 4; 
    for(width = 5; width < size.width -5; ++width){
        for(depth = 10; depth < 15; ++depth){
            if( width == 21 || width == 20 || width == 7 || width == 6){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            }
        }
    }

//second floor entry
    width = 22;
    for(depth = 7; depth < 9; ++depth){
        for (height = 5; height < 8; ++height){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

    width = 22;
    for(depth = 29; depth < size.depth -9; ++depth){
        for (height = 5; height < 8; ++height){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

//second floor pool
    height = 5; depth = 27;
    for (width = 9; width < 22; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    height = 5; width = 9;
    for (depth = 15; depth < 27; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    height = 5;
    for (width = 10; width < 22; ++width){
        for (depth = 16; depth < 27; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
        }
    }


//third floor
    for(width = 25; width < size.width -7; ++width){
        for(height = 11; height < 16; ++height){
            depth = 8;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;

            depth = 32;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(depth = 8; depth < size.depth -8; ++depth){
        for(height = 11; height < 16; ++height){
            width = 25;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            
            width = 32;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height =16;
    for(width = 25; width < size.width -7; ++width){
        for(depth = 8; depth < size.depth -7; ++depth){ 
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

//third floor roof
    for(depth = 11; depth < size.depth -9; ++depth){
        for(i = 0; i < 4; i++){
            width = 25 + i; height = 16 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(depth = 11; depth < 30; ++depth){
        for(i = 0; i < 4; i++){
            width = 29 + i; height = 19 - i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height = 17;
    for(depth = 30; depth < size.depth -8; ++depth){
        for(width = 26; width < size.width -8; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height = 18;
    for(depth = 30; depth < size.depth -9; ++depth){
        for(width = 27; width < size.width -9; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height = 17;
    for(depth = 9; depth < 11; ++depth){
        for(width = 26; width < size.width -8; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height = 18;
    for(depth = 10; depth < 11; ++depth){
        for(width = 27; width < size.width-9; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

//third floor stair roof
    for(depth = 11; depth < 30; ++depth){
        for(i = 0; i < 5; i++){
            width = 24 + i; height = 16 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        }
    }

    for(depth = 11; depth < 30; ++depth){
        for(i = 0; i < 5; i++){
            width = 29 + i; height = 20 - i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }

    for(width = 28; width < 30; ++width){
        for(i = 0; i < 5; i++){
            depth = 7 + i; height = 16 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
        }
    }

    for(width = 28; width < 30; ++width){
        for(i = 0; i < 5; i++){
            depth = 29 + i; height = 20 - i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    for(width = 25; width < 28; ++width){
        for(i = 0; i < 2; i++){
            height = 16 + i; depth = 7 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
        }
    }

    for(width = 30; width < size.width -7; ++width){
        for(i = 0; i < 2; i++){
            height = 16 + i; depth = 7 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
        }
    }

    for(width = 25; width < 28; ++width){
        for(i = 0; i < 2; i++){
            height = 17 - i; depth = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    for(width = 30; width < size.width-7; ++width){
        for(i = 0; i < 2; i++){
            height = 17 - i; depth = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    for(depth = 30; depth < size.depth -7; ++depth){
        for(i = 0; i < 2; i++){
            height = 17 - i; width = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }

    for(depth = 8; depth < 11; ++depth){
        for(i = 0; i < 2; i++){
            height = 17 - i; width = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }
    
    for(depth = 29; depth < size.depth -7; ++depth){
        for(i = 0; i < 2; i++){
            height = 16 + i; width = 24 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        }
    }

    for(depth = 8; depth < 11; ++depth){
        for(i = 0; i < 2; i++){
            height = 16 + i; width = 24 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        }
    }

    height = 16; width = 24; depth = 7; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    width = 33;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    depth = 33;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    width = 24;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    width = 26; height = 18; depth = 9;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    depth = 10; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    depth = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    depth = 31;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    width = 31; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    depth = 30; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    depth = 10;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    depth = 9;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    width = 27; height = 18;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    height = 19; depth = 10;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    depth = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    depth = 31; height = 18;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    width = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    height = 19; depth = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    depth = 10;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    depth = 9; height = 18;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;


//third floor entry
    width = 25;
    for(depth = 29; depth < size.depth -9; ++depth){
        for (height = 11; height < 14; ++height){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

//second floor stairs
    for(width = 9; width < 19; ++width){
        if(width == 9 || width == 18){
            depth = 9; height = 5;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }   
        
        for(depth = 10; depth < 15; ++depth){
            height = 5;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            if(width == 9 || width == 18){
                height = 6;
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }   
        }

        for(depth = 11; depth < 15; ++depth){
            height = 6;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            if(width == 9 || width == 18){
                height = 7;
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }   
        }

        for(depth = 12; depth < 15; ++depth){
            height = 7;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            if(width == 9 || width == 18){
                height = 8;
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }   
        }

        for(depth = 13; depth < 15; ++depth){
            height = 8;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            if(width == 9|| width == 18){
                height = 9;
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }   
        }

        for(depth = 14; depth < 15; ++depth){
            height = 9;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            if(width == 9 || width == 18){
                height = 10;
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }   
        }
    }
}

void building::createAutomaticWaterField(
                                         std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                                         const WN::Vec3 &center,
                                         WN::direction facing,
                                         const WN::Vec3 &defaultPosi,
                                         const houseSize &size,
                                         const WN::Vec3 &sendPosition,
                                         std::string &commands
                                         ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    int i;

    //空気
    height = -1; depth = 2;
    for(width = 2; width < size.width -2; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    }

    height = -1; depth = 1;
    for(width = 10; width < size.width -1; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    } 

    //ホッパー
    height = -2; depth = 2; width = size.width -3;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::hopper;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;


    //チェスト
    height = -2; depth =1;
    for(width = 10; width < size.width -1; ++width){
        if(width == size.width -3){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = left";
        } else {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = right";
        }
    } 

    //囲いクォーツ
    height = -1; depth = 0;
    for(width = 0; width < size.width; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }


    height = -1; width = 1;
    for(depth = 2; depth < size.depth; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    height = 1; width = size.width -2;
    for(depth = size.width -2 ; depth < size.depth -1; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    width = size.width -2; height = 0;
    for(depth = 2; depth < 11; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }
    
    height = -1; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;


    height = -1; depth = 1;
    for(width = 1; width < size.width -3; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    height = -1; depth = size.depth -1;
    for(width = 1; width < size.width -1; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    //ボタン
    width = size.width-2; height = -1; depth = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stoneButton;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    //トラップドア
    width = 6; height = 0; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::spruceTrapdoor;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    //土
    height = -1;
    for(depth = 3; depth < 11; ++depth){
        for(width = 2; width < size.width -2; ++width){
            if(width == 6){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                } else {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::farmland;
            }
        }
    }

    height = 0;
    for(depth = 11; depth < size.depth -3; ++depth){
        for(width = 2; width < size.width-2; ++width){
            if(width == 6){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                } else {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::farmland;
            }
        }
    }

    //階段
    width = 6; depth = 10; height = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;


    width = 6; depth = size.depth-4; height = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    //上段クォーツ
    height = 1; 
    for(depth = 17; depth < size.depth-1; ++depth){
        for(width = 2; width < size.width-2; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }   

    height = 0; depth = size.depth-3;
    for(width = 2; width < size.width-2; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    width = 6; depth = size.depth-2; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;

    depth = size.depth-1; 
    for(height = 0; height < 2; ++height){
        for(width = 1; width < size.width-1; ++width){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    //右壁
    for(width = 0; width < 2; ++width){
        for(height = 0; height < 3; ++height){
            for(depth = 1; depth < size.depth; ++depth){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }
        }
    }

    //左壁
    width = size.width-2; height = 1; 
    for(depth = 2; depth < size.width-2; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    width = size.width-1;
    for(height = -1; height < 2; ++height){
        for(depth = 1; depth < size.depth; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    height = 2; 
    for(width = size.width-2; width < size.width; ++width){
        for(depth = 1; depth < size.depth; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

//水
    height = -1; depth = 2; width = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;

    height = -1; depth = size.depth-3;
    for(width = 2; width < size.width-3; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
    }

    height = 0; width = 1; 
    for(depth = 11; depth < size.depth -2; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
    }

    height = 0; depth = size.depth -3; 
    for(width = 2; width < 6; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
    }

    height = 0; depth = size.depth -4; width = 6;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;

    //ハーフブロック
    height = 2; depth = size.depth -1; 
    for(width = 2; width < size.width -2; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickSlab;
    }

    //ネザーブロック
    width = 6;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBricks;

    //ハーフブロック
    width = 2;
    for(depth = 17; depth < size.depth -1; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickSlab;
    }

    width = 10;
    for(depth = 17; depth < size.depth -1; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickSlab;
    }

    height = 2; depth = size.depth -3; 
    for(width = 4; width < 9; ++width){
        if(width == 6){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            } else {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickSlab;
        }
    }
    
    width = size.width - 3; height = -1; depth = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type=top";

    width = 1; height = 0; depth = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    // コマンド作成
    WN::Vec3 chestPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
    
    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                       chestPosi.x + sendPosition.x,
                                                       chestPosi.y + sendPosition.y,
                                                       chestPosi.z + sendPosition.z
                                                       ),
                                              0,
                                              "minecraft:netherite_hoe",
                                              1
                                              );
    
    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                       chestPosi.x + sendPosition.x,
                                                       chestPosi.y + sendPosition.y,
                                                       chestPosi.z + sendPosition.z
                                                       ),
                                              1,
                                              "minecraft:diamond_hoe",
                                              1
                                              );
    
    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                       chestPosi.x + sendPosition.x,
                                                       chestPosi.y + sendPosition.y,
                                                       chestPosi.z + sendPosition.z
                                                       ),
                                              2,
                                              "minecraft:wheat_seeds",
                                              64
                                              );

    //明かりの追加
    height = 3; 
    for(i=0; i < 13;i += 12){
        for(depth = 1; depth < 20; depth += 6){
            posi.z = depth;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jackOLantern;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    width = 6; depth = 19;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jackOLantern;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    height = -1; depth = 6;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;

    height = 0; depth = size.depth - 7;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
}

void building::createFountain(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            std::string &commands
                            ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;

    //土台
    const double PI = std::acos(-1.0);
    double sita = 0.0;
    int radius = 0;
    
    constexpr int baseRadius = 26;

    height = -1;
    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 2) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    //一段目
    height = 0;
    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = (baseRadius / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 2) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }


    //真ん中
    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 16) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }


    //二段目ハーフブロック
    height = 1;
    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = (baseRadius / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedDioriteSlab;
        }
    }


    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 2) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }


    //二層目　クォーツブロック
    height = 7;

    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 8) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 10) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

    for (int i = -8; i < 9; i += 16) {
        posi.x = i;
        posi.z = 0;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
        posi.x = 0;
        posi.z = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
    }


    //二層目　二段目ハーフブロック
    height = 8;
    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 8) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedDioriteSlab;
        }
    }

    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 10) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

    //二層目　二段目クォーツブロック
    height = 6;
    for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 10) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }
    
    height = 6;
    for (int i = -5; i < 6; i += 10) {
        posi.x = i;
        posi.z = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
        posi.x = i;
        posi.z = -i;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
    }

    height = 7;
    for (int i = -3; i < 4; i += 6) {
        posi.x = i;
        posi.z = 0;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
        
        posi.x = 0;
        posi.z = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
        
    }

    for (int i = -5; i < 6; i += 10) {
        posi.x = i;
        posi.z = 0;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;
        
        posi.x = 0;
        posi.z = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;
        
    }

   //3層目　クォーツブロック
    height = 14;
   for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 14) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }


   for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
       for (radius = ((baseRadius -16) / 2 - 1); radius >= 0; radius -= 1) {
           posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
           posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
           posi.rotation(facing);
           posi.z += defaultPosi.z + size.depth/2;
           posi.x += defaultPosi.x + size.width/2;
           (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
       }
   }

    width =0; depth = 5; height = 14;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;

    width = 0; depth =-5;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;

    width = -5; depth =0;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;

    width = 5; depth = 0;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;

   //3層目　二段目ハーフブロック
    height = 15;
   for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
        for (radius = ((baseRadius - 14) / 2 - 1); radius >= 0; radius -= 1) {
            posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
            posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
            posi.rotation(facing);
            posi.z += defaultPosi.z +size.depth/2;
            posi.x += defaultPosi.x +size.width/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedDioriteSlab;
        }
    }

   for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
       for (radius = ((baseRadius - 16)/ 2 - 1); radius >= 0; radius -= 1) {
           posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
           posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
           posi.rotation(facing);
           posi.z += defaultPosi.z +size.depth/2;
           posi.x += defaultPosi.x +size.width/2;
           (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
       }
   }


   //3層目　二段目クォーツブロック
   height = 13;
   for (sita = 0.0; sita < 2 * PI; sita += (PI/100)) {
       for (radius = ((baseRadius - 16) / 2 - 1); radius >= 0; radius -= 1) {
           posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
           posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
           posi.rotation(facing);
           posi.z += defaultPosi.z + size.depth/2;
           posi.x += defaultPosi.x + size.width/2;
           (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
       }
   }

   for (int i = -4; i < 5; i += 8) {
        posi.x = i;
        posi.z = 2;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
        posi.x = i;
        posi.z = -2;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
    }

    for (int i = -4; i < 5; i += 8) {
        posi.x = 2;
        posi.z = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
        posi.x = -2;
        posi.z = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.width/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
    }

    width =2; depth = -2; height = 13;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = 2; depth =2;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = -2; depth =2;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = -2; depth = -2;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

///
   //土台の柱作成；一層目
    for(height = 1; height < 7; ++height){
        for(width =1; width < 3; ++width){
            for(depth =1; depth < 3; ++depth){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z + size.depth/2;
                posi.x += defaultPosi.x + size.depth/2;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }
        }
    }

    for(height = 1; height < 7; ++height){
        for(width =-2; width < 0; ++width){
            for(depth =1; depth < 3; ++depth){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z + size.depth/2;
                posi.x += defaultPosi.x + size.depth/2;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }
        } 
    }

    for(height = 1; height < 7; ++height){
        for(width =1; width < 3; ++width){
            for(depth =-2; depth < 0; ++depth){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z + size.depth/2;
                posi.x += defaultPosi.x + size.depth/2;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }
        }
    }

    for(height = 1; height < 7; ++height){
        for(width =-2; width < 0; ++width){
            for(depth =-2; depth < 0; ++depth){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z + size.depth/2;
                posi.x += defaultPosi.x + size.depth/2;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
            }
        }
    }

   //土台の階段作成；一層目
    height = 1; depth = -3;
    for(width = -2; width < 3; ++width){
        if(width == 0 || width == -3){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            } else {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
        }
    }

   //土台のライト
    height = 0; width =6; depth = -6;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    height = 1;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endRod;

    height = 2;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedDioriteSlab;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "waterlogged = true";


    height = 0;width = -6; depth = -6;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    height = 1;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endRod;

    height = 2;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedDioriteSlab;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "waterlogged = true";

    height = 0;width = -6; depth = 6;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    height = 1;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endRod;

    height = 2;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedDioriteSlab;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "waterlogged = true";

    height = 0;width = 6; depth = 6;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    height = 1;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endRod;

    height = 2;
    posi.x = width;
    posi.z = depth;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedDioriteSlab;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "waterlogged = true";

    height = 1; depth = 3;
    for(width = -2; width < 3; ++width){
        if(width == 0 || width == -3){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            } else {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    height = 1; width = -3;
    for(depth = -2; depth < 3; ++depth){
        if(depth == 0 || depth == -3){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            } else {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        }
    }

    height = 1; width = 3;
    for(depth = -3; depth < 3; ++depth){
        if(depth == 0 || depth == -3){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            } else {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }

   //土台；2層目
    height = 7;
    for(width = -1; width < 2; ++width){
        for(depth = -1; depth < 2; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z + size.depth/2;
            posi.x += defaultPosi.x + size.depth/2;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

   //土台２層目;柱
   //柵
    width = 1; depth = 1;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glassPane;
    }

    width = -1; depth = 1;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glassPane;
    }

    width = 1; depth = -1;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glassPane;
    }

    width = -1; depth = -1;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glassPane;
    }

   //ガラス
    depth = -1; width = 0;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
    }

    depth = 1; width = 0;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
    }

    depth = 0; width = 1;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
    }

    depth = 0; width = -1;
    for(height = 8; height < 13; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
    }

   //3層目;柱
    width = 1; depth = 1;
    for(height = 13; height < 18; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    width = -1; depth = 1;
    for(height = 13; height < 18; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    width = 1; depth = -1;
    for(height = 13; height < 18; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    width = -1; depth = -1;
    for(height = 13; height < 18; ++height){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

   //3層目;仕上げハーフブロックと階段
   //階段
    height =19;
    for(width = -2; width < 3; ++width){
        for(depth = -2; depth < 3; ++depth){
            if(depth == 0 && width == 0){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z + size.depth/2;
                posi.x += defaultPosi.x + size.depth/2;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
                } else {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z + size.depth/2;
                posi.x += defaultPosi.x + size.depth/2;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
            }
        }
    }

   //シーランタン
    height = 19; width = 2; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = -2; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = 2; depth = -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = -2; depth = -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    height = 18; width = 2; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = -2; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = 2; depth = -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

    width = -2; depth = -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;

   //ハーフブロックと逆階段と中段階段2と最上階の逆階段
    height = 18; width = 0; depth = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    height = 19;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    height = 21;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    height = 23;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    height = 18; width = 0; depth = -1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    height = 19;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
    height = 21;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
    height = 23;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    height = 18; width = 1; depth = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    height = 19;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
    height = 21;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
    height = 23;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    height = 18; width = -1; depth = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    height = 19;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    height = 21;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    height = 23;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half = top";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;


   //中段階段と最上階ハーフブロック
    height = 20;
    width = 0; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    height = 24;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;

    height = 20;
    width = 0; depth = -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
    height = 24;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;

    height = 20;
    width = 2; depth = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
    height = 24;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;

    height = 20;
    width = -2; depth = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    height = 24;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;

   //中段ハーフブロック
    height = 20;
    width = -1; depth = -3;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    depth = 3;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    width = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    depth = -3;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;

    width = -3; depth = -1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    depth = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    width = 3;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
    depth = -1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
}

void building::createPigBurner(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                               const WN::Vec3 &center,
                               WN::direction facing,
                               const WN::Vec3 &defaultPosi,
                               const houseSize &size,
                               const WN::Vec3 &sendPosition,
                               std::string &commands
                               ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    int i, j;
    
    // 端を検出
    int edgeCounter = 0;
    // ディスペンサーを使うか（２以上なら使う）
    int isDispense = 0;
    
    for (height = 1; height < 6; ++height) {
        for (depth = 4; depth < (size.depth - 4); ++depth) {
            for (width = 4; width < (size.width - 4); ++width) {
                
                // 豚を落とす穴
                if (width == 5 && depth == 5) {
                    continue;
                }
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                
            }
        }
    }
    
    for (height = 5; height < 10; ++height) {
        for (depth = 0; depth < size.depth; ++depth) {
            for (width = 0; width < size.width; ++width) {
                // 豚の落ちる穴
                if (width == ((size.width - 1) / 2) && depth == ((size.depth - 1) / 2)) {
                    continue;
                }
                
                edgeCounter = 0;
                isDispense = false;
                
                if (width == 0) {
                    edgeCounter++;
                }
                if (depth == 0) {
                    edgeCounter++;
                }
                if (width == (size.width - 1)) {
                    edgeCounter++;
                }
                if (depth == (size.depth - 1)) {
                    edgeCounter++;
                }
                
                if (height == 7) {
                    if (width == 1) {
                        isDispense++;
                    }
                    if (depth == 1) {
                        isDispense++;
                    }
                    if (width == (size.width - 2)) {
                        isDispense++;
                    }
                    if (depth == (size.depth - 2)) {
                        isDispense++;
                    }
                }
                
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                if (height == 6) {
                    
                    if (width % 2 == depth % 2) {
                        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::diamondBlock;
                    } else {
                        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::goldBlock;
                    }
                    
                } else if (height == 7) {
                    
                    if (isDispense >= 2) {
                        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
                        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared<WN::direction>(WN::direction::Up);
                        // コマンド作成
                        WN::Vec3 dispensorPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
                        commands += Minecraft::Command::itemInBox(
                                                                  WN::Vec3(
                                                                           dispensorPosi.x + sendPosition.x,
                                                                           dispensorPosi.y + sendPosition.y,
                                                                           dispensorPosi.z + sendPosition.z
                                                                           ),
                                                                  4,
                                                                  "minecraft:water_bucket",
                                                                  1
                                                                  );
                    } else {
                        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::grassBlock;
                    }
                    
                } else if (height >= 8 && edgeCounter > 0) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                }
                
            }
        }
    }
    
    // スポナーの設置
    height = 9;
    constexpr int spawnerPosi = 3;
    
    for (i = -1; i < 2; i += 2) {
        for (j = -1; j < 2; j += 2) {
            width = ((size.width - 1) / 2 + i * spawnerPosi);
            depth = ((size.depth - 1) / 2 + j * spawnerPosi);
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::spawner;
        }
    }
    
    // ホッパーの設置
    height = 0;
    width = 5;
    depth = 5;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::hopper;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    
    // チェストの設置
    height = 0;
    width = 5;
    depth = 4;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type=left";
    
    height = 0;
    width = 6;
    depth = 4;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type=right";
    
    
    // ３方への壁の設置
    constexpr int wallWidth = 4;
    
    for (height = 0; height < 6; ++height) {
        for (depth = 0; depth < size.depth; ++depth) {
            for (i = 0; i < wallWidth; ++i) {
                width = 0;
                posi.z = depth;
                posi.x = width + i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                
                width = size.width - 1;
                posi.z = depth;
                posi.x = width - i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
            }
        }
        
        for (width = wallWidth; width < (size.width - wallWidth); ++width) {
            for (i = 0; i < wallWidth; ++i) {
                depth = size.depth - 1;
                posi.z = depth - i;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
            }
        }
    }
    
    
}

void building::createGateBuilding(std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                                  const WN::Vec3 &center,
                                  WN::direction facing,
                                  const WN::Vec3 &defaultPosi,
                                  const houseSize &size,
                                  const WN::Vec3 &sendPosition,
                                  std::string &commands
                                  ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // 高さ用のデフォルト値
    const int heightDefault = defaultPosi.y + 1;
    
    // １階分の高さ
    constexpr int floorHeight = 8;
    
    
    for (depth = 0; depth < size.depth; ++depth) {
        for (width = 0; width < size.width; ++width) {
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            
            (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::gildedBlackstone;
        }
    }
    
    int counter = 0;
    
    for (height = 0; height < 2 * floorHeight; ++height) {
        for (depth = 0; depth < size.depth; ++depth) {
            for (width = 0; width < size.width; ++width) {
                counter = 0;
                
                if (depth == 0 &&
                    !(
                      (width >= size.width/2-1) &&
                      (width <= size.width/2) &&
                      height < 2
                      )
                    ) {
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
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                if (counter == 1) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                } else if (counter == 2) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::gildedBlackstone;
                }
                
            }
        }
    }
    
    for (height = 7; height < 18; height += floorHeight) {
        for (depth = 1; depth < size.depth - 1; ++depth) {
            for (width = 1; width < size.width - 1; ++width) {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::cryingObsidian;
            }
        }
    }
}

void building::createBridge(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                               const WN::Vec3 &center,
                               WN::direction facing,
                               const WN::Vec3 &defaultPosi,
                               const houseSize &size,
                               const WN::Vec3 &sendPosition,
                               std::string &commands
                               ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int height, depth;
    
    int i, j;

    /*外側*/
    //ジャックオランタン
    height = 0;
    for(i = 0; i < 9; i += 8){
        for(j = 0; j < 19; j += 18){
            if (i == 0) {
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jackOLantern;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
            } else {
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jackOLantern;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
            }
        }
    }

    height = 2;
    for(i = 0; i < 9; i += 8){
        for(j = 5; j < 14; j += 8){
            if (i == 0) {
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jackOLantern;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
            } else {
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jackOLantern;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
            }
        }
    }

    //橋のクォーツブロック
    height = 0;
    for(i = 0; i < 9; i += 8){
        for(j = 1; j < 19; j += 16){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    //ハーフブロック
    for(height = 0; height < 2; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 2; j < 18; j += 14){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                if(height == 0){
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
                    } else {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
                }
            }
        }
    }

    //橋のクォーツブロック
    height = 1;
    for(i = 0; i < 9; i += 8){
        for(j = 3; j < 18; j += 12){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    //ハーフブロック
    for(height = 1; height < 3; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 4; j < 15; j += 10){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                if(height == 1){
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
                    } else {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
                }
            }
        }
    }

    //橋の中心(ハーフブロック類)
    for(height = 2; height < 4; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 6; j < 15; j += 6){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                if(height == 2){
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                    } else {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
                }
            }
        }
    }

    height = 1;
    for(i = 0; i < 9; i += 8){
        for(j = 5; j < 15; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
        }
    }

    height = 2;
    for(i = 0; i < 9; i += 8){
        for(j = 7; j < 12; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
            if (j == 9) {
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jackOLantern; 
                if (i == 0) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
                } else {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
                }
            } else {
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
            }
        }
    }

    height = 3;
    for(i = 0; i < 9; i += 8){
        for(j = 7; j < 12; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzSlab;
        }
    }

    /*内側*/
    //橋のはじめの渡る部分
    height = 0;
    for(i = 1; i < 8; ++i){
        for(j = 0; j < 2; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        if ( i > 2 && i < 6){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::brickSlab;
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        }
        }
    }

    height = 0;
    for(i = 1; i < 8; ++i){
        for(j = 17; j < 19; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        if ( i > 2 && i < 6){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::brickSlab;
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        }
        }
    }

    //橋の階段部分
    height = 0; depth = 2;
    for(i = 1; i < 8; ++i){
        posi.z = depth;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
    }

    height = 1;
    for(i = 1; i < 8; ++i){
        for(j = 3; j < 5; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        if ( j == 3){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type =bottom";
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
        }
        }
    }

    height = 2; depth = 5;
    for(i = 1; i < 8; ++i){
        posi.z = depth;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
    }

    height = 0; depth = 16;
    for(i = 1; i < 8; ++i){
        posi.z = depth;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
    }

    height = 1;
    for(i = 1; i < 8; ++i){
        for(j = 15; j > 13; --j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        if ( j == 15){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type =bottom";
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
        }
        }
    }

    height = 2; depth = 13;
    for(i = 1; i < 8; ++i){
        posi.z = depth;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
    }

    //橋の中心部分
    height = 2;
    for(i = 1; i < 8; ++i){
        for(j = 6; j < 8; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
        if ( i > 2 && i < 6){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::brickSlab;
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        }
        }
    }

    for(i = 1; i < 8; ++i){
        for(j = 8; j < 11; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        if ( i > 2 && i < 6){ 
            if (j == 9 && i == 4){
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
            } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::prismarineBrickSlab;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
            }
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
        }
        }
    }

    for(i = 1; i < 8; ++i){
        for(j = 11; j < 13; ++j){
        posi.z = j;
        posi.x = i;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "type = top";
        if ( i > 2 && i < 6){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::brickSlab;
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzSlab;
        }
        }
    }
}





