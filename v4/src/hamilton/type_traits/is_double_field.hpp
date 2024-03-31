#ifndef __HAM_IS_DOUBLE_FIELD
#define __HAM_IS_DOUBLE_FIELD 20240331

#include <type_traits>

namespace hamilton{
    template <class T>
    struct is_double_field{
    private:
        // Test function for pow(T, double)
        template<typename X, typename = decltype(std::declval<X>() * 0.0)>
        static std::true_type test_backward(int);

        // Fallback for pow(T, double)
        template<typename>
        static std::false_type test_backward(...);

        // Test function for pow(T, double)
        template<typename X, typename = decltype(0.0 * std::declval<X>())>
        static std::true_type test_front(int);

        // Fallback for pow(T, double)
        template<typename>
        static std::false_type test_front(...);
    public:
        static constexpr bool value = decltype(test_backward<T>(0))::value && decltype(test_front<T>(0))::value;
    };
    template <class T>
    inline constexpr bool is_double_field_v = is_double_field<T>::value;
}

#endif