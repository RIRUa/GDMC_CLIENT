//
//  Minecraft.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/17.
//

#ifndef Minecraft_hpp
#define Minecraft_hpp

#include <iostream>
#include <vector>
#include "Position.hpp"


namespace Minecraft {

    enum class MinecraftBlock:int {
        // 気体
        air,
        // 液体
        water,
        flowingWater,
        // 固体
        stone,
        cobbleStone
    };

    std::string getMinecraftBlockName(MinecraftBlock block, std::string addition);
    
    struct blockInfo {
        WN::Vec3 position;
        MinecraftBlock block;
        std::string addition;
        
        
        
        // コンストラクタ
        blockInfo();
        blockInfo(WN::position x, WN::position y, WN::position z, MinecraftBlock block, std::string addition);
        blockInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition);
        // デストラクタ
        ~blockInfo();
        
        // チルダ形式の情報を入手
        std::string getTildeText();
        // 情報をセットする関数
        void setInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition);
    };

    using blockInfoOf3D = std::vector<std::vector<std::vector<blockInfo>>>;
    void initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size);
    void initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size, const WN::Vec3 &center);
}


#endif /* Minecraft_hpp */
