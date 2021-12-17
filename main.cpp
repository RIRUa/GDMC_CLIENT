//
//  main.cpp
//  GDMC_Client
//
//  Created by 渡辺奈央騎 on 2021/12/03.
//

#include "API/URLSession.hpp"

int main(){
    
    URLSession u;
    
    auto resp = u.httpDelete("http://localhost:1323/users/1");
    std::cout <<resp;
    
    int a[3][3][3];
    
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            
        }
    }
    
//    auto resp = u.httpPut("http://localhost:9000/blocks?x=0&y=105&z=0", "minecraft:tnt");
//
//    std::cout <<resp;
//
//    size_t t;
    
    return 0;
}
