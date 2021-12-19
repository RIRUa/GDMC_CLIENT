//
//  Minecraft.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/17.
//

#ifndef Minecraft_hpp
#define Minecraft_hpp

#include <iostream>


namespace Minecraft {

    enum class MinecraftBlock:int {
        stone,
        cobbleStone
    };

    std::string getMinecraftBlockName(MinecraftBlock block, std::string addition);

    using position = int64_t;
    
    typedef struct __blockInfo {
        position x;
        position y;
        position z;
        MinecraftBlock block;
        
        std::string getInfo();
    }blockInfo;
}


#endif /* Minecraft_hpp */
