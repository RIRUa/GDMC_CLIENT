//
//  Minecraft.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/17.
//

#include "Minecraft.hpp"

std::string Minecraft::getMinecraftBlockName(MinecraftBlock block, std::string addition) {
    
    std::string blockName = "minecraft:";
    
    switch (block) {
        case Minecraft::MinecraftBlock::air:
            blockName += "air";
            break;
            
        case Minecraft::MinecraftBlock::stone:
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

Minecraft::blockInfo::blockInfo(){}
Minecraft::blockInfo::~blockInfo(){}

Minecraft::blockInfo::blockInfo(WN::position x, WN::position y, WN::position z, MinecraftBlock block, std::string addition) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->block = block;
    this->addition = addition;
}

Minecraft::blockInfo::blockInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition) {
    this->position = vec;
    this->block = block;
    this->addition = addition;
}

std::string Minecraft::blockInfo::getTildeText() {
    
    std::string pos = "~";
    
    pos += std::to_string(this->position.x);
    pos += " ~";
    pos += std::to_string(this->position.y);
    pos += " ~";
    pos += std::to_string(this->position.z);
    pos += " ";
    
    pos += Minecraft::getMinecraftBlockName(block, addition);
    
    return pos;
}
