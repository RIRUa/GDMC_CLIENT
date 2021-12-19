//
//  Minecraft.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/17.
//

#include "Minecraft.hpp"

std::string Minecraft::getMinecraftBlockName(MinecraftBlock block, std::string addition) {
    
    std::string blockName = "minecraft:";
    
    // static_cast<int>でMinecraftBlock->intのキャストを行う
    switch (block) {
        case static_cast<int>(Minecraft::MinecraftBlock::stone):
            blockName += "stone";
            break;
            
        default:
            blockName += "air";
            break;
    }
    
    if (addition != std::string()) {
        blockName += "[";
        blockName += addition;
        blockName += "]";
    }
    
    return blockName;
}
