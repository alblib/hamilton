#ifndef __HAM_ENDIAN
#define __HAM_ENDIAN 201805

#define __HAM_LITTLE_ENDIAN 0x41424344UL
#define __HAM_BIG_ENDIAN    0x44434241UL
#define __HAM_PDP_ENDIAN    0x42414443UL
#define __HAM_ENDIAN_ORDER  ('ABCD')

namespace Hamilton {
    enum class endian: unsigned long{
        little  = __HAM_LITTLE_ENDIAN,
        big     = __HAM_BIG_ENDIAN,
        pdp     = __HAM_PDP_ENDIAN,
        native  = __HAM_ENDIAN_ORDER
    };
}

#endif

