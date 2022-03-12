//
//  process.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/25.
//

#ifndef process_hpp
#define process_hpp

#include "../untouchable/GDMC.hpp"
#include <memory>

// WFCの可能性を入れる配列の型の定義
using possibilities = std::vector< std::vector<bool> >;

// 家の縦横のサイズを保存する構造体
struct houseSize {
    unsigned int width;
    unsigned int depth;
};



class Process {
    // width, height, depth
    const WN::Vec3 area = WN::Vec3(40, 30, 40);
    // 地面の高さ（+1すると空気）
    const int groundHeight = 5;
    
    std::shared_ptr< Minecraft::blockInfoOf3D > createArea;
    std::shared_ptr< possibilities > possibility;
    
public:
    Process();
    ~Process();
    
    bool init();
    bool sendDatas();
    
    void createHouse1(const WN::Vec3 &center);
};

#endif /* process_hpp */
