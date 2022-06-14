//
//  interior.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/05/04.
//

#include "interior.hpp"
#include <random>

void interior::createHouse1(
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
    bool isStair = false;
    
    /**　階段の作成　**/
    for (height = 0; height < 5; ++height) {
        for (depth = 13; depth < 19; ++depth) {
            for (width = (size.width - 5); width < (size.width - 3); ++width) {
                
                counter = 0;
                isStair = false;
                
                if (height < 2) {
                    counter++;
                } else {
                    if (depth + height < 18) {
                        counter++;
                        if (depth + height == 17) {
                            isStair = true;
                        }
                    }
                }
                
                if (counter == 1) {
                    posi.z = depth;
                    posi.x = width;
                    posi.rotation(facing);
                    posi.z += defaultPosi.z;
                    posi.x += defaultPosi.x;
                    
                    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
                    
                    if (isStair) {
                        posi.z = depth + 1;
                        posi.x = width;
                        posi.rotation(facing);
                        posi.z += defaultPosi.z;
                        posi.x += defaultPosi.x;
                        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
                        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.front;
                    }
                }
                
            }
        }
    }
    
    height = 0;
    width = (size.width - 6);
    
    for (depth = 17; depth < 19; ++depth) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteConcrete;
        
        (*block3d)[heightDefault + height + 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
        (*block3d)[heightDefault + height + 1][posi.z][posi.x].angle = directions.right;
        
        posi.z = depth;
        posi.x = width - 1;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartzStairs;
        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.right;
        
    }
    
    height = 3;
    width = (size.width - 7);
    depth = 18;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
    
    
    // 玄関前の灯り
    height = 3;
    width = 15;
    depth = 9;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "hanging=true";
    
    height = 3;
    width = (size.width - 16);
    depth = 9;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "hanging=true";
    
    // 倉庫作成（納戸）
    for (height = 0; height < 3; ++height) {
        for (depth = size.depth-18; depth < size.depth-16; ++depth) {
            for (width = (size.width - 12); width < (size.width - 3); width += 2) {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                
                (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
                (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.left;
                if (depth == size.depth-18) {
                    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "type=right";
                } else {
                    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "type=left";
                    
                    // コマンド作成
                    WN::Vec3 chestPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
                    
                    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                       chestPosi.x + sendPosition.x,
                                                                       chestPosi.y + sendPosition.y,
                                                                       chestPosi.z + sendPosition.z
                                                                       ),
                                                              0,
                                                              "minecraft:netherite_sword",
                                                              1
                                                              );
                    
                    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                       chestPosi.x + sendPosition.x,
                                                                       chestPosi.y + sendPosition.y,
                                                                       chestPosi.z + sendPosition.z
                                                                       ),
                                                              1,
                                                              "minecraft:lapis_lazuli",
                                                              64
                                                              );
                }
            }
        }
    }
    
    // 便利ブロックの設置
    height = 0;
    
    width = (size.width - 9);
    depth = 8;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::craftingTable;
    
    depth = 11;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::furnace;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.front;
    
    width = (size.width - 8);
    depth = 8;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoker;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.behind;
    
    depth = 11;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::blastFurnace;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.front;
    
    width = (size.width - 7);
    depth = 8;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::cartographyTable;
    
    depth = 11;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::fletchingTable;
    
    width = (size.width - 6);
    depth = 8;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::grindstone;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.behind;
    
    depth = 11;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smithingTable;
    
    width = (size.width - 5);
    depth = 8;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stonecutter;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.behind;
    
    depth = 11;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::anvil;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.front;
    
    width = (size.width - 4);
    depth = 8;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::jukebox;
    
    depth = 11;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::enderChest;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.front;
    
    // ジュークボックス用チェスト＆アルバム
    width = (size.width - 4);
    depth = 9;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.left;
    
    WN::Vec3 chestPosi = (*block3d)[heightDefault + height][posi.z][posi.x].position;
    
    std::string items[] = {
        "minecraft:music_disc_13",
        "minecraft:music_disc_cat",
        "minecraft:music_disc_blocks",
        "minecraft:music_disc_chirp",
        "minecraft:music_disc_far",
        "minecraft:music_disc_mall",
        "minecraft:music_disc_mellohi",
        "minecraft:music_disc_stal",
        "minecraft:music_disc_strad",
        "minecraft:music_disc_ward",
        "minecraft:music_disc_11",
        "minecraft:music_disc_wait",
        "minecraft:music_disc_pigstep",
    };
    
    int i = 0;
    for (std::string item : items) {
        commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                           chestPosi.x + sendPosition.x,
                                                           chestPosi.y + sendPosition.y,
                                                           chestPosi.z + sendPosition.z
                                                           ),
                                                  i,
                                                  item,
                                                  1
                                                  );
        ++i;
    }
    
    // ベッドの設置
    height = 5;width = (size.width - 13);depth = 16;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::magentaBed;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.right;
    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "part=foot";
    
    width++;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::magentaBed;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.right;
    (*block3d)[heightDefault + height][posi.z][posi.x].addition = "part=head";
    
    
    width = size.width - 5;
    depth = size.depth / 2 - 7;
    for (height = -3; height < 2; ++height) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        if (height != -1) {
            (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
        } else {
            (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::water;
        }
        
        (*block3d)[heightDefault + height][posi.z][posi.x].angle = nullptr;
        
    }
}

void interior::createHouse2(
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
    int i,j;

    //地面の照明
    height = -1;
    for(i=0; i < 28; i+=3){
        width = 7 + i; 
        for(j=0; j < 28; j+=2){
            depth = 7 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    //玄関周りの地面の照明
    height = -1; depth = 2; 
    for(i=0; i < 37; i+=3){
        width = 2 + i; 
        if(i == 18){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
        } else {
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    height = -1; depth = 37;
    for(i=0; i < 37; i+=3){
        width = 2 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }

    for(i=0; i < 28; i+=3){
        width = 2;
        depth = 6 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;

        width = 38;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }


    //醸造台の作成
    height = 0;
    for(i=0; i < 4; i+=3){
        width = 29 + i; 
        for(j=0; j < 25; j+=4){
            depth = 7 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::cauldron;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "level = 3";
        }
    }

    for(i=0; i < 4; i+=3){
        width = 29 + i; 
        for(j=0; j < 25; j+=4){
            depth = 8 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].block = Minecraft::MinecraftBlock::brewingStand;
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition = "has_bottle_0 = false";
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition = "has_bottle_1 = true";
            (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].addition += ",has_bottle_2 = true";
        }
    }

    for(i=0; i < 4; i+=3){
        width = 29 + i; 
        for(j=0; j < 25; j+=4){
            depth = 9 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
            WN::Vec3 chestPosi = (*block3d)[defaultPosi.y + height][posi.z][posi.x].position;
            commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                                            chestPosi.x + sendPosition.x,
                                                                            chestPosi.y + sendPosition.y,
                                                                            chestPosi.z + sendPosition.z
                                                                            ),
                                                                    0,
                                                                    "minecraft:glass_bottle",
                                                                    64
                                                                    );
        }
    }

    //first glass
    depth = 5;
    for(height = 1; height < 3; ++height){
        for(i = 0; i < 10; i+=4){
        width = 7 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 1; height < 3; ++height){
        for(i = 0; i < 10; i+=4){
        width = 8 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 1; height < 3; ++height){
        for(i = 0; i < 5; i+=4){
        width = 26 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 1; height < 3; ++height){
        for(i = 0; i < 5; i+=4){
        width = 27 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    depth = 35;
    for(height = 1; height < 3; ++height){
        for(i = 0; i < 5; i+=4){
        width = 26 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 1; height < 3; ++height){
        for(i = 0; i < 5; i+=4){
        width = 27 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    width = 35;
    for(height = 1; height < 3; ++height){
        for(i = 0; i < 23; i+=4){
        depth = 9 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 1; height < 3; ++height){
        for(i = 0; i < 23; i+=4){
        depth = 10 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    //second glass
    depth = 5;
    for(height = 6; height < 8; ++height){
        for(i = 0; i < 10; i+=4){
        width = 24 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 6; height < 8; ++height){
        for(i = 0; i < 10; i+=4){
        width = 25 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    depth = 35;
    for(height = 6; height < 8; ++height){
        for(i = 0; i < 10; i+=4){
        width = 24 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 6; height < 8; ++height){
        for(i = 0; i < 10; i+=4){
        width = 25 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    width = 35;
    for(height = 6; height < 8; ++height){
        for(i = 0; i < 27; i+=4){
        depth = 7 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 6; height < 8; ++height){
        for(i = 0; i < 27; i+=4){
        depth = 8 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    //二階のシャンデリア
    //プール
    for(i=0; i < 14; i+=5){
        width = 8 + i; 
        for(j=0; j < 15; j+=6){
            depth = 19 + j;
            for(height = 9; height > 6; --height){
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
            }
        }
    }

    height = 7;
    for(i=0; i < 15; i+=5){
        width = 7 + i; 
        for(j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    for(i=0; i < 14; i+=5){
        width = 9 + i; 
        for(j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    for(i=0; i < 14; i+=5){
        width = 8 + i; 
        for(j=0; j < 15; j+=6){
            depth = 20 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    for(i=0; i < 14; i+=5){
        width = 8 + i; 
        for(j=0; j < 15; j+=6){
            depth = 18 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    height = 8;
    for(i=0; i < 15; i+=5){
        width = 7 + i; 
        for(j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(i=0; i < 14; i+=5){
        width = 9 + i; 
        for(j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(i=0; i < 14; i+=5){
        width = 8 + i; 
        for(j=0; j < 15; j+=6){
            depth = 20 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(i=0; i < 14; i+=5){
        width = 8 + i; 
        for(j=0; j < 15; j+=6){
            depth = 18 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

//広場
    for(i=0; i < 9; i+=5){
        width = 26 + i; 
        for(j=0; j < 23; j+=6){
            depth = 11 + j;
            for(height = 9; height > 6; --height){
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
            }
        }
    }

    height = 7;
    for(i=0; i < 9; i+=5){
        width = 25 + i; 
        for(j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    for(i=0; i < 9; i+=5){
        width = 27 + i; 
        for(j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    for(i=0; i < 9; i+=5){
        width = 26 + i; 
        for(j=0; j < 23; j+=6){
            depth = 10 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    for(i=0; i < 9; i+=5){
        width = 26 + i; 
        for(j=0; j < 23; j+=6){
            depth = 12 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    height = 8;
    for(i=0; i < 9; i+=5){
        width = 25 + i; 
        for(j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(i=0; i < 9; i+=5){
        width = 27 + i; 
        for(j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(i=0; i < 9; i+=5){
        width = 26 + i; 
        for(j=0; j < 23; j+=6){
            depth = 12 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(i=0; i < 9; i+=5){
        width = 26 + i; 
        for(j=0; j < 23; j+=6){
            depth = 10 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }


    // dark fenceと松明の生成
    for(width = 5; width < 22; ++width){
        height = 5; depth = 5;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    for(depth = 5; depth < 15; ++depth){
        width = 5; height = 5;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    for(i = 0; i < 7; ++i){
        width = 9; depth = 8 + i; height = 5 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
        (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;

        width = 18;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
        (*block3d)[defaultPosi.y + height +1][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
    }

    for(width = 5; width < 10; ++width){
        depth = 15; height = 11;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    for(width = 18; width < 23; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    for(depth = 16; depth < 36; ++depth){
        width = 5; height = 11;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    for(depth = 5; depth < 36; ++depth){
        width = 35; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    for(width = 5; width < 36; ++width){
        depth = 35; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }
    
    for(width = 22; width < 36; ++width){
        depth = 5;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    for(depth = 6; depth < 16; ++depth){
        width =22;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    } 

// 3階の照明
    height = 15; width = 28;
    for(i = 0; i < 20; i+=3){
        depth = 11 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
    }

    height = 15; width = 29;
    for(i = 0; i < 20; i+=3){
        depth = 11 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
    }

    height = 14; width = 28;
    for(i = 0; i < 20; i+=3){
        depth = 11 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }

    height = 14; width = 29;
    for(i = 0; i < 20; i+=3){
        depth = 11 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }

//三階のガラス
    depth = 8;
    for(height = 12; height < 14; ++height){
        for(i = 0; i < 7; i+=4){
        width = 26 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 12; height < 14; ++height){
        for(i = 0; i < 7; i+=4){
        width = 27 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    depth = 32;
    for(height = 12; height < 14; ++height){
        for(i = 0; i < 7; i+=4){
        width = 26 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    for(height = 12; height < 14; ++height){
        for(i = 0; i < 7; i+=4){
        width = 27 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }
    //屋上のエレベータにつく松明
    height = 13; 
    for(i= 0; i < 5;i +=4){
        width = 8 +i; depth = size.depth -8;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::wallTorch;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    }

    //ランタン
    height = 14;
    for(width = 8; width < 22; width +=3){
        for(depth = 16; depth < size.depth -10; depth +=3){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
        }
    }

    //3階の屋根の照明
    height = 15;
    for(i= 0; i < 10;i +=9){
        width = 24 +i; depth = 7;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;

        depth = size.depth -7;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }
}
    
void interior::createStreetlight1(
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

    //土台
    for(width = 0; width < size.width; ++width){
        height = 0; depth = 0;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
    }

    for(width = 0; width < size.width; ++width){
        height = 0; depth = size.depth - 1;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    }

    for(depth = 1; depth < size.depth; ++depth){
        height = 0; width = 0;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    }

    for(depth = 1; depth < size.depth; ++depth){
        height = 0; width = size.width - 1;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
    }

//柱
    for(height = 0; height < 4; ++height){
        depth = 1; width = 1;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::smoothQuartz;
    }

//ライト部分
    //下の支え
    height = 3;
    depth = 0; width = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half=top";

    depth = size.depth - 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half=top";

    depth = 1; width = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half=top";

    width = size.width - 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "half=top";

    //上の支え
    height = 5;
    depth = 0; width = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.behind;

    depth = size.depth - 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;

    depth = 1; width = 0;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.right;

    width = size.width - 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzStairs;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = std::make_shared <WN::direction>(WN::direction::Up);
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;

    //ライト
    height = 4; depth = 1; width = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneLamp;

    //鎖
    
    for (depth = 0; depth < size.depth; ++depth) {
        for (width = 0; width < size.width; ++width) {
            
            if (width == 1 && depth == 1) {
                continue;
            }
            
            if (width == 1 || depth == 1) {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chain;
            }
        }
    }
    //月照センサー
    height = 5; depth = 1; width = 1;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::daylightDetector;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "inverted=true";
    
    //白のカーペット
    height = 6;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::whiteCarpet;
}

void interior::createStreetlight2(
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

    //柱
    for(height = 0; height < 5; ++height){
        depth = 0; width =0;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::netherBrickFence;
    }

    //月照センサー
    height = 5; depth = 0;
    for (width = 0; width < size.width; ++width) {
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::daylightDetector;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "inverted=true";
    }
    
    //ランプ
    height = 4;
    posi.z = depth;
    posi.x = width - 1;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneLamp;
}

void interior::createFarmProducts(
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

    int v = rand() % 3;

    height = 0; 
    for(depth = 3; depth < 11; ++depth){
        for(width = 2; width < size.width-2; ++width){
            if(width == 6){
                continue;
            } 
            if(v == 2){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::wheat;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "age = 7";
            } else if (v == 1){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::carrots;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "age = 7";
            } else {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::potatoes;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "age = 7";
            }
        }
    }

    height = 1;
    for(depth = 11; depth < size.depth -3; ++depth){
        for(width = 2; width < size.width-2; ++width){
            if(width == 6){
                continue;
            } 
            if(v == 2){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::wheat;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "age = 7";
            } else if (v == 1){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::carrots;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "age = 7";
            } else {
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::potatoes;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "age = 7";
            }
        }
    }
}

void interior::createPigBurner(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
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
    
    
    height = 2;
    
    width = (size.width - 1) / 2;
    depth = (size.depth - 1) / 2;
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lava;
    
    height = 1;
    (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakWallSign;

    for(height = 1;height < 10; height += 4){
        for(width = 0; width < size.width; width += 10){
            for(depth = 0; depth < size.depth; depth +=5){
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;
            }
        }
    }

    height = 9; width = (size.width - 1) / 2;
    for(depth = 0; depth < size.depth; depth +=10){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::seaLantern;
    }
}

void interior::createGateBuilding(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
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
    
    int counter = 0;
    
    width = 2;
    height = 0;
    depth = 1;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.behind;
    // コマンド作成
    WN::Vec3 chestPosi = (*block3d)[heightDefault + height][posi.z][posi.x].position;
    
    for (counter = 0; counter < 28; ++counter) {
        commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                           chestPosi.x + sendPosition.x,
                                                           chestPosi.y + sendPosition.y,
                                                           chestPosi.z + sendPosition.z
                                                           ),
                                                  counter,
                                                  "minecraft:flint_and_steel",
                                                  1
                                                  );
    }
    
    width = 1;
    for (height = 0; height < 6; ++height) {
        for (depth = 1; depth < 8; ++depth) {
            counter = 0;
            
            if (depth == 1) {
                counter++;
            }
            if (height == 0) {
                counter++;
            }
            if (depth == 7) {
                counter++;
            }
            if (height == 5) {
                counter++;
            }
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            
            
            if (counter > 0) {
                (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::obsidian;
            }
            
        }
    }
    
    height = 8;
    
    for (width = size.width / 2 - 1; width < size.width / 2 + 2; ++width) {
        depth = 1;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endPortalFrame;
        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.behind;
        
        depth = 5;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endPortalFrame;
        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.front;
    }
    
    for (depth = 2; depth < 5; ++depth) {
        width = size.width / 2 - 2;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endPortalFrame;
        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.right;
        
        width = size.width / 2 + 2;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        
        (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::endPortalFrame;
        (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.left;
    }
    
    width = 2;
    depth = 1;
    
    posi.z = depth;
    posi.x = width;
    posi.rotation(facing);
    posi.z += defaultPosi.z;
    posi.x += defaultPosi.x;
    
    (*block3d)[heightDefault + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::chest;
    (*block3d)[heightDefault + height][posi.z][posi.x].angle = directions.behind;
    // コマンド作成
    chestPosi = (*block3d)[heightDefault + height][posi.z][posi.x].position;
    
    commands += Minecraft::Command::itemInBox(WN::Vec3(
                                                       chestPosi.x + sendPosition.x,
                                                       chestPosi.y + sendPosition.y,
                                                       chestPosi.z + sendPosition.z
                                                       ),
                                              0,
                                              "minecraft:ender_eye",
                                              64
                                              );
}

void interior::createBridge(std::shared_ptr< Minecraft::blockInfoOf3D > &block3d,
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
    int i,j;

    //焚火の屋根
    height = 8; 
    for(width = 0; width < 9; ++width){
        for(depth = 5; depth < 14; ++depth){
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::campfire;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.left;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "lit = false";
        }
    }

    //フェンス
    height = 1;
    for(i = 0; i < 9; i += 8){
        for(j = 0; j < 19; j += 18){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    for(height = 1; height < 5; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 1; j < 19; j += 16){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
            }
        }
    }

    for(height = 3; height < 8; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 5; j < 14; j += 8){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
            }
        }
    }

    for(height = 4; height < 6; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 2; j < 17; j += 14){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
            }
        }
    }

    for(height = 5; height < 7; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 3; j < 17; j += 12){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
            }
        }
    }

    for(height = 6; height < 8; ++height){
        for(i = 0; i < 9; i += 8){
            for(j = 4; j < 17; j += 10){
                posi.z = j;
                posi.x = i;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
            }
        }
    }

    height = 7;
    for(i = 0; i < 9; i += 8){
        for(j = 6; j < 13; ++j){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFence;
        }
    }

    //フェンスゲート

    for(i = 1; i < 8; ++i){
        for(j = 5; j < 14; j += 8){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oakFenceGate;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].angle = directions.front;
        }
    }

    //ランタン
    height = 3;
    for(i = 0; i < 9; i += 8){
        for(j = 2; j < 19; j += 14){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "hanging = true";
        }
    }

    height = 5;
    for(i = 0; i < 9; i += 8){
        for(j = 4; j < 19; j += 10){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "hanging = true";
        }
    }

    height = 6;
    for(i = 0; i < 9; i += 8){
        for(j = 7; j < 12; j += 2){
            posi.z = j;
            posi.x = i;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].addition = "hanging = true";
        }
    }
}


