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
    height = 0; depth = 0;
    for (width = 0; width < size.width +1; ++width){
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

    height = 0; depth = 39;
    for(width = 0; width < size.width ; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
        
        }

    height = 0; width = 40;
    for(depth = 0; depth < size.depth ; ++depth){

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;    

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
        }
    
    height = 0; width = 0;
    for(depth = 0; depth < size.depth ; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warped_fence;
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

    for(depth = 11; depth < 30; ++depth){
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

    for(width = 30; width < size.width -7; ++width){
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

    for(width = 30; width < size.width-7; ++width){
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

    for(depth = 30; depth < size.depth -7; ++depth){
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
    
    for(depth = 29; depth < size.depth -7; ++depth){
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
    for(width = 1; width < size.width; ++width){
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
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stone_button;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    //トラップドア
    width = 6; height = 0; depth = 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::spruce_trapdoor;

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
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartz_stairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;


    width = 6; depth = size.depth-4; height = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartz_stairs;
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
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_slab;
    }

    //ネザーブロック
    width = 6;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_bricks;

    //ハーフブロック
    width = 2;
    for(depth = 17; depth < size.depth -1; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_slab;
    }

    width = 10;
    for(depth = 17; depth < size.depth -1; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_slab;
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
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_slab;
        }
    }

    width = 1; height = 0; depth = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    commands += std::string("replaceitem")+" "+"block"+" "+std::to_string(posi.x - defaultPosi.x -6 +center.x)+" "+std::to_string(defaultPosi.y + height + 4)+" "+std::to_string(posi.z -defaultPosi.z -10 +center.z)+" "+"container.0"+" "+"minecraft:netherite_hoe"+" "+"1"+"\n";
    commands += std::string("replaceitem")+" "+"block"+" "+std::to_string(posi.x - defaultPosi.x -6 +center.x)+" "+std::to_string(defaultPosi.y + height + 4)+" "+std::to_string(posi.z -defaultPosi.z -10 +center.z)+" "+"container.1"+" "+"minecraft:diamond_hoe"+" "+"1"+"\n";
    commands += std::string("replaceitem")+" "+"block"+" "+std::to_string(posi.x - defaultPosi.x -6 +center.x)+" "+std::to_string(defaultPosi.y + height + 4)+" "+std::to_string(posi.z -defaultPosi.z -10 +center.z)+" "+"container.2"+" "+"minecraft:wheat_seeds"+" "+"64"+"\n";
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
                    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::diamondBlock;
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
    width = ((size.width - 1) / 2);
    depth = ((size.depth - 1) / 2);
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::spawner;
    
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
    int i = 0;
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

