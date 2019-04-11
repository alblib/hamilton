//
//  main.cpp
//  HamiltonTest
//
//  Created by WOOHYUN RIM on 2018-05-09.
//  Copyright © 2018 Protelum Liberium. All rights reserved.
//

#include <iostream>
#include "../../../include/endian.hpp"
//#include "../../../include/intfixtypes.hpp"
#include "../../../include/chrono.hpp"
#include "../../../include/ratio.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << (Hamilton::endian::native == Hamilton::endian::little);
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();
    std::cout << (t1-(t2-t1)).time_since_epoch();
    return 0;
}
