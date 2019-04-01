#ifndef __HAM_CHRONO
#define __HAM_CHRONO 201904

#include <chrono>

#include <type_traits>

#include <ios>

#include <iomanip>

#include <ostream>

#include <cmath>

#include <cstdint>

#include <string>

#include "ratio.hpp"



namespace Hamilton {

    namespace chrono {

        using ::std::chrono::duration_cast;

        using ::std::chrono::duration;

        using picoseconds = duration<long double, ::Hamilton::ratio::pico>;

        using nanoseconds = duration<long double, ::Hamilton::ratio::nano>;

        using microseconds = duration<long double, ::Hamilton::ratio::micro>;

        using milliseconds = duration<long double, ::Hamilton::ratio::milli>;

        using seconds = duration<long double>;

        using minutes = duration<long double, ::Hamilton::ratio::ratio<60>>;

        using hours = duration<long double, ::Hamilton::ratio::ratio<3600>>;

        using days = duration<long double, std::ratio<86400>>;

        using weeks = duration<long double, std::ratio<86400 * 7>>;

        using gregorian_months = typename duration<long double, ::std::ratio<2629746>>;

        using gregorian_years = typename duration<long double, std::ratio<31556952>>;

        using julian_months = typename duration<long double, std::ratio<2629800>>;

        using julian_years = typename duration<long double, std::ratio<31557600>>;

        using synodic_months = typename duration<long double, std::ratio<2551443>>;

        //

        template <class Duration, class CharT = char>

        struct period_string;

        template <class Rep, class Period, class CharT>

        struct period_string<duration<Rep, Period>, CharT> {

            static std::basic_string<CharT> symbol()
            
            {

                return std::basic_string<CharT>(1, CharT('[')) +

                    std::to_string(double(Ratio::num) / double(Ratio::den))
                    
                    + CharT('s]');

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, picoseconds::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return ::Hamilton::ratio::ratio_string<picoseconds::period, CharT>::symbol() + CharT('s');

            }

        };
        

        template <class Rep, class CharT>

        struct period_string<duration<Rep, nanoseconds::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return ::Hamilton::ratio::ratio_string<nanoseconds::period, CharT>::symbol() + CharT('s');

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, microseconds::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return ::Hamilton::ratio::ratio_string<microseconds::period, CharT>::symbol() + CharT('s');

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, milliseconds::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return ::Hamilton::ratio::ratio_string<milliseconds::period, CharT>::symbol() + CharT('s');

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, seconds::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return std::basic_string<CharT>(1, CharT('s'));

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, minutes::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return std::basic_string<CharT>{CharT('m'), CharT('i'), CharT('n')};

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, hours::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return std::basic_string<CharT>(1, CharT('h'));

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, days::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return std::basic_string<CharT>(1, CharT('d'));

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, weeks::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return "weeks";

            }

        };


        template <class Rep, class CharT>

        struct period_string<duration<Rep, julian_years::period>, CharT> {

            static std::basic_string<CharT> symbol()

            {

                return "Julian years";

            }

        };





    }

}



template <class CharT, class Traits, class Rep, class Period>

std::basic_ostream<CharT, Traits>& operator <<

(std::basic_ostream<CharT, Traits>& os, const Hamilton::chrono::duration<Rep, Period>& op) {

    auto flags = os.flags();

    std::streamsize size = os.precision();

    double new_size = size;

    if (std::is_integral<Rep>::value) {

        if (Period::den == 1 || 1000 % Period::den == 0

            || 1000000000L % Period::den == 0

            || 1000000000000000000LL % Period::den == 0) {

            os.flags(flags ^ (flags ? flags & std::ios_base::fixed : 0)); // make fixed=false;

        }

        os << std::setprecision(std::log10(double(op.count()) * 2) + 2);

    }

    os << std::setprecision(new_size);

    os << op.count() << " " << Hamilton::chrono::period_string<Hamilton::chrono::duration<Rep, Period>, CharT>::symbol();

    os.flags(flags);

    os << std::setprecision(size);

    return os;

}

#endif
