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
    
    const houseSize size = {40,40};
    
    WN::Vec3 posi(0,0,0);
    
    WN::direction facing = WN::direction::East;
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    std::cout << defaultPosi.x << "," << defaultPosi.z << std::endl;
    
//    building::createHouse1(
//                           this->createArea,
//                           center,
//                           facing,
//                           defaultPosi,
//                           size
//                           );
    
//    interior::createHouse1(
//                           this->createArea,
//                           center,
//                           facing,
//                           defaultPosi,
//                           size
//                           );
    
//    gimmick::automaticDoor(
//                           this->createArea,
//                           center,
//                           WN::direction::North,
//                           defaultPosi,
//                           size,
//                           WN::Vec3(9, this->groundHeight + 1, 10),
//                           Minecraft::MinecraftBlock::air
//                           );
    
}
