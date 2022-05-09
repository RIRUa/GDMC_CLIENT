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
                            int elePosi,
                            WN::direction angle,
                            Minecraft::MinecraftBlock blockType,
                            WN::Vec3 defaultPosi
                            ) {
    /** 使用変数の定義**/
    int wallCounter = 0;
    // 方角指定
    WN::EveryDirection directions = WN::EveryDirection();
    // for用
    int width, height, depth;
    
    //　配列の指定子
    WN::Vec3 posi(0,0,0);

    /** 自動水流エレベーター作成開始**/
    // ピストン埋め
    height = 0; depth =0;
    width = elePosi + 2;
    posi.z = defaultPosi.z + depth;
    posi.x = defaultPosi.x + width;
    
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    width = elePosi -2;
    posi.z = defaultPosi.z + depth;
    posi.x = defaultPosi.x + width;

    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
    // レッドストーンワイヤの回路
    height = 0; depth =-1;
    width = elePosi + 2;
    posi.z = defaultPosi.z + depth;
    posi.x = defaultPosi.x + width;

    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;

    width = elePosi - 2;
    posi.z = defaultPosi.z + depth;
    posi.x = defaultPosi.x + width;

    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;

    //オブザーバーの設置
    for (height = 0; height < 15; ++height) {
    depth =0;
    width = elePosi + 2;
    posi.z = defaultPosi.z + depth;
    posi.x = defaultPosi.x + width;
    
    (*block3d)[defaultPosi.y + height + 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::observer;
    (*block3d)[defaultPosi.y + height + 1][posi.z][posi.x].angle = directions.front;

    width = elePosi - 2;
    posi.z = defaultPosi.z + depth;
    posi.x = defaultPosi.x + width;

    (*block3d)[defaultPosi.y + height + 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::observer;
    (*block3d)[defaultPosi.y + height + 1][posi.z][posi.x].angle = directions.behind;
    }
}