//
//  interior.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2022/05/04.
//

#include "interior.hpp"


void interior::createHouse1(
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
    
}

void interior::createHouse2(
                            std::shared_ptr<Minecraft::blockInfoOf3D> &block3d,
                            const WN::Vec3 &center,
                            WN::direction facing,
                            const WN::Vec3 &defaultPosi,
                            const houseSize &size
                            ) {
    WN::EveryDirection directions = WN::EveryDirection(facing);
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;

    //地面の照明
    height = -1;
    for(int i=0; i < 28; i+=3){
        width = 7 + i; 
        for(int j=0; j < 28; j+=2){
            depth = 7 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    //second glass
    depth = 5;
    for(height = 6; height < 8; ++height){
        for(int i = 0; i < 10; i+=4){
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
        for(int i = 0; i < 10; i+=4){
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
        for(int i = 0; i < 10; i+=4){
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
        for(int i = 0; i < 10; i+=4){
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
        for(int i = 0; i < 27; i+=4){
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
        for(int i = 0; i < 27; i+=4){
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
    for(int i=0; i < 14; i+=5){
        width = 8 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 19 + j;
            for(height = 9; height > 6; --height){
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
            }
        }
    }

    height = 7;
    for(int i=0; i < 15; i+=5){
        width = 7 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 9 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 8 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 20 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 8 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 18 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    height = 8;
    for(int i=0; i < 15; i+=5){
        width = 7 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 9 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 19 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 8 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 20 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 8 + i; 
        for(int j=0; j < 15; j+=6){
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
    for(int i=0; i < 9; i+=5){
        width = 26 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 11 + j;
            for(height = 9; height > 6; --height){
                
                posi.z = depth;
                posi.x = width;
                posi.rotation(facing);
                posi.z += defaultPosi.z;
                posi.x += defaultPosi.x;
                (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
            }
        }
    }

    height = 7;
    for(int i=0; i < 9; i+=5){
        width = 25 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 27 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 26 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 10 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 26 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 12 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    height = 8;
    for(int i=0; i < 9; i+=5){
        width = 25 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 27 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 11 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 26 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 12 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 26 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 10 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }


    // dark fence 
    for(width = 5; width < 22; ++width){
        height = 5; depth = 5;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 5; depth < 15; ++depth){
        width = 5; height = 5;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(int i = 0; i < 7; ++i){
        width = 9; depth = 8 + i; height = 5 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;

        width = 18;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(width = 5; width < 10; ++width){
        depth = 15; height = 11;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(width = 18; width < 23; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 16; depth < 36; ++depth){
        width = 5; height = 11;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 5; depth < 36; ++depth){
        width = 35; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(width = 5; width < 36; ++width){
        depth = 35; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }
    
    for(width = 22; width < 36; ++width){
        depth = 5;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 6; depth < 16; ++depth){
        width =22;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    } 

// 3階の照明
    height = 15; width = 28;
    for(int i = 0; i < 20; i+=3){
        depth = 11 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
    }

    height = 15; width = 29;
    for(int i = 0; i < 20; i+=3){
        depth = 11 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
    }

    height = 14; width = 28;
    for(int i = 0; i < 20; i+=3){
        depth = 11 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }

    height = 14; width = 29;
    for(int i = 0; i < 20; i+=3){
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
        for(int i = 0; i < 7; i+=4){
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
        for(int i = 0; i < 7; i+=4){
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
        for(int i = 0; i < 7; i+=4){
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
        for(int i = 0; i < 7; i+=4){
        width = 27 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }
}