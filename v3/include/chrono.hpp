#include <chrono>
#include <type_traits>
#include <ios>
#include <iomanip>
#include <ostream>
#include <cmath>
#include <cstdint>
#include "ratio.hpp"

namespace Hamilton{
  namespace chrono{
    using ::std::chrono::duration_cast;
    using ::std::chrono::duration;
    using nanoseconds = duration<long double, ::Hamilton::ratio::nano>;
    using microseconds = duration<long double, ::Hamilton::ratio::micro>;
    using milliseconds = duration<long double, ::Hamilton::ratio::milli>;
    using seconds = duration<long double>;
    using minutes = duration<long double, ::Hamilton::ratio::ratio<60>>;
    using hours = duration<long double, ::Hamilton::ratio::ratio<3600>>;
    using days = duration<long double,std::ratio<86400>>;
    using weeks = duration<long double,std::ratio<86400*7>>;
    using gregorian_months = duration<long double,std::ratio<2629746>>;
    using gregorian_years = duration<long double,std::ratio<31556952>>;
    using julian_months = duration<long double,std::ratio<2629800>>;
    using julian_years = duration<long double,std::ratio<31557600>>;
    using synodic_months = duration<long double,std::ratio<2551443>>;
    
    template <class Duration, class CharT>
    struct period_string;
    template <class Rep, class Period, class CharT>
    struct period_string<duration<Rep, Period>, CharT>{
    
    };
    
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
            new_size = std::log10(double(op.count())*2)+2;
        }
        os << std::setprecision(new_size);
        if (std::is_same<Period, minutes::period>){
        else
            os << " " << ::Hamilton::ratio::ratio_string<Period, CharT>::symbol() << "s";
    }
  }
}
