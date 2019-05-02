//
//  main.cpp
//  HamiltonTest
//
//  Created by WOOHYUN RIM on 2018-05-09.
//  Copyright © 2018 Protelum Liberium. All rights reserved.
//

#include <iostream>
#include "../../../include/endian.hpp"
#include "../../../include/intfixtypes.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    
#ifdef __unix__
    std::cout << "Hello, World!\n";
#endif
    //std::cout << (Hamilton::endian::native == Hamilton::endian::little);
    return 0;
}
