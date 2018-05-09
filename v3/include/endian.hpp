#ifndef __HAM_ENDIAN
#define __HAM_ENDIAN 201805

#define __HAM_ENDIAN_LITTLE 0x41424344UL
#define __HAM_ENDIAN_BIG    0x44434241UL
#define __HAM_ENDIAN_PDP    0x42414443UL
/** Represents current endianness. */
#define __HAM_ENDIAN_ORDER  ('ABCD')

namespace Hamilton {
    enum class endian: unsigned long{
        little  = __HAM_ENDIAN_LITTLE,
        big     = __HAM_ENDIAN_BIG,
        pdp     = __HAM_ENDIAN_PDP,
        /** Represents current endianness. */
        native  = __HAM_ENDIAN_ORDER
    };
}

#endif

