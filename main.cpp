//
//  main.cpp
//  GDMC_Client
//
#include "untouchable/GDMC.hpp"

int main(){
    
    
    GDMC session;
    
//    Minecraft::blockInfo a(1,2,3,Minecraft::MinecraftBlock::stone,"");

//    std::cout << sizeof(a) << std::endl;
    
    Minecraft::blockInfoOf3D a;
    Minecraft::initBlockInfoOf3D(a, WN::Vec3(1, 2, 3));
    int i,height,k;
    
    for (i = 0; i < 3; i++) {
        for (height = 0; height < 2; height++) {
            for (k = 0; k < 1; k++) {
                a[height][i][k].block = Minecraft::MinecraftBlock::stone;
            }
        }
    }
    
    std::cout << session.setBlocks(WN::Vec3(0, 4, 0), a) << std::endl;
    
    return 0;
}
