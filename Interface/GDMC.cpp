//
//  GDMC.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/12.
//

#include "GDMC.hpp"

GDMC::GDMC(){
}

GDMC::~GDMC(){
}

std::string GDMC::getBlock(int x, int y, int z){
    std::string blockName;
    std::string url = "http://localhost:9000/blocks?x={"+std::to_string(x)+"}&y={"+std::to_string(y)+"}&z={"+std::to_string(z)+"}";
    
    try {
        blockName = session.httpGet(url);
    } catch (error) {
        return "minecraft:void_air";
    }
    
    return blockName;
}


