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
                            WN::Vec3 elePosi,
                            int elevatorHeight,
                            const std::vector< int > &floor
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
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
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
    
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::piston;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    width = elePosi.x -2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::piston;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    //空気を置く。
    height = -1; depth = elePosi.z; width = elePosi.x + 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    // レッドストーンワイヤの回路
    height = -1; depth = elePosi.z -1;
    width = elePosi.x + 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;

    width = elePosi.x - 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;

    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;

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
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
            (*block3d)[defaultPosi.y + height][posi.z -2][posi.x].block = Minecraft::MinecraftBlock::stone_button;
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::observer;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
        }

        width = elePosi.x - 2;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        if(std::find(floor.begin(),floor.end(),height) != floor.end()){
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
            (*block3d)[defaultPosi.y + height][posi.z -2][posi.x].block = Minecraft::MinecraftBlock::stone_button;
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::observer;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
        }
    }

    //石のボタン
    height = 0;
    depth = elePosi.z;
    width = elePosi.x - 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z -2][posi.x].block = Minecraft::MinecraftBlock::stone_button;

    width = elePosi.x + 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z -2][posi.x].block = Minecraft::MinecraftBlock::stone_button;

    //ソウルサンドとマグマブロック
    height = -1;
    width = elePosi.x;
    depth = elePosi.z;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::magmaBlock;

    width = elePosi.x -1;
    depth = elePosi.z;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::soulSand;

    //水
    width = elePosi.x;
    depth = elePosi.z;
    for (height = 0; height < elevatorHeight; ++height) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
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
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::warpedFenceGate;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        } else {
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }
}

void gimmick::automaticWaterField(
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
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
    commands += std::string("replaceitem")+" "+"block"+" "+std::to_string(posi.x - defaultPosi.x -6 +center.x)+" "+std::to_string(defaultPosi.y + height + 4 + center.y)+" "+std::to_string(posi.z -defaultPosi.z -10 +center.z)+" "+"container.4"+" "+"minecraft:water_bucket"+" "+"1"+"\n";
    
}

