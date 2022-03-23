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
            width = 13;
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
            
            
            width = 18;
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
        }
    }
    
    // レッドストーンワイヤの回路
    for (depth = 0; depth <= 2; ++depth) {
        for (width = 13; width <= 18; ++width) {
            wallCounter = 0;
            if (depth == 0) {
                wallCounter++;
            }
            if (depth == 2) {
                wallCounter++;
            }
            if (width <= 14) {
                wallCounter++;
            }
            if (width >= 17) {
                wallCounter++;
            }
            // 大地を削らなくていい場所を省く
            if (wallCounter == 2) {
                continue;
            }
            
            // 13と18の時は１ます上に
            if (width == 13 || width == 18) {
                height = -1;
            }else{
                height = -2;
            }
            
            posi.z = defaultPosi.z + depth;
            posi.x = defaultPosi.x + width;
            
            if (depth == 1 && (width == 14 || width == 17)) {
                (*block3d)[defaultPosi.y - 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            }
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
        }
    }
    
    Minecraft::MinecraftBlock block = Minecraft::MinecraftBlock::air;
    depth = 1;
    for (height = 0; height <= 2; ++height) {
        for (width = 12; width <= 19; ++width) {
            if (width >= 13 && width <= 18) {
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
    
    for (height = 0; height <= 2; ++height) {
        if (height == 1) {
            continue;
        }
        for (depth = 0; depth <= 2; ++depth) {
            if (depth == 1) {
                continue;
            }
            for (width = 15; width <=16; ++width) {
                switch (height) {
                    case 0:
                        block = Minecraft::MinecraftBlock::stonePressurePlate;
                        break;
                        
                    case 2:
                        block = Minecraft::MinecraftBlock::lantern;
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
    }
}
