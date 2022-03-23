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
    
    WN::Vec3 defaultPosi(
                         this->area.x/2 + center.x - size.width/2,
                         this->groundHeight,
                         this->area.z/2 + center.z - size.depth/2
                         );
    
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
                if (height == 4 || height == 9) {
                    wallCounter == 0 ? wallCounter++: wallCounter;
                }
                
                posi.z = defaultPosi.z + depth;
                posi.x = defaultPosi.x + width;
                
                // 照明の追加
                if ( (height == 3 || height == 8) && posi.x%3 == 0 && posi.z%3 == 0) {
                    (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::lantern;
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
    
    gimmick::automaticDoor(
                           this->createArea,
                           15,
                           WN::direction::North,
                           Minecraft::MinecraftBlock::diamondBlock,
                           defaultPosi
                           );
    
}
