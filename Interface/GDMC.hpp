//
//  GDMC.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/12.
//

#ifndef GDMC_hpp
#define GDMC_hpp

#include <iostream>
#include "../API/URLSession.hpp"
#include "../util/Minecraft.hpp"

class GDMC {
    URLSession session;
    
public:
    GDMC();
    ~GDMC();
    
    std::string getBlock(int x, int y, int z);
    std::string getBlockMoreInfo(int x, int y, int z);
    std::string setBlock(const Minecraft::blockInfo &info);
    std::string setBlocks(const Minecraft::blockInfo &info);
};


#endif /* GDMC_hpp */
