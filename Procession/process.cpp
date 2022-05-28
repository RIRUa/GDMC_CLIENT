//
//  process.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/25.
//

#include "process.hpp"

Process::Process(WN::Vec3 *sendPosi) {
    this->sendPosi = sendPosi;
    this->init();
}

Process::~Process() {
}

bool Process::init() {
    this->commands = "";
    this->createArea = std::make_shared< Minecraft::blockInfoOf3D >();
    Minecraft::initBlockInfoOf3D(
                                 *(this->createArea),
                                 this->area,
                                 WN::Vec3(0, 0, 0)
                                 );
    this->possibility = std::make_shared< possibilities >( this->area.z, std::vector< bool >(this->area.x, true) );
    
    WN::Vec3 defaultPosi(
                         this->area.x/2,
                         this->groundHeight,
                         this->area.z/2
                         );
    int height;
    const double PI = std::acos(-1.0);
    double sita = 0.0;
    int radius = 0;
    WN::Vec3 posi(0,0,0);
    
    // sita += (PI / 1000)のところはもう少し良いアルゴリズムを探すべきかも
    for (height = 0; height < this->groundHeight; ++height) {
        for (sita = 0.0; sita < 2 * PI; sita += (PI / 1000)) {
            for (radius = (this->area.x / 2 - 1); radius >= 0; radius -= 1) {
                posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
                posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
                (*this->createArea)[height][defaultPosi.z + posi.z][defaultPosi.x + posi.x].block = Minecraft::MinecraftBlock::lightGrayConcrete;
                
            }
        }
    }
    
    
    return true;
}

bool Process::sendData() {
    GDMC session;
    
    session.setBlocks(*(this->sendPosi),
                      *(this->createArea)
                      );
    session.command(this->commands);
    
    return true;
}

void Process::createHouse1(const WN::Vec3 &center) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {40,40};
    
    WN::Vec3 posi(0,0,0);
    
    WN::direction facing = WN::direction::North;
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    std::cout << defaultPosi.x << "," << defaultPosi.z << std::endl;
    
    building::createHouse1(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           *(this->sendPosi),
                           this->commands
                           );
    
    interior::createHouse1(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           this->commands
                           );
    
    WN::Vec3 doorPosi(19, this->groundHeight + 1, 10);
    
    gimmick::automaticDoor(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           *(this->sendPosi),
                           this->commands,
                           doorPosi,
                           Minecraft::MinecraftBlock::air
                           );
    
}

void  Process::createHouse2(const WN::Vec3 &center) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {40,40};
    
    WN::direction facing = WN::direction::North;
    
    WN::Vec3 defaultPosi(
                         this->area.x/2 + center.x - size.width/2,
                         this->groundHeight,
                         this->area.z/2 + center.z - size.depth/2
                         );
    
    building::createHouse2(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           *(this->sendPosi),
                           this->commands
                           );
    
    interior::createHouse2(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           this->commands
                           );
    
    WN::Vec3 elePosi(10, this->groundHeight , 34);
    
    gimmick::waterElevator(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           *(this->sendPosi),
                           this->commands,
                           elePosi,
                           13,
                           std::vector<int>{5, 11}
                           );
}

void  Process::createStreetlight1(const WN::Vec3 &center) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {4,4};
    
    WN::direction facing = WN::direction::North;
    
    WN::Vec3 defaultPosi(
                         this->area.x/2 + center.x - size.width/2,
                         this->groundHeight,
                         this->area.z/2 + center.z - size.depth/2
                         );
    
    interior::createStreetlight1(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 this->commands
                                 );
}

void  Process::createStreetlight2(const WN::Vec3 &center) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {2,2};
    
    WN::direction facing = WN::direction::North;
    
    WN::Vec3 defaultPosi(
                         this->area.x/2 + center.x - size.width/2,
                         this->groundHeight,
                         this->area.z/2 + center.z - size.depth/2
                         );
    
    interior::createStreetlight2(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 this->commands
                                 );
}

void  Process::createAutomaticWaterField(const WN::Vec3 &center) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {13,20};
    
    WN::direction facing = WN::direction::South;
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    building::createAutomaticWaterField(
                                        this->createArea,
                                        center,
                                        facing,
                                        defaultPosi,
                                        size,
                                        *(this->sendPosi),
                                        this->commands
                                        );
    
    gimmick::automaticWaterField(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 *(this->sendPosi),
                                 this->commands
                                 );
    
    interior::createFarmProducts(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 this->commands
                                 );
}

void Process::createPigBurner(const WN::Vec3 &center) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {11,11};
    
    WN::Vec3 posi(0,0,0);
    
    WN::direction facing = WN::direction::North;
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    building::createPigBurner(
                              this->createArea,
                              center,
                              facing,
                              defaultPosi,
                              size,
                              *(this->sendPosi),
                              this->commands
                              );
}
