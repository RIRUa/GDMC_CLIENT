//
//  main.cpp
//  GDMC_Client
//

#include "Procession/process.hpp"

int main(){
    
    WN::Vec3 center = WN::Vec3(0,0,0);
    Process p = Process(&center);
    p.createGateBuilding(WN::Vec3(0,0,0));
    p.sendData();
    
    return 0;
}
