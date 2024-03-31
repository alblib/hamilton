#ifndef __HAM_QUADRATIC_SOLUTION
#define __HAM_QUADRATIC_SOLUTION 20240301

#include <type_traits>
#include <cmath>
#include "../type_traits/has_pow.hpp"
#include "../type_traits/is_double_field.hpp"

namespace hamilton{
    template <class T, typename std::enable_if<has_pow_v<T> && is_double_field_v<T>>::type* = nullptr>
    void quadratic_solution(T coeff0, T coeff1, T coeff2, T& sol1, T& sol2)
    {
        T determinant = coeff1 * coeff1 - 4.0 * coeff0 * coeff2;
        T sqrt_det = pow(determinant, 0.5);
        sol1 = (-coeff1 + sqrt_det) / (2.0 * coeff2);
        sol2 = (-coeff1 - sqrt_det) / (2.0 * coeff2);
    }
}

#endif