//
//  main.cpp
//  GDMC_Client
//

#include "Procession/process.hpp"
#include <unistd.h>

int main(){
    Process p = Process();
    p.automaticWaterField(WN::Vec3(-20,0,-75));
    p.sendData();
    return 0;
}
