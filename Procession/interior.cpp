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
        width = 2 + i; 
        for(int j=0; j < 28; j+=2){
            depth = 2 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    //second glass
    depth = 0;
    for(height = 6; height < 8; ++height){
        for(int i = 0; i < 10; i+=4){
        width = 19 + i;

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
        width = 20 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    depth = 30;
    for(height = 6; height < 8; ++height){
        for(int i = 0; i < 10; i+=4){
        width = 19 + i;

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
        width = 20 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    width = 30;
    for(height = 6; height < 8; ++height){
        for(int i = 0; i < 27; i+=4){
        depth = 2 + i; 

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
        depth = 3 + i; 

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
        width = 3 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 14 + j;
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
        width = 2 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 14 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 4 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 14 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 3 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 15 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 3 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 13 + j;

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
        width = 2 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 14 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 4 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 14 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 3 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 15 + j;

            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::torch;
        }
    }

    for(int i=0; i < 14; i+=5){
        width = 3 + i; 
        for(int j=0; j < 15; j+=6){
            depth = 13 + j;

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
        width = 21 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 6 + j;
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
        width = 20 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 6 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 22 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 6 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 21 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 5 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 21 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 7 + j;
            
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
        width = 20 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 6 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 22 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 6 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 21 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 7 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }

    for(int i=0; i < 9; i+=5){
        width = 21 + i; 
        for(int j=0; j < 23; j+=6){
            depth = 5 + j;
            
            posi.z = depth;
            posi.x = width;
            posi.rotation(facing);
            posi.z += defaultPosi.z;
            posi.x += defaultPosi.x;
            (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
        }
    }


    // dark fence 
    for(width = 0; width < 17; ++width){
        height = 5; depth = 0;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 0; depth < 10; ++depth){
        width = 0; height = 5;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(int i = 0; i < 7; ++i){
        width = 4; depth = 3 + i; height = 5 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;

        width = 13;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(width = 0; width < 5; ++width){
        depth = 10; height = 11;
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(width = 13; width < 18; ++width){
        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 11; depth < 31; ++depth){
        width = 0; height = 11;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 0; depth < 31; ++depth){
        width = 30; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(width = 0; width < 31; ++width){
        depth = 30; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }
    
    for(width = 17; width < 31; ++width){
        depth = 0;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    }

    for(depth = 1; depth < 11; ++depth){
        width =17;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::nether_brick_fence;
    } 

// 3階の照明
    height = 15; width = 23;
    for(int i = 0; i < 20; i+=3){
        depth = 6 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
    }

    height = 15; width = 24;
    for(int i = 0; i < 20; i+=3){
        depth = 6 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::oak_fence;
    }

    height = 14; width = 23;
    for(int i = 0; i < 20; i+=3){
        depth = 6 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }

    height = 14; width = 24;
    for(int i = 0; i < 20; i+=3){
        depth = 6 + i; 

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;

        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glowstone;
    }

//三階のガラス
    depth = 3;
    for(height = 12; height < 14; ++height){
        for(int i = 0; i < 7; i+=4){
        width = 21 + i;

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
        width = 22 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }

    depth = 27;
    for(height = 12; height < 14; ++height){
        for(int i = 0; i < 7; i+=4){
        width = 21 + i;

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
        width = 22 + i;

        posi.z = depth;
        posi.x = width;
        posi.rotation(facing);
        posi.z += defaultPosi.z;
        posi.x += defaultPosi.x;
        (*block3d)[defaultPosi.y + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::glass;
        }
    }
}