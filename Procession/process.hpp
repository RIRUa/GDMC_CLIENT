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


class Process {
    // width, height, depth
    const WN::Vec3 area = WN::Vec3(400, 30, 400);
    // 地面の高さ（+1すると空気）
    const int groundHeight = 5;
    
    // 送信先の中心座標
    WN::Vec3 *sendPosi;
    
    std::shared_ptr< Minecraft::blockInfoOf3D > createArea;
    
    std::string commands;
    
public:
    Process(WN::Vec3 *sendPosi);
    ~Process();
    
    // -MARK: 実行箇所
    void operator()();
    
    
private:
    bool init();
    bool sendData();
    
    void createHouse1(const WN::Vec3 &center, const WN::direction &facing);
    void createHouse2(const WN::Vec3 &center, const WN::direction &facing);
    void createStreetlight1(const WN::Vec3 &center, const WN::direction &facing);
    void createStreetlight2(const WN::Vec3 &center, const WN::direction &facing);
    void createAutomaticWaterField(const WN::Vec3 &center, const WN::direction &facing);
    void createFountain(const WN::Vec3 &center, const WN::direction &facing);
    void createPigBurner(const WN::Vec3 &center, const WN::direction &facing);
    void createGateBuilding(const WN::Vec3 &center, const WN::direction &facing);
    void createBridge(const WN::Vec3 &center, const WN::direction &facing);
};

#endif /* process_hpp */
