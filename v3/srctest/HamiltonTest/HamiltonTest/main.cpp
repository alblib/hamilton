//
//  main.cpp
//  HamiltonTest
//
//  Created by WOOHYUN RIM on 2018-05-09.
//  Copyright © 2018 Protelum Liberium. All rights reserved.
//

#include <iostream>
#include "../../../include/endian.hpp"
<<<<<<< HEAD
#include "../../../include/intfixtypes.hpp"
#include "../../../include/memory.hpp"
#include "../../../include/system.hpp"
=======
//#include "../../../include/intfixtypes.hpp"
#include "../../../include/chrono.hpp"
#include "../../../include/ratio.hpp"
#include "../../../include/cl_inttypes.hpp"
>>>>>>> feature/ratio_chrono_units

int main(int argc, const char * argv[]) {
    // insert code here...
    
#ifdef __unix__
    std::cout << "Hello, World!\n";
<<<<<<< HEAD
#endif
    //std::cout << (Hamilton::endian::native == Hamilton::endian::little);
    
    using namespace Hamilton::literals::system_literals;
    
    std::cout << 3432952_bytes;
    
=======
    std::cout << (Hamilton::endian::native == Hamilton::endian::little);
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = std::chrono::steady_clock::now();
    std::cout << (t1-(t2-t1)).time_since_epoch() << std::endl;
    std::cout << t1 << std::endl;
>>>>>>> feature/ratio_chrono_units
    return 0;
}
