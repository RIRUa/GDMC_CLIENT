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
    
    blockName += "\n";
    
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

void Minecraft::blockInfo::setInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition) {
    this->position = vec;
    this->block = block;
    this->addition = addition;
}

void Minecraft::initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size) {
    object.reserve(size.y);
    for (auto &block2d : object) {
        block2d.reserve(size.z);
        for (auto &block1d : block2d) {
            block1d.reserve(size.x);
        }
    }
    
    for (int i = 0; i < size.y; ++i) {
        object.push_back(std::vector<std::vector<Minecraft::blockInfo>>());
        for (int j = 0; j < size.z; ++j) {
            object[i].push_back(std::vector<Minecraft::blockInfo>());
            for (int k = 0; k < size.x; ++k) {
                object[i][j].push_back(Minecraft::blockInfo(
                                                            k,
                                                            i,
                                                            j,
                                                            MinecraftBlock::air,
                                                            ""
                                                            )
                                       );
            }
        }
    }
    
    
}
