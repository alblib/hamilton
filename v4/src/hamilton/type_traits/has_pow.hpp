#ifndef __HAM_HAS_POW
#define __HAM_HAS_POW 20240301

#include <utility>
#include <type_traits>
#include <cmath>

namespace hamilton{

    // Alias std::pow to hamilton::pow
    template<typename T, typename U>
    inline decltype(auto) pow(T base, U exp) {
        return std::pow(base, exp);
    }

    template <class T>
    struct has_pow{
    private:
        // Test function for pow(T, double)
        template<typename X, typename = decltype(pow(std::declval<X>(), 0.0))>
        static std::true_type test_double(int);

        // Fallback for pow(T, double)
        template<typename>
        static std::false_type test_double(...);
    public:
        static constexpr bool value = decltype(test_double<T>(0))::value;
    };
    template <class T>
    inline constexpr bool has_pow_v = has_pow<T>::value;
}

#endif