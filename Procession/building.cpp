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
                            const houseSize &size
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

    // TODO: ２階に鉄格子

}

void building::createHouse2(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size 
                            ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
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

//warped_fence
    for (width = 0; width < 41; ++width){
                height = 0; depth = 0;

                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                if(width == 20 || width == 21){
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
                }
            }

    for (width = 0; width < 41; ++width){
                height = 0; depth = 40;

                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                
            }

    for (depth = 0; depth < 41; ++depth){
                height = 0; width = 40;

                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;    

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                
            }
    
    for (depth = 0; depth < 41; ++depth){
                height = 0; width = 0;

                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;

                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
                
            }


//floor
    for (width = 20; width < 22; ++width){
        for(depth = 0; depth < 6; ++depth){
            height = -1; 
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(width = 5; width < 36; ++width){
        for(depth = 6; depth < 35; ++depth){
            height = -1; 
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
        for (int i = 0; i < 5; ++i){
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
        for (int i = 0; i < 5; ++i){
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
    for(width = 22; width < 36; ++width){
        for(height = 5; height < 10; ++height){
            for(depth = 5; depth < 36; ++depth){
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
        for(depth = 5; depth < 36; ++depth){
            for(width = 22; width < 36; ++width){
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

    for(depth = 5; depth < 36; ++depth){
        for(width = 22; width < 36; ++width){
            height = 10;

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
            for(depth = 15; depth < 36; ++depth){
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

    for(height = 5; height < 10; ++height){
        for(depth = 16; depth < 35; ++depth){
            width = 5;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(width = 5; width < 22; ++width){
        for(depth = 16; depth < 35; ++depth){
            height = 10;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

// root to go up second floor
    for(width = 5; width < 35; ++width){
        for(depth = 10; depth < 15; ++depth){
            if( width == 21 || width == 20 || width == 7 || width == 6){
                height = 4; 

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
    for(depth = 7; depth < 9; ++depth){
        for (height = 5; height < 8; ++height){
            width = 22;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

    for(depth = 29; depth < 31; ++depth){
        for (height = 5; height < 8; ++height){
            width = 22;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

//second floor pool
    for (width = 9; width < 22; ++width){
        height = 5; depth = 27;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    for (depth = 15; depth < 27; ++depth){
        height = 5; width = 9;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

    for (width = 10; width < 22; ++width){
        for (depth = 16; depth < 27; ++depth){
            height = 5;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
        }
    }


//third floor
    for(width = 25; width < 33; ++width){
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

    for(depth = 8; depth < 32; ++depth){
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

    for(width = 25; width < 33; ++width){
        for(depth = 8; depth < 33; ++depth){
            height =16; 
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

//third floor roof
    for(depth = 11; depth < 31; ++depth){
        for(int i = 0; i < 4; i++){
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
        for(int i = 0; i < 4; i++){
            width = 29 + i; height = 19 - i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(depth = 30; depth < 32; ++depth){
        for(width = 26; width < 32; ++width){
            height = 17;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(depth = 30; depth < 31; ++depth){
        for(width = 27; width < 31; ++width){
            height = 18;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(depth = 9; depth < 11; ++depth){
        for(width = 26; width < 32; ++width){
            height = 17;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        }
    }

    for(depth = 10; depth < 11; ++depth){
        for(width = 27; width < 31; ++width){
            height = 18;
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
        for(int i = 0; i < 5; i++){
            width = 24 + i; height = 16 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        }
    }

    for(depth = 11; depth < 31; ++depth){
        for(int i = 0; i < 5; i++){
            width = 29 + i; height = 20 - i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }

    for(width = 28; width < 30; ++width){
        for(int i = 0; i < 5; i++){
            depth = 7 + i; height = 16 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
        }
    }

    for(width = 28; width < 30; ++width){
        for(int i = 0; i < 5; i++){
            depth = 29 + i; height = 20 - i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    for(width = 25; width < 28; ++width){
        for(int i = 0; i < 2; i++){
            height = 16 + i; depth = 7 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
        }
    }

    for(width = 30; width < 33; ++width){
        for(int i = 0; i < 2; i++){
            height = 16 + i; depth = 7 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
        }
    }

    for(width = 25; width < 28; ++width){
        for(int i = 0; i < 2; i++){
            height = 17 - i; depth = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    for(width = 30; width < 33; ++width){
        for(int i = 0; i < 2; i++){
            height = 17 - i; depth = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    for(depth = 30; depth < 33; ++depth){
        for(int i = 0; i < 2; i++){
            height = 17 - i; width = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }

    for(depth = 8; depth < 11; ++depth){
        for(int i = 0; i < 2; i++){
            height = 17 - i; width = 32 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }
    
    for(depth = 30; depth < 33; ++depth){
        for(int i = 0; i < 2; i++){
            height = 16 + i; width = 24 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        }
    }

    for(depth = 8; depth < 11; ++depth){
        for(int i = 0; i < 2; i++){
            height = 16 + i; width = 24 + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        }
    }

    height = 16; width = 24; depth = 7; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    width = 33;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    depth = 33;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    width = 24;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    width = 26; height = 18; depth = 9;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    depth = 10; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    depth = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    depth = 31;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    width = 31; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    depth = 30; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    depth = 10;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    depth = 9;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    width = 27; height = 18;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    height = 19; depth = 10;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    depth = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    depth = 31; height = 18;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    width = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    height = 19; depth = 30;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    depth = 10;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    depth = 9; height = 18;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;


//third floor entry
    for(depth = 29; depth < 31; ++depth){
        for (height = 11; height < 14; ++height){
            width = 25;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }

//secondfloor stairs
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

