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

namespace Hamilton{

    namespace system{
        
        template <class SizeType = size_t, class Ratio = ::Hamilton::ratio::ratio<1>>
        class basic_byte_size{
        public:
            using size_type = SizeType;
        private:
            SizeType _data;
        public:
            constexpr basic_byte_size(): _data(){}
            constexpr basic_byte_size(const size_type& op): _data(op){}
            constexpr basic_byte_size(size_type&& op): _data(op){}
            
            template <class SizeType2, class Ratio2>
            explicit constexpr basic_byte_size(const basic_byte_size<SizeType2,Ratio2>& op){
                
            }
            
            operator size_type () const {return _data;}
            
        };
        using byte_size = basic_byte_size<>;
    }
    
    namespace literals{
        namespace system_literals{
            constexpr ::Hamilton::system::byte_size operator""_bytes(unsigned long long int _data){
                return ::Hamilton::system::byte_size(static_cast<size_t>(_data));
            }
        }
    }
}
        
template <class _CharT, class _Traits, class SizeType>
std::basic_ostream<_CharT,_Traits>& operator << (std::basic_ostream<_CharT,_Traits>& os, const Hamilton::system::basic_byte_size<SizeType>& op)
{
    using namespace ::Hamilton::ratio;
    SizeType data = op, unit = 1;
    while (data > 1000){
        data /= 1024;
        unit *= 1024;
    }
    os << static_cast<double>(static_cast<SizeType>(op)) / unit << " " << ratio_string<ratio<unit>,_CharT>::symbol() << "B";
}




#endif
