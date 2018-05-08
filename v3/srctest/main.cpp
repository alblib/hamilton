//
//  main.cpp
//  Hamilton
//
//  Created by WOOHYUN RIM on 2018-05-08.
//  Copyright © 2018 Protelum Liberium. All rights reserved.
//

#include "../include/endian.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << Hamilton::endian::little == Hamilton::endian::native;
    return 0;
}
