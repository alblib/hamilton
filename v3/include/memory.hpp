#ifndef __HAM_MEMORY
#define __HAM_MEMORY 201905

#if (defined(__APPLE__) && defined(__MACH__)) || defined(__FreeBSD__)

#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/vmmeter.h>

#elif defined(__unix__) || defined(__linux__)

#include <unistd.h>

namespace Hamilton {
    namespace memory {
        
        template <class SizeType = unsigned long long>
        struct memory_manager_basic{
            using size_type = SizeType;
            size_type total_physical_memory(){
                size_type pages = sysconf(_SC_PHYS_PAGES);
#ifdef _SC_PAGESIZE
                size_type page_size = sysconf(_SC_PAGESIZE);
#else
                size_type page_size = sysconf(_SC_PAGE_SIZE);
#endif
                return pages * page_size;
            }
            size_type available_physical_memory(){
                size_type pages = sysconf(_SC_AVPHYS_PAGES);
#ifdef _SC_PAGESIZE
                size_type page_size = sysconf(_SC_PAGESIZE);
#else
                size_type page_size = sysconf(_SC_PAGE_SIZE);
#endif
                return pages * page_size;
            }
        };
        using memory_manager = memory_manager_basic<>;

    }
}

#elif defined(_WIN32) || defined(_WIN64)

#include <windows.h>

namespace Hamilton {
    namespace memory {
        
        template <class SizeType = unsigned long long>
        struct memory_manager_basic{
            using size_type = SizeType;
            size_type total_physical_memory(){
                MEMORYSTATUSEX status;
                status.dwLength = sizeof(status);
                GlobalMemoryStatusEx(&status);
                return status.ullTotalPhys;
            }
            size_type available_physical_memory(){
                MEMORYSTATUSEX status;
                status.dwLength = sizeof(status);
                GlobalMemoryStatusEx(&status);
                return status.ullAvailPhys;
            }
        };
        using memory_manager = memory_manager_basic<>;
    }
}

#endif

#endif
