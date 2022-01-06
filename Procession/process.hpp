//
//  process.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/25.
//

#ifndef process_hpp
#define process_hpp

#include "../Interface/GDMC.hpp"

class Process {
    Minecraft::blockInfoOf3D blocks;
    
public:
    Process();
    ~Process();
    
    bool init();
    
    Minecraft::blockInfoOf3D scan3dObject(const WN::Vec3 &Vec);
};

#endif /* process_hpp */
