//
//  main.cpp
//  GDMC_Client
//

#include "Procession/process.hpp"

int main(int argc, char *argv[]){
    
    int x = std::atoi(argv[1]);
    int z = std::atoi(argv[2]);
    
    int size_x = std::atoi(argv[3]);
    int size_z = std::atoi(argv[4]);
    
    WN::Vec3 center = WN::Vec3(
                               (x + size_x) / 2,
                               220,
                               (z + size_z) / 2
                               );
    std::cout << "center position is (" << center.x << ", " << center.z << ")" << std::endl;
    Process p = Process(&center);
    p();
    
    return 0;
}
