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

        case Minecraft::MinecraftBlock::water:
            blockName += "water";
            break;
        
        case Minecraft::MinecraftBlock::flowingWater:
            blockName += "flowing_water";
            break;

        case Minecraft::MinecraftBlock::lava:
            blockName += "lava";
            break;

        case Minecraft::MinecraftBlock::flowingLava:
            blockName += "flowing_lava";
            break;
            
        case Minecraft::MinecraftBlock::stone:
            blockName += "stone";
            break;
            
        case Minecraft::MinecraftBlock::cobbleStone:
            blockName += "cobblestone";
            break;

        case Minecraft::MinecraftBlock::beacon:
            blockName += "beacon";
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
    
    int height, depth, width;
    
    for (height = 0; height < size.y; ++height) {
        object.push_back(std::vector<std::vector<Minecraft::blockInfo>>());
        for (depth = 0; depth < size.z; ++depth) {
            object[height].push_back(std::vector<Minecraft::blockInfo>());
            for (width = 0; width < size.x; ++width) {
                object[height][depth].push_back(Minecraft::blockInfo(
                                                            width,
                                                            height,
                                                            depth,
                                                            MinecraftBlock::air,
                                                            ""
                                                            )
                                       );
            }
        }
    }
    
}

void Minecraft::initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size, const WN::Vec3 &center) {
    WN::Vec3 begPosi(
                     center.x - 1 * size.x / 2,
                     center.y - 1 * size.y / 2,
                     center.z - 1 * size.z / 2
                     );
    
    object.reserve(size.y);
    for (auto &block2d : object) {
        block2d.reserve(size.z);
        for (auto &block1d : block2d) {
            block1d.reserve(size.x);
        }
    }
    
    int height, depth, width;
    
    for (height = 0; height < size.y; ++height) {
        object.push_back(std::vector<std::vector<Minecraft::blockInfo>>());
        for (depth = 0; depth < size.z; ++depth) {
            object[height].push_back(std::vector<Minecraft::blockInfo>());
            for (width = 0; width < size.x; ++width) {
                object[height][depth].push_back(Minecraft::blockInfo(
                                                            begPosi.x + width,
                                                            height,
                                                            begPosi.z + depth,
                                                            MinecraftBlock::air,
                                                            ""
                                                            )
                                       );
            }
        }
    }
    
}
