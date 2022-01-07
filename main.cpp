//
//  main.cpp
//  GDMC_Client
//
#include "untouchable/GDMC.hpp"

int main(){
    
    
    GDMC session;
    
//    Minecraft::blockInfo a(1,2,3,Minecraft::MinecraftBlock::stone,"");

//    std::cout << sizeof(a) << std::endl;
    int line = 5;
    WN::Vec3 size(line,5,line);
    
    Minecraft::blockInfoOf3D a;
    Minecraft::initBlockInfoOf3D(
                                 a,
                                 size,
                                 WN::Vec3(0,0,0)
                                 );
    int i,height,k;

    for (i = 0; i < size.y; i++) {
        for (height = 0; height < size.z; height++) {
            for (k = 0; k < size.x; k++) {
                a[height][i][k].block = Minecraft::MinecraftBlock::stone;
            }
        }
    }

    std::cout << session.setBlocks(WN::Vec3(100, 4, 0), a) << std::endl;
    
    return 0;
}
