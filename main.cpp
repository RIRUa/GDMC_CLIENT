//
//  main.cpp
//  GDMC_Client
//

#include "Procession/process.hpp"

int main(){
    
    Process p = Process();
    p.createHouse1(WN::Vec3(0,0,0));
    p.sendDatas();
    
    return 0;
}
