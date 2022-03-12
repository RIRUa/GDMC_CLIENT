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

bool Process::sendDatas() {
    GDMC session;
    
    session.setBlocks(WN::Vec3(0, 4, 0),
                      *(this->createArea)
                      );
    
    return true;
}

void Process::createHouse1(const WN::Vec3 &center) {
    
    const houseSize size = {30,30};
    
    WN::Vec3 posi(0,0,0);
    
    int width, height, depth;
    
    /****/
    for (height = 0; height < 20; ++height) {
        /**　四方へのブロック配置処理　**/
        for (depth = 0; depth < size.depth; ++depth) {
            for (width = 0; width < size.width; ++width) {
                
                if (depth<=3 || width==0 || depth == this->area.z-1 || width == this->area.x-1 || depth >= size.depth-1 || width >= size.width-1) {
                    posi.z = this->area.z/2 + center.z - size.depth/2 + depth;
                    posi.x = this->area.x/2 + center.z - size.width/2 + width;
                    // ブロックの挿入
                    (*this->createArea)[this->groundHeight + height][posi.z][posi.x].block = Minecraft::MinecraftBlock::quartzBlock;
                }

            }
        }
    }
    
    
}
