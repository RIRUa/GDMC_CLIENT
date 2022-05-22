//
//  GDMC.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/12.
//

#include "GDMC.hpp"

GDMC::GDMC(){
    URLSession();
}

GDMC::~GDMC(){
}

std::string GDMC::getBlock(int x, int y, int z){
    std::string blockName;
    std::string url = "http://localhost:9000/blocks?x="+std::to_string(x)+"&y="+std::to_string(y)+"&z="+std::to_string(z);
    
    try {
        blockName = this->httpGet(url);
    } catch (error) {
        return "minecraft:void_air";
    }
    
    return blockName;
}

std::string GDMC::getBlockMoreInfo(int x, int y, int z){
    std::string blockName;
    std::string url = "http://localhost:9000/blocks?x="+std::to_string(x)+"&y="+std::to_string(y)+"&z="+std::to_string(z)+"&includeState=true";
    
    try {
        blockName = this->httpGet(url);
    } catch (error) {
        return "minecraft:void_air";
    }
    
    return blockName;
}

std::string GDMC::setBlock(const Minecraft::blockInfo &info) {
    std::string result;
    std::string url = "http://localhost:9000/blocks?x="+std::to_string(info.position.x)+"&y="+std::to_string(info.position.y)+"&z="+std::to_string(info.position.z);
    
    try {
        result = this->httpPut(url, Minecraft::getMinecraftBlockName(info.block, info.addition));
    } catch (error) {
        return "";
    }
    
    return result;
}

std::string GDMC::setBlocks(const WN::Vec3 center, const Minecraft::blockInfoOf3D &info) {
    std::string result;
    std::string url = "http://localhost:9000/blocks?x="+std::to_string(center.x)+"&y="+std::to_string(center.y)+"&z="+std::to_string(center.z);
    std::string blocks = "";
    int i = 0;
    
    for (auto &block2d : info) {
        for (auto &block1d : block2d) {
            for (auto block : block1d) {
                i++;
                if (i >= 4000) {
                    try {
                        result += this->httpPut(url, blocks);
                    } catch (error) {
                        return "";
                    }
                    i = 0;
                    blocks = "";
                }
                blocks += block.getTildeText();
            }
        }
    }
    
    try {
        result += this->httpPut(url, blocks);
    } catch (error) {
        return "";
    }
    
    return result;
}
