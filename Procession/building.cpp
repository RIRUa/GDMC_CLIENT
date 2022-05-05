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
    // ガラスを使うか
    bool isGlassBlock = false;
    
    for (depth = 1; depth < size.depth - 1; ++depth) {
        for (width = 1; width < size.width - 1; ++width) {
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
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
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;
                
                (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::prismarineWall;
            } else if (depth == 0 && (width >= size.width/2-1) && (width <= size.width/2)) {
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;
                
                (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedFenceGate;
                (*block3d)[defaultPosi.y][posi.z][posi.x].angle = directions.front;
                
                posi.z = defaultPosi.z + 1 + depth;
                posi.x = defaultPosi.x + width;
                
                (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedBlackstonePressurePlate;
            }
        }
    }
    
    /**　基礎の作成　**/
    for (depth = 7; depth < size.depth-15; ++depth) {
        for (width = 2; width < size.width-2; ++width) {
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
            (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
        }
    }
    
    
    /**　玄関前の階段の作成　**/
    depth = 6;
    for (width = 15; width < (size.width - 15); ++width) {
        posi.z = defaultPosi.z + depth;
        posi.x = defaultPosi.x + width;
        
        (*block3d)[defaultPosi.y][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
        (*block3d)[defaultPosi.y][posi.z][posi.x].angle = directions.behind;
    }
    
    // ドアを入れるか
    bool isDoor = false;
    // ドアの種類
    Minecraft::MinecraftBlock doorType;
    // ドアの向き
    std::shared_ptr<WN::direction> facing;
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
                        facing = directions.front;
                        
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
                        facing = directions.front;
                        
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
                                facing = directions.behind;
                            }
                        }
                        counter--;
                    }
                    counter++;
                }
                
                
                if (counter > 0) {
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    
                    if (isGlassBlock && counter == 1) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                    }
                } else if (height == 3 && (width%3 == 0 && depth%3 == 0)) {
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
                    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "hanging=true";
                } else if (isDoor) {
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = doorType;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = facing;
                    if (height == 1) {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition = "half=upper";
                    } else {
                        (*block3d)[heightDefault + height][posi.z][posi.x].addition = "half=lower";
                    }
                    
                    if (hinge ^
                        !(facing == directions.front ||
                         facing == directions.right)
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
                        facing = directions.right;
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
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    
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
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = doorType;
                    (*block3d)[heightDefault + height][posi.z][posi.x].angle = facing;
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
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
                } else if (counter >= 2) {
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                }
                
            }
        }
    }
    
    // TODO: ２階に鉄格子
    
}

void building::createHouse2(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction direction,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size 
                            ) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // その位置が壁か角か判別するためのカウンター
    int wallCounter;
    
    /****/
    for (height = 0; height < 5; ++height) {
        /**　四方へのブロック配置処理　**/
        for (depth = 0; depth < 31; ++depth) {
            for (width = 0; width < 31; ++width) {
                // カウンターを０に
                wallCounter = 0;
                
                if (depth <= 0 ){
                     // 入口用ドアのスペースを開ける
                    if ((width == 15 || width == 16) && height < 2 ) {
                        continue;
                    }
                    wallCounter++;
                }
                if (width == 0) {
                    wallCounter++;
                }
                if (depth >= 30) {
                    wallCounter++;
                }
                if (width >= 30) {
                    wallCounter++;
                }
                
                // ２階の床用
                if (height == 4 || height == 9) {
                    wallCounter == 0 ? wallCounter++: wallCounter;
                }
                
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;
                
                
                // 壁にブロックの挿入
                if (wallCounter == 2 && !(depth > 0 && depth <= 3)) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }else if (wallCounter >= 1) {
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
                
            }
        }
    }

//warped_fence
    for (width = -7; width < 30; ++width){
                height = 0; depth = -5;

                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                if(width == 15 || width == 16){
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
                }
            }

    for (width = -7; width < 30; ++width){
                height = 0; depth = 35;

                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                
            }

    for (depth = -5; depth < 35; ++depth){
                height = 0; width = 30;

                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                
            }
    
    for (depth = -5; depth < 35; ++depth){
                height = 0; width = -7;

                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                
            }

// dark fence 
    for(width = 0; width < 17; ++width){
        height = 5; depth = 0;

        posi.z = defaultPosi.z + depth;
        posi.x = defaultPosi.x + width;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 0; depth < 11; ++depth){
        width = 0; height = 5;

        posi.z = defaultPosi.z + depth;
        posi.x = defaultPosi.x + width;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

// second floor
    for(width = 17; width < 31; ++width){
        for(height = 5; height < 10; ++height){
            for(depth = 0; depth < 31; ++depth){
                if(depth == 0 || depth == 30){
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;

                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
            }
        }
    }

    for(height = 5; height < 10; ++height){
        for(depth = 0; depth < 31; ++depth){
            for(width = 17; width < 31; ++width){
                if(width == 17 || width == 30){
                    posi.z = defaultPosi.z + depth;
                    posi.x = defaultPosi.x + width;

                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
            }
        }
    }   

    for(depth = 0; depth < 31; ++depth){
        for(width = 17; width < 31; ++width){
            height = 10;

            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    } 

    for(width = 0; width < 17; ++width){
        for(height = 5; height < 11; ++height){
            for(depth = 10; depth < 31; ++depth){
                if(depth == 10 || depth == 30){
                
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
                }
            }
        }
    }

    for(height = 5; height < 11; ++height){
        for(depth = 11; depth < 30; ++depth){
            width = 0;

            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

//stair
    // for(width = 4; width < 14; ++width){
        
    // }
}

