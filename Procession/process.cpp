//
//  process.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/25.
//

#include "process.hpp"

Process::Process() {
    this->init();
}

Process::~Process() {
}

bool Process::init() {
    
    this->createArea = std::make_shared< Minecraft::blockInfoOf3D >();
    Minecraft::initBlockInfoOf3D(
                                 *(this->createArea),
                                 this->area,
                                 WN::Vec3(0, 0, 0)
                                 );
    this->possibility = std::make_shared< possibilities >( this->area.z, std::vector< bool >(this->area.x, true) );
    
    int height;
    
    for (height = 0; height < this->groundHeight; ++height) {
        for (auto &block1d : (*this->createArea)[height]) {
            for (auto &block : block1d) {
                block.block = Minecraft::MinecraftBlock::stone;
            }
        }
    }
    
    
    return true;
}

bool Process::sendData() {
    GDMC session;
    
    session.setBlocks(WN::Vec3(0, 4, 0),
                      *(this->createArea)
                      );
    
    return true;
}

void Process::createHouse1(const WN::Vec3 &center) {
    
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {30,30};
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    // その位置が壁か角か判別するためのカウンター
    int wallCounter;
    
    /****/
    for (height = 0; height < 10; ++height) {
        /**　四方へのブロック配置処理　**/
        for (depth = 0; depth < size.depth; ++depth) {
            for (width = 0; width < size.width; ++width) {
                // カウンターを０に
                wallCounter = 0;
                
                if (depth <= 2) {
                    // 入口用ドアのスペースを開ける
                    if ((width == 15 || width == 16) && height < 3 ) {
                        continue;
                    }
                    wallCounter++;
                }
                if (width == 0) {
                    wallCounter++;
                }
                if (depth == this->area.z-1) {
                    wallCounter++;
                }
                if (width == this->area.x-1) {
                    wallCounter++;
                }
                if (depth >= size.depth-1) {
                    wallCounter++;
                }
                if (width >= size.width-1) {
                    wallCounter++;
                }
                
                // ２階の床用
                if (height == 4) {
                    wallCounter == 0 ? wallCounter++: wallCounter;
                }
                
                posi.z = this->area.z/2 + center.z - size.depth/2 + depth;
                posi.x = this->area.x/2 + center.z - size.width/2 + width;
                
                // 照明の追加
                if (height == 3 && posi.x%3 == 0 && posi.z%3 == 0) {
                    (*this->createArea)[this->groundHeight + 3][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
                }
                // 壁にブロックの挿入
                if (wallCounter == 2 && !(depth > 0 && depth <= 3)) {
                    (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::polishedBlackstoneBricks;
                } else if (wallCounter >= 1) {
                    (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                }
                
            }
        }
    }
    /**　自動ドア作成　**/
    // ピストン埋め
    for (height = 0; height < 3; ++height) {
        for (depth = 1; depth < 2; ++depth) {
            width = 13;
            posi.z = this->area.z/2 + center.z - size.depth/2 + depth;
            posi.x = this->area.x/2 + center.z - size.width/2 + width;
            
            (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*this->createArea)[this->groundHeight + height][posi.z][posi.x].angle = directions.right;
            
            
            width = 18;
            posi.z = this->area.z/2 + center.z - size.depth/2 + depth;
            posi.x = this->area.x/2 + center.z - size.width/2 + width;
            
            (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::stickyPiston;
            (*this->createArea)[this->groundHeight + height][posi.z][posi.x].angle = directions.left;
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
            
            posi.z = this->area.z/2 + center.z - size.depth/2 + depth;
            posi.x = this->area.x/2 + center.z - size.width/2 + width;
            
            if (depth == 1 && (width == 14 || width == 17)) {
                (*this->createArea)[this->groundHeight - 1][posi.z][posi.x].block = Minecraft::MinecraftBlock::air;
            }
            (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::redstoneWire;
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
            
            posi.z = this->area.z/2 + center.z - size.depth/2 + depth;
            posi.x = this->area.x/2 + center.z - size.width/2 + width;
            (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = block;
            if (height == 2) {
                (*this->createArea)[this->groundHeight + height][posi.z][posi.x].addition = "east=side,north=side,power=15,south=side,west=side";
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
                
                posi.z = this->area.z/2 + center.z - size.depth/2 + depth;
                posi.x = this->area.x/2 + center.z - size.width/2 + width;
                (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = block;
                if (height == 2) {
                    (*this->createArea)[this->groundHeight + height][posi.z][posi.x].addition = "east=side,north=side,power=15,south=side,west=side";
                }
            }
        }
    }
    
}
