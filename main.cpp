//
//  main.cpp
//  GDMC_Client
//

#include "Procession/process.hpp"

int main(){
    
    Process p = Process();
    p.createAutomaticWaterField(WN::Vec3(10,0,30));
    p.sendData();
    
    return 0;
}
