#include <chrono>
#include <type_traits>
#include <ios>
#include <ostream>
#include <cmath>
#include "ratio.hpp"

namespace Hamilton{
  namespace chrono{
    using ::std::chrono::duration;
    template <class CharT, class Traits, class Rep, class Period>
    std::basic_ostream<CharT, Traits>& operator << 
      (std::basic_ostream<CharT, Traits>& os, const duration<Rep, Period>& op){
        bool fixed = os.flags() | std::ios_base::fixed;
        std::streamsize size = os.precision();
        bool new_fixed = fixed;
        double new_size = size;
        if (std::is_integral<Rep>::value){
            if (Period::den==1 || 1000%Period::den == 0 
              || 1000000000L%Period::den == 0 
              || 1000000000000000000LL%Period::den == 0){
                new_fixed = false;
            }
            new_size = std::log10(double(op.count()))+3;
        }
        double count = std::duration_cast<std::chrono::duration<double>>(op).count();
        if (count < 60){
            
            int unit = int(-std::floor((std::log10(count)+1)/3)+0.1);
        }else{
        }
    }
  }
}
