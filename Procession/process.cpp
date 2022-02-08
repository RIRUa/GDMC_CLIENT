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
    
    int width, /*height,*/ depth;
    
    for (depth = 0; depth < this->area.z; ++depth) {
        for (width = 0; width < this->area.x; ++width) {
            
            if (depth<=3 || width==0 || depth == this->area.z-1 || width == this->area.x-1) {
                (*this->createArea)[0][depth][width].block = Minecraft::MinecraftBlock::stone;
            }
            
        }
    }
}
