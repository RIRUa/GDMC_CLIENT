//
//  main.cpp
//  GDMC_Client
//
#include "util/Minecraft.hpp"

int main(){
    
    
    
    Minecraft::blockInfo a(1,2,3,Minecraft::MinecraftBlock::stone,"");

    std::cout << sizeof(a) << std::endl;
    
    return 0;
}
