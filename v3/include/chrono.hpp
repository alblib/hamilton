#ifndef __HAM_CHRONO
#define __HAM_CHRONO 201904

#include <chrono>

#include <type_traits>

#include <ios>

#include <iomanip>

#include <ostream>

#include <cmath>

#include <string>

#include <vector>

#include "ratio.hpp"

#include <ctime>

// MARK: -

// MARK: Aliasing class duration and its relatives

namespace Hamilton {

    namespace chrono {

        using ::std::chrono::duration_cast;

        using ::std::chrono::duration;

        /** std::chrono::duration with rep = long double and period = 1e-12 s. */
        using picoseconds = duration<long double, ::Hamilton::ratio::pico>;

        /** std::chrono::duration with rep = long double and period = 1e-9 s. */
        using nanoseconds = duration<long double, ::Hamilton::ratio::nano>;

        /** std::chrono::duration with rep = long double and period = 1e-6 s. */
        using microseconds = duration<long double, ::Hamilton::ratio::micro>;

        /** std::chrono::duration with rep = long double and period = 1/1000 s. */
        using milliseconds = duration<long double, ::Hamilton::ratio::milli>;

        /** std::chrono::duration with rep = long double and period = 1 s. */
        using seconds = duration<long double>;

        /** std::chrono::duration with rep = long double and period = 1 min. */
        using minutes = duration<long double, ::Hamilton::ratio::ratio<60>>;

        /** std::chrono::duration with rep = long double and period = 1 hr. */
        using hours = duration<long double, ::Hamilton::ratio::ratio<3600>>;
        
        /** std::chrono::duration with rep = long double and period = 1 day = 86400 s. */
        using days = duration<long double, ::Hamilton::ratio::ratio<86400>>;

        /** std::chrono::duration with rep = long double and period = 7 days. */
        using weeks = duration<long double, ::Hamilton::ratio::ratio<86400 * 7>>;

        /** std::chrono::duration with rep = long double and period = 1/12 of an average Gregorian year. */
        using gregorian_months = duration<long double, ::Hamilton::ratio::ratio<2629746>>;

        /** std::chrono::duration with rep = long double and period = 1 average Gregorian year = 365.2425 days. */
        using gregorian_years = duration<long double, ::Hamilton::ratio::ratio<31556952>>;

        /** std::chrono::duration with rep = long double and period = 1/12 of an average Julian year. */
        using julian_months = duration<long double, ::Hamilton::ratio::ratio<2629800>>;

        /** std::chrono::duration with rep = long double and period = 1 average Julian year = 365.25 days. */
        using julian_years = duration<long double, std::ratio<31557600>>;
        
        /** std::chrono::duration with rep = long double and period = average one cycle of the moon phase. */
        using synodic_months = duration<long double, ::Hamilton::ratio::ratio<2551443>>;

        // MARK: - Defining class period_string

        /*!
         \class Hamilton::chrono::period_string<Duration, CharT>
         \brief A template class contains a string representing Hamilton::chrono::duration aliases.
         
         Hamilton::chrono::period_string<Duration, CharT = char> is a template class contains the string
         representing each period defined in namespace Hamilton::chrono as duration aliases.
         The smallest defined unit is the picosecond, and the largest unit is the Julian year.
         Each unit symbol here follows the standard such as SI etc.
         Note that Gregorian average years are represented by 'yr',
         while a Julian year is represented by standard symbol 'a'.
         */
        
        template <class Duration, class CharT = char>

        struct period_string;

        template <class Rep, class Period, class CharT>

        struct period_string<duration<Rep, Period>, CharT> {

            static std::basic_string<CharT> symbol()
            
            {

                return std::basic_string<CharT>(1, CharT('[')) +

                    std::to_string(double(Period::num) / double(Period::den))
                    
                    + "s]";

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

                return "a";

            }

        };
        
        
        template <class Rep, class CharT>
        
        struct period_string<duration<Rep, gregorian_years::period>, CharT> {
            
            static std::basic_string<CharT> symbol()
            
            {
                
                return "yr";
                
            }
            
        };
        
    }
    
}


// MARK: - Printing class duration to std::ostream


template <class CharT, class Traits, class Rep, class Period>

std::basic_ostream<CharT, Traits>& operator <<

(std::basic_ostream<CharT, Traits>& os, const Hamilton::chrono::duration<Rep, Period>& op) {
    
    auto flags = os.flags();
    
    auto size = os.precision();
    
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
    
    os << op.count() << Hamilton::chrono::period_string<Hamilton::chrono::duration<Rep, Period>, CharT>::symbol();
    
    os.flags(flags);
    
    os.precision(size);
    
    return os;
    
}

// MARK: -

// MARK: Defining class autoscale_duration

namespace Hamilton{
    
    namespace chrono{
        
        template <class Rep, class MinimumPeriod>
        class autoscale_duration: public duration<Rep, MinimumPeriod>
        {
            
        public:
            
            using base_type = duration<Rep, MinimumPeriod>;
            
            constexpr autoscale_duration() = default;
            
            constexpr autoscale_duration(const autoscale_duration&) = default;
            
            autoscale_duration(autoscale_duration&&) = default;
            
            constexpr autoscale_duration& operator = (const autoscale_duration&) = default;
            
            autoscale_duration& operator = (autoscale_duration&&) = default;
            
            constexpr autoscale_duration(const duration<Rep, MinimumPeriod>& op)
            : duration<Rep, MinimumPeriod>(op){}
            
            autoscale_duration(duration<Rep, MinimumPeriod>&& op)
            : duration<Rep, MinimumPeriod>(op){}
            
            template <class Rep2, class Period2>
            constexpr explicit autoscale_duration(const duration<Rep2, Period2>& op)
            : duration<Rep, MinimumPeriod>(op){}
            
            template <class Rep2, class Period2>
            constexpr explicit autoscale_duration(const autoscale_duration<Rep2, Period2>& op)
            : duration<Rep, MinimumPeriod>(op){}
            
            constexpr operator duration<Rep, MinimumPeriod> () const{
                return *this;
            }
            
            /** Converts this autoscale_duration to its base class std::chrono::duration object. */
            constexpr duration<Rep, MinimumPeriod> base_duration() const{
                return *this;
            }
            
        };
        
        template <class FromDuration>
        constexpr autoscale_duration<typename FromDuration::rep, typename FromDuration::period>
        autoscale_duration_cast(const FromDuration& from)
        {
            
            return autoscale_duration<typename FromDuration::rep, typename FromDuration::period>(from);
            
        }
        
    }
    
}

// MARK: - Printing autoscale_duration

template <class CharT, class Traits, class Rep, class Period>

std::basic_ostream<CharT, Traits>& operator <<

(std::basic_ostream<CharT, Traits>& os, Hamilton::chrono::autoscale_duration<Rep, Period> op) {
    
    using namespace Hamilton::chrono;
    
    const bool fixed = os.flags() & std::ios_base::fixed;
    
    const auto size = os.precision();
    
    long double new_size = size;
    
    const duration<Rep, Period> epsilon = op / std::powl(10, new_size) / 2;
    
    bool printed_sth = false, hr_printed = false, yr_printed = false, d_printed = false;
    
    if (op.count() < 0) {
        
        os << "-";
        
        op = -op;
        
    }
    
    // Years
    
    auto years = autoscale_duration_cast<julian_years>(op);
    
    if (years.count() >= 1) {
        
        printed_sth = true;
        
        yr_printed = true;
        
        new_size -= std::log10l(years.count());
        
        if (new_size <= 0) {
            
            os << years.base_duration();
            
            // return
            
        }
        
        else{
        
            auto flryr = duration_cast<duration<std::intmax_t,julian_years::period>>(op);
            
            auto flryr1 = flryr; ++flryr;
            
            if ((op - flryr1) >= -epsilon) flryr = flryr1;
            
            os << flryr;
            
            op -= flryr;
            
        }
        
    }
    
    // Days
    
    auto days = duration_cast<duration<std::intmax_t, days::period>>(op);
    
    auto days1 = days; ++days1;
    
    if ((op - days1) >= -epsilon) days = days1;
    
    if (new_size > 0 && (days.count() >= 1 || (printed_sth && fixed) || (yr_printed && op.count() > 0))) {
        
        if (printed_sth) os << " ";
        
        else printed_sth = true;
        
        d_printed = true;
        
        new_size -= std::log10l(days.count());
        
        os << days;
        
        op -= days;
        
    }
    
    // Hours
    
    auto hrs = duration_cast<duration<std::intmax_t, hours::period>>(op);
    
    auto hrs1 = hrs; ++hrs1;
    
    if ((op - hrs1) >= -epsilon) hrs = hrs1;
    
    if (new_size > 0 && (hrs.count() >= 1 || (printed_sth && fixed) || (d_printed && op.count() > 0))) {
        
        if (printed_sth) os << " ";
        
        else printed_sth = true;
        
        hr_printed = true;
        
        new_size -= std::log10l(hrs.count());
        
        os << hrs;
        
        op -= hrs;
        
    }
    
    // Minutes
    
    auto mins = duration_cast<duration<std::intmax_t, minutes::period>>(op);
    
    auto mins1 = mins; ++mins1;
    
    if ((op - mins1) >= -epsilon) mins = mins1;
    
    if (new_size > 0 && (mins.count() >= 1 || (printed_sth && fixed) || (hr_printed && op.count() > 0))) {
        
        if (printed_sth) os << " ";
        
        else printed_sth = true;
        
        new_size -= std::log10l(mins.count());
        
        os << mins;
        
        op -= mins;
        
    }
    
    if (op.count() < 0) op = duration<Rep, Period>(0);
    
    // Seconds
    
    if (new_size > 0){
        
        os.precision(new_size);
        
        auto secs = duration_cast<seconds>(op);
        
        if (!printed_sth){
            
            switch (int((std::log10l(secs.count()) + 12) + 3)){
                    
                case 4:
                    
                    os << secs;
                    
                    break;
                    
                case 3:
                    
                    os << duration_cast<milliseconds>(op);
                    
                    break;
                    
                case 2:
                    
                    os << duration_cast<microseconds>(op);
                    
                    break;
                    
                case 1:
                    
                    os << duration_cast<nanoseconds>(op);
                    
                    break;
                    
                default:
                    
                    os << duration_cast<nanoseconds>(op);
                    
            }
            
        } else if (fixed) {
            
            os << " ";
            
            os << secs;
            
        }
        
    }
    
    os.precision(size);
    
    return os;
    
}


// MARK: - Printing std::chrono::time_point<TrivialClock>

namespace Hamilton{
    
    namespace chrono{
        
        using ::std::chrono::time_point;
        
    }
    
}

template <class CharT, class Traits, class TrivialClock>

std::basic_ostream<CharT, Traits>& operator <<

(std::basic_ostream<CharT, Traits>& os, const Hamilton::chrono::time_point<TrivialClock>& op) {
    
    std::time_t tym = TrivialClock::to_time_t(op);
    
    return os << std::ctime(&tym);
    
}


namespace Hamilton{
    
    // MARK: - Defining class chronometer and its relatives
        
    namespace chrono{

        using steady_high_resolution_clock = typename ::std::conditional<::std::chrono::high_resolution_clock::is_steady, typename ::std::chrono::high_resolution_clock, typename ::std::chrono::steady_clock>::type;

        template <class TrivialClock>

        class basic_chronometer {

        public:

            using time_point = typename TrivialClock::time_point;

            using duration = typename TrivialClock::duration;

        private:

            ::std::vector<duration> _data;
            
            time_point epoch;
            
            bool _stop = true;

        public:

            void clear() { _data.clear(); _stop = true; epoch = time_point::min(); }
            
            constexpr basic_chronometer(): _data(), _stop(true), epoch(time_point::min()) {}

            /** Start or resume chronometer. */
            time_point start() {
                
                if (_stop) {
                    
                    _stop = false;
                    
                    epoch = _data.empty() ? TrivialClock::now() : TrivialClock::now() - _data.back();
                
                }
                    
                return epoch;

            }
            
            inline duration elapsed_time() const{
                
                return TrivialClock::now() - epoch;
                
            }

            duration lap() {

                _data.push_back(elapsed_time());

                return _data.back();

            }
            
            inline ::std::vector<duration> lap_list() const{
                
                return _data;
                
            }
            
            duration stop() {
                
                _stop = true;
                
                return lap();
                
            }

        };

        using chronometer = basic_chronometer<steady_high_resolution_clock>;

    }

    // MARK: - namespace literals

    namespace literals {
        
        namespace chrono_literals {

            using namespace ::std::literals::chrono_literals;

        }

    }

}



#endif
