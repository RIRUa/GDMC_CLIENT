//
//  gimmick.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/03/18.
//

#include "gimmick.hpp"

void gimmick::automaticDoor(std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            const WN::Vec3 &sendPosition,
                            std::string &commands,
                            WN::Vec3 doorLeftPosi,
                            Minecraft::MinecraftBlock blockType
                            ) {
    /** 使用変数の定義**/
    int wallCounter = 0;
    // 方角指定
    WN::EveryDirection directions = WN::EveryDirection(facing);
    // for用
    int width, height, depth;
    
    //　配列の指定子
    WN::Vec3 posi(0,0,0);
    
    /** 自動ドア作成開始**/
    // ピストン埋め
    depth = doorLeftPosi.z + 1;
    for (height = 0; height < 3; ++height) {
        
        width = doorLeftPosi.x - 2;
        
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
        (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].angle = directions.right;
        
        width = doorLeftPosi.x - 1;
        
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
        
        width = doorLeftPosi.x + 3;
        
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
        (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].angle = directions.left;
        
        width = doorLeftPosi.x + 2;
        
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        
    }
    
    // レッドストーンワイヤの回路
    for (depth = doorLeftPosi.z; depth <= doorLeftPosi.z + 2; ++depth) {
        for (width = doorLeftPosi.x - 2; width <= doorLeftPosi.x + 3; ++width) {
            wallCounter = 0;
            if (depth == doorLeftPosi.z) {
                wallCounter++;
            }
            if (depth == doorLeftPosi.z + 2) {
                wallCounter++;
            }
            if (width <= doorLeftPosi.x - 1) {
                wallCounter++;
            }
            if (width >= doorLeftPosi.x + 2) {
                wallCounter++;
            }
            // 大地を削らなくていい場所を省く
            if (wallCounter == 2) {
                continue;
            }

            // 13と18の時は１ます上に
            if (width == doorLeftPosi.x - 2 || width == doorLeftPosi.x + 3) {
                height = -1;
            }else{
                height = -2;
            }

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;

            if (depth == doorLeftPosi.z + 1 && (width == doorLeftPosi.x - 1 || width == doorLeftPosi.x + 2)) {
                (*block3d)[doorLeftPosi.y - 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            }
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
        }
    }

    Minecraft::MinecraftBlock block = Minecraft::MinecraftBlock::air;
    depth = doorLeftPosi.z + 1;
    for (height = 0; height <= 2; ++height) {
        for (width = doorLeftPosi.x - 3; width <= doorLeftPosi.x + 4; ++width) {
            if (width >= doorLeftPosi.x - 2 && width <= doorLeftPosi.x + 3) {
                continue;
            }

            switch (height) {
                case 0:
                    block = Minecraft::MinecraftBlock::redstoneTorch;
                    break;

                case 2:
                    block = Minecraft::MinecraftBlock::redstoneWire;
                    break;

                default:
                    continue;
            }

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = block;
            if (height == 2) {
                (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].addition = "east=side,north=side,power=15,south=side,west=side";
            }
        }
    }

    for (height = 0; height < 3; ++height) {
        for (depth = doorLeftPosi.z; depth <= doorLeftPosi.z + 2; ++depth) {
            if (depth == doorLeftPosi.z + 1) {
                continue;
            }
            for (width = doorLeftPosi.x; width <= doorLeftPosi.x + 1; ++width) {
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                if (height > 0) {
                    (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
                } else {
                    (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stonePressurePlate;
                }
            }
        }
    }
}

void gimmick::waterElevator(
                            std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            const WN::Vec3 &sendPosition,
                            std::string &commands,
                            WN::Vec3 elePosi,
                            int elevatorHeight,
                            const std::vector< int > &floor,
                            Minecraft::MinecraftBlock blockType
                            ) {
    // 方角指定
    WN::EveryDirection directions = WN::EveryDirection(facing);
    // for用
    int width, height, depth;
    
    //　配列の指定子
    WN::Vec3 posi(0,0,0);

    /** 自動水流エレベーター作成開始**/

    //クォーツブロック
    for(height = 0; height < elevatorHeight + 1; ++height){
        for(depth = elePosi.z -1; depth < elePosi.z + 2; ++depth ){
            for(width = elePosi.x - 3; width < elePosi.x + 4; ++width){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[elePosi.y + height][posi.z][posi.x].block = blockType;
            }
        }  
    }

    // ピストン埋め
    height = -1; depth = elePosi.z;
    width = elePosi.x + 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::piston;
    (*block3d)[elePosi.y + height][posi.z][posi.x].angle = directions.left;

    width = elePosi.x -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::piston;
    (*block3d)[elePosi.y + height][posi.z][posi.x].angle = directions.right;

    //空気を置く。
    height = -1; depth = elePosi.z; width = elePosi.x + 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    // レッドストーンワイヤの回路
    height = -1; depth = elePosi.z -1;
    width = elePosi.x + 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;

    width = elePosi.x - 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;

    //オブザーバーの設置
    for (height = 0; height < elevatorHeight; ++height) {
        
        depth = elePosi.z;
        width = elePosi.x + 2;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
    
        if(std::find(floor.begin(),floor.end(),height) != floor.end()){
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
            
            depth = elePosi.z - 2;
            width = elePosi.x + 2;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stoneButton;
            (*block3d)[elePosi.y + height][posi.z][posi.x].angle = directions.front;
        } else {
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::observer;
            (*block3d)[elePosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
        }

        depth = elePosi.z;
        width = elePosi.x - 2;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        if(std::find(floor.begin(),floor.end(),height) != floor.end()){
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
            
            depth = elePosi.z - 2;
            width = elePosi.x - 2;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stoneButton;
            (*block3d)[elePosi.y + height][posi.z][posi.x].angle = directions.front;
        } else {
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::observer;
            (*block3d)[elePosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
        }
    }

    //石のボタン
    height = 0;
    depth = elePosi.z - 2;
    width = elePosi.x - 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stoneButton;
    (*block3d)[elePosi.y + height][posi.z][posi.x].angle = directions.front;

    width = elePosi.x + 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stoneButton;
    (*block3d)[elePosi.y + height][posi.z][posi.x].angle = directions.front;

    //ソウルサンドとマグマブロック
    height = -1;
    width = elePosi.x;
    depth = elePosi.z;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::magmaBlock;

    width = elePosi.x -1;
    depth = elePosi.z;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::soulSand;

    //水
    width = elePosi.x;
    depth = elePosi.z;
    for (height = 0; height < elevatorHeight; ++height) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
        }

    //ガラスと看板
    width = elePosi.x;
    depth = elePosi.z -1;
    for (height = 0; height < elevatorHeight; ++height) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        if(std::find(floor.begin(),floor.end(),height) != floor.end() ||
        std::find(floor.begin(),floor.end(),height -1) != floor.end() || 
        height == 0 || height == 1){  
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakWallSign;
            (*block3d)[elePosi.y + height][posi.z][posi.x].angle = directions.left;
        } else {
            (*block3d)[elePosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }
}

void gimmick::automaticWaterField(
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

    //レッドストーン回路
    height = -1; width = size.width-2; 
    for(depth = 3; depth < 10; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }

    height = -1; width = size.width-2; depth = 10;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    height = 0; width = size.width-2;
    for(depth = 11; depth < size.depth-3; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }

    height = 0; width = size.width-2; depth = size.depth-3;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    height = 0; width = size.width-2; depth = size.depth-2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;

    depth = size.depth-2; 
    for (width = 7; width < size.width-2; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }

    height = 1; width = 6; depth = size.depth-2; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;

    height = 2; width = 6; depth = size.depth-2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);

    WN::Vec3 dispensorPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                           dispensorPosi.x + sendPosition.x,
                                                                           dispensorPosi.y + sendPosition.y,
                                                                           dispensorPosi.z + sendPosition.z
                                                                           ),
                                                                  4,
                                                                  "minecraft:water_bucket",
                                                                  1
                                                                  );
}

void gimmick::createFountain(
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

    //レッドストーントーチ
    width = 0; depth = 0;
        for(int j = 1; j < 14; j++){
        height = -3 + 2*j;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
    }

    //レッドストーンランプ
    for(int i = 0; i < 13; i++){
        height = -2 + 2*i ;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneLamp;
    }

    //ディスペンサー
    width = 0; depth = 0; height = 24;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);

    WN::Vec3 dispensorPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                           dispensorPosi.x + sendPosition.x,
                                                                           dispensorPosi.y + sendPosition.y,
                                                                           dispensorPosi.z + sendPosition.z
                                                                           ),
                                                                  4,
                                                                  "minecraft:water_bucket",
                                                                  1
                                                                  );

    width = 0; depth = -1; height = 15;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    dispensorPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;

    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                           dispensorPosi.x + sendPosition.x,
                                                                           dispensorPosi.y + sendPosition.y,
                                                                           dispensorPosi.z + sendPosition.z
                                                                           ),
                                                                  4,
                                                                  "minecraft:water_bucket",
                                                                  1
                                                                  );
                                                                  
    width = 0; depth = 1; height = 15;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    dispensorPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;

    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                           dispensorPosi.x + sendPosition.x,
                                                                           dispensorPosi.y + sendPosition.y,
                                                                           dispensorPosi.z + sendPosition.z
                                                                           ),
                                                                  4,
                                                                  "minecraft:water_bucket",
                                                                  1
                                                                  );

    width = 1; depth = 0; height = 15;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    dispensorPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;

    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                           dispensorPosi.x + sendPosition.x,
                                                                           dispensorPosi.y + sendPosition.y,
                                                                           dispensorPosi.z + sendPosition.z
                                                                           ),
                                                                  4,
                                                                  "minecraft:water_bucket",
                                                                  1
                                                                  );
    
    width = -1; depth = 0; height = 15;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    dispensorPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;

    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                           dispensorPosi.x + sendPosition.x,
                                                                           dispensorPosi.y + sendPosition.y,
                                                                           dispensorPosi.z + sendPosition.z
                                                                           ),
                                                                  4,
                                                                  "minecraft:water_bucket",
                                                                  1
                                                                  );

    //レッドストーン
    width = 0; height = -2;
    for(depth = -2; depth > -13; --depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }

    depth = -12; height = -2;
    for(width = -2; width < 0; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }

    //リピーター
    width = 0; depth = -1; height = -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    depth = -9; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    //クロック回路
    //リピータ
    depth = -12; height = -2;
    for(width = -3; width > -10; --width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "delay = 4";
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    }

    depth = -13; height = -2;
    for(width = -3; width > -10; --width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "delay = 4";
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
    }

    //レッドストーン
    width = -10; height = -2;
    for(depth = -13; depth < -11; ++depth){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z + size.depth/2;
        posi.x += defaultPosi.x + size.depth/2;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }

    //レッドストーンコンパレーター
    height = -2; width = -2; depth = -13; 
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::comparator;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "mode = subtract";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    //レバー
    height = -2; width = -2; depth = -14;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z + size.depth/2;
    posi.x += defaultPosi.x + size.depth/2;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lever;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "powered = true";
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
}

void gimmick::createPigBurner(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
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
    
    constexpr int hole = 1;
    
    // 回路作成
    for (height = 2; height < 8; height += 2) {
        width = hole;
        depth = hole;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
        
        width = size.width - 1 - hole;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
        
        depth = size.depth - 1 - hole;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
        
        width = hole;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
    }
    
    height = 1;
    for (depth = hole + 1; depth < size.depth - 1 - hole; ++depth) {
        width = hole;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
        
        width = size.width - 1 - hole;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }
    
    for (width = hole + 1; width < size.width - 1 - hole; ++width) {
        depth = size.depth - 1 - hole;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }
    
    int i, j = 0;
    
    for (i = 1; i < 3; ++i) {
        for (j = 1; j < 3; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }
            width = size.width - 1 - hole - i;
            depth = size.depth - 1 - hole - j;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
            
            width = hole + i;
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
        }
    }
    
    // リピーター
    width = (size.width - 1) / 2;
    depth = size.depth - 1 - hole;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    
    // ボタン（水流起動用）
    width = size.width - 1 - hole - 2;
    depth = hole + 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedButton;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
}


void gimmick::automaticEquipment(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                        const WN::Vec3 &center,
                        WN::direction facing,
                        const WN::Vec3 &defaultPosi,
                        const houseSize &size,
                        const WN::Vec3 &sendPosition,
                        std::string &commands,
                        const WN::Vec3 &equipPosi
                        ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    WN::Vec3 posi(0,0,0);
    int width, height, depth;
    int i;
    int boxPosiInside;
    
    WN::Vec3 boxPosi;
    
    
    height = equipPosi.y;
    width = equipPosi.x;depth = equipPosi.z;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedPressurePlate;
    
    for (i = 0; i < 2; ++i) {
        
        height = equipPosi.y + i;
        
        width = equipPosi.x - 1;depth = equipPosi.z;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
        boxPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
        if (i == 0) {
            for (boxPosiInside = 0; boxPosiInside < 9; ++boxPosiInside) {
                commands += Minecraft::Command::itemInBox(
                                                          WN::Vec3(boxPosi.x + sendPosition.x,
                                                                   boxPosi.y + sendPosition.y,
                                                                   boxPosi.z + sendPosition.z),
                                                          boxPosiInside,
                                                          "minecraft:netherite_leggings",
                                                          1
                                                          );
            }
        } else {
            for (boxPosiInside = 0; boxPosiInside < 9; ++boxPosiInside) {
                commands += Minecraft::Command::itemInBox(
                                                          WN::Vec3(boxPosi.x + sendPosition.x,
                                                                   boxPosi.y + sendPosition.y,
                                                                   boxPosi.z + sendPosition.z),
                                                          boxPosiInside,
                                                          "minecraft:netherite_helmet",
                                                          1
                                                          );
            }
        }
        
        width = equipPosi.x;depth = equipPosi.z + 1;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        boxPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
        
        if (i == 0) {
            for (boxPosiInside = 0; boxPosiInside < 9; ++boxPosiInside) {
                commands += Minecraft::Command::itemInBox(
                                                          WN::Vec3(boxPosi.x + sendPosition.x,
                                                                   boxPosi.y + sendPosition.y,
                                                                   boxPosi.z + sendPosition.z),
                                                          boxPosiInside,
                                                          "minecraft:netherite_boots",
                                                          1
                                                          );
            }
        } else {
            for (boxPosiInside = 0; boxPosiInside < 9; ++boxPosiInside) {
                commands += Minecraft::Command::itemInBox(
                                                          WN::Vec3(boxPosi.x + sendPosition.x,
                                                                   boxPosi.y + sendPosition.y,
                                                                   boxPosi.z + sendPosition.z),
                                                          boxPosiInside,
                                                          "minecraft:netherite_chestplate",
                                                          1
                                                          );
            }
        }
        
        width = equipPosi.x - 1;depth = equipPosi.z + 1;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::dispenser;
        
        if (i == 0) {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "lit=false";
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::diamondBlock;
        }
    }
    
    height = equipPosi.y - 2;
    
    for (width = equipPosi.x; width < equipPosi.x + 2; ++width) {
        depth = equipPosi.z;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    }
    
    for (width = equipPosi.x; width < equipPosi.x + 2; ++width) {
        depth = equipPosi.z + 1;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    }
    
    width = equipPosi.x - 1;depth = equipPosi.z + 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneTorch;
    
    height = equipPosi.y - 3;
    width = equipPosi.x;
    depth = equipPosi.z + 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::repeater;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    
    height = equipPosi.y - 3;
    width = equipPosi.x + 1;
    depth = equipPosi.z + 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
    
}

