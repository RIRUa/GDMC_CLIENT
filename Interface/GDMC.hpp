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

class GDMC {
    URLSession session;
    
public:
    GDMC();
    ~GDMC();
    
    std::string getBlock(int x, int y, int z);
    std::string setBlock(int x, int y, int z);
};


#endif /* GDMC_hpp */
