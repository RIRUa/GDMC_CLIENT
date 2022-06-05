//
//  process.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/25.
//

#ifndef process_hpp
#define process_hpp

#include "../untouchable/GDMC.hpp"
#include "gimmick.hpp"
#include "building.hpp"
#include "interior.hpp"
#include <memory>

// WFCの可能性を入れる配列の型の定義
using possibilities = std::vector< std::vector<bool> >;


class Process {
    // width, height, depth
    const WN::Vec3 area = WN::Vec3(200, 30, 200);
    // 地面の高さ（+1すると空気）
    const int groundHeight = 5;
    
    // 送信先の中心座標
    WN::Vec3 *sendPosi;
    
    std::shared_ptr< Minecraft::blockInfoOf3D > createArea;
    std::shared_ptr< possibilities > possibility;
    
    std::string commands;
    
public:
    Process(WN::Vec3 *sendPosi);
    ~Process();
    
    bool init();
    bool sendData();
    
    void createHouse1(const WN::Vec3 &center);
    void createHouse2(const WN::Vec3 &center);
    void createStreetlight1(const WN::Vec3 &center);
    void createStreetlight2(const WN::Vec3 &center);
    void createAutomaticWaterField(const WN::Vec3 &center);
    void createFountain(const WN::Vec3 &center);
    void createPigBurner(const WN::Vec3 &center);
    
    void createGateBuilding(const WN::Vec3 &center);
};

#endif /* process_hpp */
