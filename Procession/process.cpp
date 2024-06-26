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

// -MARK: 実行関数
void Process::operator()() {
    int i,j;
    
    std::cout << "create Bridge" << std::endl;
    for(i=-180;i < 181; i+= 60){
        if(i == 0){
            continue;
        } 
            this->createBridge(WN::Vec3(i,0,0), WN::direction::North);
            this->createBridge(WN::Vec3(0,0,i), WN::direction::West);
    }
    
    std::cout << "create Fountain" << std::endl;
    for (i = -100; i < 150; i += 100) {
        if (i== 0) {
            continue;
        }
        this->createFountain(WN::Vec3(i,0,i), WN::direction::North);
        this->createFountain(WN::Vec3(i,0,-i), WN::direction::North);
        
    }

    std::cout << "create House1" << std::endl;
    this->createHouse1(WN::Vec3(-150,0,45), WN::direction::East);
    this->createHouse1(WN::Vec3(-50,0,50), WN::direction::South);
    this->createHouse1(WN::Vec3(-50,0,-50), WN::direction::North);
    
    std::cout << "create House2" << std::endl;
    this->createHouse2(WN::Vec3(-50,0,150), WN::direction::North);
    this->createHouse2(WN::Vec3(-50,0,-150), WN::direction::South);
    this->createHouse2(WN::Vec3(-150,0,-45), WN::direction::East);

    std::cout << "create Automatic Water Field" << std::endl;
    for (i = 1; i < 7; i++) {
        for (j = 30; j < 185 - (i - 1) * 15; j += 15) {
            
            if (j > 85 && j < 120 && i >= 3 && i <= 5 ) {
                continue;
            }
            
            this->createAutomaticWaterField(
                                            WN::Vec3(
                                                     j,
                                                     0,
                                                     i * 25
                                                     ),
                                            WN::direction::South
                                            );
        }
    }
    
    auto circleFunc = [](int a) -> int {
        if (a < 3) {
            return 0;
        } else if (a < 5) {
            return 1;
        } else if (a == 7) {
            return 5;
        } else {
            return a - 3;
        }
    };
    
    std::cout << "create PigBurner" << std::endl;
    for (j = 0; j < 8; j++) {
        for (i = 30; i < 185 - (circleFunc(j) * 20); i += 20) {
            
            if (j >= 3 && j <= 4 && i > 80 && i < 115) {
                continue;
            }
            
            this->createPigBurner(WN::Vec3(
                                           i,
                                           0,
                                           -30 + j * -20
                                           ),
                                  WN::direction::South
                                  );
        }
    }

    std::cout << "create GateBuilding" << std::endl;
    for (i = -130; i < 131; i += 260) {
        if(i == -130){
            this->createGateBuilding(WN::Vec3(-130,0,i), WN::direction::South);
        } else {
            this->createGateBuilding(WN::Vec3(-130,0,i), WN::direction::North);
        }
    }

    std::cout << "create Streetlight1" << std::endl;
    for(i = -160; i < 161; i += 20){
        if (i < 11 && i > -11) {
            continue;
        } 
        if (i < -91 && i > -111) {
            continue;
        } 
        if (i < 111 && i > 89) {
            continue;
        } 
        this->createStreetlight1(WN::Vec3(-90,0,i), WN::direction::North);
        this->createStreetlight1(WN::Vec3(-110,0,i), WN::direction::North);
    }
    
    for(i = -160; i < -9; i += 20){
        if (i < -91 && i > -111) {
            continue;
        }
        this->createStreetlight1(WN::Vec3(i,0,-90), WN::direction::North);
        this->createStreetlight1(WN::Vec3(i,0,-110), WN::direction::North);
        this->createStreetlight1(WN::Vec3(i,0,90), WN::direction::North);
        this->createStreetlight1(WN::Vec3(i,0,110), WN::direction::North);
    }

    std::cout << "create Streetlight2" << std::endl;
    for(i = -140; i < 141; i += 20){
        if (i < 11 && i > -11) {
            continue;
        } 
        if (i < -91 && i > -111) {
            continue;
        } 
        if (i < 111 && i > 89) {
            continue;
        } 
        this->createStreetlight2(WN::Vec3(-120,0,i), WN::direction::North);
    }

    for(i = -120; i < 121; i += 240){
        this->createStreetlight2(WN::Vec3(-140,0,i), WN::direction::North);
    }
    
    for(i = -60; i < -39; i += 20){
        this->createStreetlight2(WN::Vec3(i,0,-80), WN::direction::North);
        this->createStreetlight2(WN::Vec3(i,0,-120), WN::direction::North);
        this->createStreetlight2(WN::Vec3(i,0,80), WN::direction::North);
        this->createStreetlight2(WN::Vec3(i,0,120), WN::direction::North);
        this->createStreetlight2(WN::Vec3(i,0,20), WN::direction::North);
        this->createStreetlight2(WN::Vec3(i,0,-20), WN::direction::North);
        this->createStreetlight2(WN::Vec3(i,0,180), WN::direction::North);
        this->createStreetlight2(WN::Vec3(i,0,-180), WN::direction::North);

    }

    for(i = -180; i < 181; i += 20){
        if (i < 11 && i > -11) {
            continue;
        } 
        if (i < -91 && i > -111) {
            continue;
        } 
        if (i < 111 && i > 89) {
            continue;
        } 
        this->createStreetlight2(WN::Vec3(-80,0,i), WN::direction::North);
        this->createStreetlight2(WN::Vec3(-20,0,i), WN::direction::North);
    }
    
    std::cout << "------------sending start------------" << std::endl;
    /** 送信部位（消さない） **/
    this->sendData();
    std::cout << "------------sending finish------------" << std::endl;
}


bool Process::init() {
    this->commands = "";
    this->createArea = std::make_shared< Minecraft::blockInfoOf3D >();
    Minecraft::initBlockInfoOf3D(
                                 *(this->createArea),
                                 this->area,
                                 WN::Vec3(0, 0, 0)
                                 );
    
    WN::Vec3 defaultPosi(
                         this->area.x/2,
                         this->groundHeight,
                         this->area.z/2
                         );
    int height;
    const double PI = std::acos(-1.0);
    double sita = 0.0;
    double radius = 0;
    WN::Vec3 posi(0,0,0);
    
    // sita += (PI / 1000)のところはもう少し良いアルゴリズムを探すべきかも
    for (height = 0; height < this->groundHeight; ++height) {
        for (radius = (this->area.x / 2 - 1); radius >= 0; radius -= 0.5) {
            for (sita = 0.0; sita < 2 * PI; sita += (PI / 1000)) {
                posi.x = static_cast<WN::position>( std::round( double(radius) * std::cos(sita) ) );
                posi.z = static_cast<WN::position>( std::round( double(radius) * std::sin(sita) ) );
                
                if (height == this->groundHeight - 1 && radius >= (this->area.x / 2 - 1.5)) {
                    (*this->createArea)[height][defaultPosi.z + posi.z][defaultPosi.x + posi.x].block = Minecraft::MinecraftBlock::water;
                    (*this->createArea)[height - 1][defaultPosi.z + posi.z][defaultPosi.x + posi.x].block = Minecraft::MinecraftBlock::seaLantern;
                } else {
                    (*this->createArea)[height][defaultPosi.z + posi.z][defaultPosi.x + posi.x].block = Minecraft::MinecraftBlock::lightGrayConcrete;
                }
            }
        }
    }
    
    height = this->groundHeight - 1;
    int i, j;
    
    for (i = this->area.z / -2; i < this->area.z / 2; ++i) {
        for (j = -5; j < 5; ++j) {
            
            if ((*this->createArea)[this->groundHeight - 1][defaultPosi.z + i][defaultPosi.x + j].block != Minecraft::MinecraftBlock::air) {
                (*this->createArea)[this->groundHeight - 2][defaultPosi.z + i][defaultPosi.x + j].block = Minecraft::MinecraftBlock::seaLantern;
                (*this->createArea)[this->groundHeight - 1][defaultPosi.z + i][defaultPosi.x + j].block = Minecraft::MinecraftBlock::water;
            }
            
        }
    }
    
    for (i = this->area.z / -2; i < this->area.z / 2; ++i) {
        for (j = -5; j < 5; ++j) {
            
            if ((*this->createArea)[this->groundHeight - 1][defaultPosi.z + j][defaultPosi.x + i].block != Minecraft::MinecraftBlock::air) {
                (*this->createArea)[this->groundHeight - 2][defaultPosi.z + j][defaultPosi.x + i].block = Minecraft::MinecraftBlock::seaLantern;
                (*this->createArea)[this->groundHeight - 1][defaultPosi.z + j][defaultPosi.x + i].block = Minecraft::MinecraftBlock::water;
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

void Process::createHouse1(
                           const WN::Vec3 &center,
                           const WN::direction &facing
                           ) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {40,40};
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
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
                           *(this->sendPosi),
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
    
    WN::Vec3 equipPosi = WN::Vec3(
                              25,
                              1,
                              22
                              );
    
    gimmick::automaticEquipment(this->createArea,
                                center,
                                facing,
                                defaultPosi,
                                size,
                                *(this->sendPosi),
                                this->commands,
                                equipPosi
                                );
}

void  Process::createHouse2(
                            const WN::Vec3 &center,
                            const WN::direction &facing
                            ) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {40,40};
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
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
                           *(this->sendPosi),
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
                           std::vector<int>{5, 11},
                           Minecraft::MinecraftBlock::smoothQuartz
                           );
}

void  Process::createStreetlight1(const WN::Vec3 &center, const WN::direction &facing) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {3,3};
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    interior::createStreetlight1(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 *(this->sendPosi),
                                 this->commands
                                 );
}

void  Process::createStreetlight2(const WN::Vec3 &center, const WN::direction &facing) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {2,1};
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    interior::createStreetlight2(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 *(this->sendPosi),
                                 this->commands
                                 );
}

void Process::createAutomaticWaterField(const WN::Vec3 &center, const WN::direction &facing) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {13,20};
    
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
                                 *(this->sendPosi),
                                 this->commands
                                 );
}

void  Process::createFountain(const WN::Vec3 &center, const WN::direction &facing) {
    WN::EveryDirection directions = WN::EveryDirection();
    const houseSize size = {26,26};

    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;

    building::createFountain(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           this->commands
                           );

   gimmick::createFountain(
                          this->createArea,
                          center,
                          facing,
                          defaultPosi,
                          size,
                          *(this->sendPosi),
                          this->commands
                          );
}

void Process::createPigBurner(const WN::Vec3 &center, const WN::direction &facing) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {11,11};
    
    WN::Vec3 posi(0,0,0);
    
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
    
    gimmick::createPigBurner(
                             this->createArea,
                             center,
                             facing,
                             defaultPosi,
                             size,
                             *(this->sendPosi),
                             this->commands
                             );
    
    interior::createPigBurner(
                              this->createArea,
                              center,
                              facing,
                              defaultPosi,
                              size,
                              *(this->sendPosi),
                              this->commands
                              );
}

void Process::createGateBuilding(const WN::Vec3 &center, const WN::direction &facing) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {10,10};
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    building::createGateBuilding(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 *(this->sendPosi),
                                 this->commands
                                 );
    gimmick::waterElevator(
                           this->createArea,
                           center,
                           facing,
                           defaultPosi,
                           size,
                           *(this->sendPosi),
                           this->commands,
                           WN::Vec3(
                                    5,
                                    this->groundHeight + 1,
                                    8
                                    ),
                           10,
                           std::vector<int>{8},
                           Minecraft::MinecraftBlock::whiteConcrete
                           );
    
    interior::createGateBuilding(
                                 this->createArea,
                                 center,
                                 facing,
                                 defaultPosi,
                                 size,
                                 *(this->sendPosi),
                                 this->commands
                                 );
}

void Process::createBridge(const WN::Vec3 &center, const WN::direction &facing) {
    WN::EveryDirection directions = WN::EveryDirection();
    
    const houseSize size = {8,18};
    
    WN::Vec3 posi(0,0,0);
    
    WN::Vec3 defaultPosi(
                         size.width/2,
                         this->groundHeight,
                         size.depth/2
                         );
    defaultPosi.rotation(facing);
    defaultPosi.x = this->area.x/2 + center.x - defaultPosi.x;
    defaultPosi.z = this->area.z/2 + center.z - defaultPosi.z;
    
    building::createBridge(
                              this->createArea,
                              center,
                              facing,
                              defaultPosi,
                              size,
                              *(this->sendPosi),
                              this->commands
                              );

    interior::createBridge(
                              this->createArea,
                              center,
                              facing,
                              defaultPosi,
                              size,
                              *(this->sendPosi),
                              this->commands
                              );

}
