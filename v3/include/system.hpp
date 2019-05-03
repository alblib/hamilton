#ifndef __HAM_SYSTEM
#define __HAM_SYSTEM 201905

#if (defined(__APPLE__) && defined(__MACH__)) || defined(__FreeBSD__)
#define __HAM_SYSTEM_APPLE
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#elif defined(__unix__) || defined(__linux__)
#define __HAM_SYSTEM_LINUX
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#define __HAM_SYSTEM_WINDOWS
#include <windows.h>
#else
#define __HAM_SYSTEM_UNKNOWN
#endif

#include <ostream>
#include "ratio.hpp"

// MARK: - Byte Size Type

namespace Hamilton{

    namespace system{
        
        template <class SizeType = size_t, class Ratio = ::Hamilton::ratio::ratio<1>>
        class basic_byte_size{
        public:
            using size_type = SizeType;
            using ratio = Ratio;
            
            SizeType value;
            
            constexpr basic_byte_size(): value(){}
            constexpr basic_byte_size(const size_type& op): value(op){}
            constexpr basic_byte_size(size_type&& op): value(op){}
            
            constexpr basic_byte_size(const basic_byte_size&) = default;
            basic_byte_size(basic_byte_size&&) = default;
            
            template <class SizeType2, class Ratio2>
            explicit constexpr basic_byte_size(const basic_byte_size<SizeType2,Ratio2>& op):value(static_cast<SizeType>(static_cast<long double>(static_cast<SizeType2>(op))*Ratio2::num*Ratio::den / Ratio2::den / Ratio::num)){}
            
            constexpr size_type byte_count () const {return value * Ratio::num / Ratio::den;}
            
            constexpr basic_byte_size& operator = (const basic_byte_size&) = default;
            basic_byte_size& operator = (basic_byte_size&&) = default;
            
            constexpr bool operator < (const basic_byte_size& op){return value < op.value;}
            constexpr bool operator <= (const basic_byte_size& op){return value <= op.value;}
            constexpr bool operator > (const basic_byte_size& op){return value > op.value;}
            constexpr bool operator >= (const basic_byte_size& op){return value >= op.value;}
            constexpr bool operator == (const basic_byte_size& op){return value == op.value;}
            constexpr bool operator != (const basic_byte_size& op){return value != op.value;}
            
        };
        using byte_size = basic_byte_size<>;
        using bit_size = basic_byte_size<size_t, ::Hamilton::ratio::ratio<1,8>>;
        using kibibyte_size = basic_byte_size<long double, ::Hamilton::ratio::kibi>;
        using mebibyte_size = basic_byte_size<long double, ::Hamilton::ratio::mebi>;
        using gibibyte_size = basic_byte_size<long double, ::Hamilton::ratio::gibi>;
        using tebibyte_size = basic_byte_size<long double, ::Hamilton::ratio::tebi>;
        using pebibyte_size = basic_byte_size<long double, ::Hamilton::ratio::pebi>;
        using exbibyte_size = basic_byte_size<long double, ::Hamilton::ratio::exbi>;
    }
    
    namespace literals{
        namespace system_literals{
            constexpr ::Hamilton::system::byte_size operator""_B(unsigned long long int _data){
                return ::Hamilton::system::byte_size(static_cast<size_t>(_data));
            }
            constexpr ::Hamilton::system::bit_size operator""_b(unsigned long long int _data){
                return ::Hamilton::system::bit_size(static_cast<size_t>(_data));
            }
            constexpr ::Hamilton::system::kibibyte_size operator""_KiB(unsigned long long int _data){
                return ::Hamilton::system::kibibyte_size(static_cast<size_t>(_data));
            }
            constexpr ::Hamilton::system::mebibyte_size operator""_MiB(unsigned long long int _data){
                return ::Hamilton::system::mebibyte_size(static_cast<size_t>(_data));
            }
            constexpr ::Hamilton::system::gibibyte_size operator""_GiB(unsigned long long int _data){
                return ::Hamilton::system::gibibyte_size(static_cast<size_t>(_data));
            }
            constexpr ::Hamilton::system::tebibyte_size operator""_TiB(unsigned long long int _data){
                return ::Hamilton::system::tebibyte_size(static_cast<size_t>(_data));
            }
            constexpr ::Hamilton::system::pebibyte_size operator""_PiB(unsigned long long int _data){
                return ::Hamilton::system::pebibyte_size(static_cast<size_t>(_data));
            }
            constexpr ::Hamilton::system::exbibyte_size operator""_EiB(unsigned long long int _data){
                return ::Hamilton::system::exbibyte_size(static_cast<size_t>(_data));
            }
        }
    }
}
        
template <class _CharT, class _Traits, class SizeType, class Ratio>
std::basic_ostream<_CharT,_Traits>& operator << (std::basic_ostream<_CharT,_Traits>& os, const Hamilton::system::basic_byte_size<SizeType, Ratio>& op)
{
    using namespace ::Hamilton::ratio;
    return os << op.value << " " << ratio_string<Ratio,_CharT>::symbol() << "B";
}

template <class _CharT, class _Traits, class SizeType>
std::basic_ostream<_CharT,_Traits>& operator << (std::basic_ostream<_CharT,_Traits>& os, const Hamilton::system::basic_byte_size<SizeType, ::Hamilton::ratio::ratio<1,8>>& op)
{
    return os << op.value << " " << "b";
}

namespace Hamilton{
    namespace system{
        template <class SizeType = size_t>
        class autoscale_byte_size: public basic_byte_size<SizeType>{
        public:
            constexpr autoscale_byte_size() = default;
            constexpr autoscale_byte_size(const autoscale_byte_size&) = default;
            
            
            constexpr autoscale_byte_size(const SizeType& bytes): basic_byte_size<SizeType>(bytes){}
            constexpr autoscale_byte_size(SizeType&& bytes): basic_byte_size<SizeType>(bytes){}
        };
        
        
        template <class ByteSize>
        autoscale_byte_size<typename ByteSize::size_type> autoscale_byte_size_cast(const ByteSize& op){
            return autoscale_byte_size<typename ByteSize::size_type>(op.byte_count());
        }
    }
}

template <class _CharT, class _Traits, class SizeType>
std::basic_ostream<_CharT,_Traits>& operator << (std::basic_ostream<_CharT,_Traits>& os, const Hamilton::system::autoscale_byte_size<SizeType>& op)
{
    long double data = op.byte_count();
    unsigned long long unit = 1;
    while(data >= 1000.0){
        data /= 1024;
        unit *= 1024;
    }
    switch (unit) {
        case ::Hamilton::ratio::kibi::num:
            return os << data << " KiB";
        case ::Hamilton::ratio::mebi::num:
            return os << data << " MiB";
        case ::Hamilton::ratio::gibi::num:
            return os << data << " GiB";
        case ::Hamilton::ratio::tebi::num:
            return os << data << " TiB";
        case ::Hamilton::ratio::pebi::num:
            return os << data << " PiB";
        case ::Hamilton::ratio::exbi::num:
            return os << data << " EiB";
            
        default:
            return os << op.byte_count() << " B";
    }
}

#endif
