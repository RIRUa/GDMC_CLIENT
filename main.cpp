//
//  main.cpp
//  GDMC_Client
//

#include "Procession/process.hpp"

int main(){
    
    WN::Vec3 center = WN::Vec3(0,220,0);
    Process p = Process(&center);
    p();
    
    return 0;
}
