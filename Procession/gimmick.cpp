//
//  gimmick.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/03/18.
//

#include "gimmick.hpp"

void gimmick::automaticDoor(
                            std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
                            int doorPosi,
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
    
    /** 自動ドア作成開始**/
    // ピストン埋め
    for (height = 0; height < 3; ++height) {
        for (depth = 1; depth < 2; ++depth) {
            width = doorPosi - 2;
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
            
            
            width = doorPosi+3;
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }
    
    // レッドストーンワイヤの回路
    for (depth = 0; depth <= 2; ++depth) {
        for (width = doorPosi - 2; width <= doorPosi+3; ++width) {
            wallCounter = 0;
            if (depth == 0) {
                wallCounter++;
            }
            if (depth == 2) {
                wallCounter++;
            }
            if (width <= doorPosi - 1) {
                wallCounter++;
            }
            if (width >= doorPosi+2) {
                wallCounter++;
            }
            // 大地を削らなくていい場所を省く
            if (wallCounter == 2) {
                continue;
            }
            
            // 13と18の時は１ます上に
            if (width == doorPosi - 2 || width == doorPosi+3) {
                height = -1;
            }else{
                height = -2;
            }
            
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
            if (depth == 1 && (width == doorPosi - 1 || width == doorPosi+2)) {
                (*block3d)[defaultPosi.y - 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            }
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
        }
    }
    
    Minecraft::MinecraftBlock block = Minecraft::MinecraftBlock::air;
    depth = 1;
    for (height = 0; height <= 2; ++height) {
        for (width = doorPosi - 3; width <= doorPosi+4; ++width) {
            if (width >= doorPosi - 2 && width <= doorPosi+3) {
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
            
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = block;
            if (height == 2) {
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "east=side,north=side,power=15,south=side,west=side";
            }
        }
    }
    
    height = 0;
    depth = 0;
    for (depth = 0; depth <= 2; ++depth) {
        if (depth == 1) {
            continue;
        }
        for (width = doorPosi; width <= doorPosi + 1; ++width) {
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stonePressurePlate;
        }
    }
}
