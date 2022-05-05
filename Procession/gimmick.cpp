//
//  gimmick.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/03/18.
//

#include "gimmick.hpp"

void gimmick::automaticDoor(std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction direction,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size,
                            WN::Vec3 doorLeftPosi,
                            Minecraft::MinecraftBlock blockType
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
            width = doorLeftPosi.x - 2;
            posi.z = defaultPosi.z + doorLeftPosi.z + depth;
            posi.x = defaultPosi.x + doorLeftPosi.z + width;
            
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].angle = directions.right;
            
            width = doorLeftPosi.x - 1;
            posi.z = defaultPosi.z + doorLeftPosi.z + depth;
            posi.x = defaultPosi.x + doorLeftPosi.z + width;
            
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            
            
            width = doorLeftPosi.x + 3;
            posi.z = defaultPosi.z + doorLeftPosi.z + depth;
            posi.x = defaultPosi.x + doorLeftPosi.z + width;
            
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].angle = directions.left;
            
            width = doorLeftPosi.x + 2;
            posi.z = defaultPosi.z + doorLeftPosi.z + depth;
            posi.x = defaultPosi.x + doorLeftPosi.z + width;
            
            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        }
    }
    
    // レッドストーンワイヤの回路
//    for (depth = 0; depth <= 2; ++depth) {
//        for (width = doorLeftPosi.x - 2; width <= doorLeftPosi.x + 3; ++width) {
//            wallCounter = 0;
//            if (depth == 0) {
//                wallCounter++;
//            }
//            if (depth == 2) {
//                wallCounter++;
//            }
//            if (width <= doorLeftPosi.x - 1) {
//                wallCounter++;
//            }
//            if (width >= doorLeftPosi.x + 2) {
//                wallCounter++;
//            }
//            // 大地を削らなくていい場所を省く
//            if (wallCounter == 2) {
//                continue;
//            }
//
//            // 13と18の時は１ます上に
//            if (width == doorLeftPosi.x - 2 || width == doorLeftPosi.x + 3) {
//                height = -1;
//            }else{
//                height = -2;
//            }
//
//            posi.z = defaultPosi.z + doorLeftPosi.z + depth;
//            posi.x = defaultPosi.x + doorLeftPosi.z + width;
//
//            if (depth == 1 && (width == doorLeftPosi.x - 1 || width == doorLeftPosi.x + 2)) {
//                (*block3d)[doorLeftPosi.y - 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
//            }
//            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
//        }
//    }
//
//    Minecraft::MinecraftBlock block = Minecraft::MinecraftBlock::air;
//    depth = 1;
//    for (height = 0; height <= 2; ++height) {
//        for (width = doorLeftPosi.x - 3; width <= doorLeftPosi.x + 4; ++width) {
//            if (width >= doorLeftPosi.x - 2 && width <= doorLeftPosi.x + 3) {
//                continue;
//            }
//
//            switch (height) {
//                case 0:
//                    block = Minecraft::MinecraftBlock::redstoneTorch;
//                    break;
//
//                case 2:
//                    block = Minecraft::MinecraftBlock::redstoneWire;
//                    break;
//
//                default:
//                    continue;
//            }
//
//            posi.z = defaultPosi.z + doorLeftPosi.z + depth;
//            posi.x = defaultPosi.x + doorLeftPosi.z + width;
//            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = block;
//            if (height == 2) {
//                (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].addition = "east=side,north=side,power=15,south=side,west=side";
//            }
//        }
//    }
//
//    height = 0;
//    depth = 0;
//    for (depth = 0; depth <= 2; ++depth) {
//        if (depth == 1) {
//            continue;
//        }
//        for (width = doorLeftPosi.x; width <= doorLeftPosi.x + 1; ++width) {
//            posi.z = defaultPosi.z + doorLeftPosi.z + depth;
//            posi.x = defaultPosi.x + doorLeftPosi.z + width;
//            (*block3d)[doorLeftPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stonePressurePlate;
//        }
//    }
}
