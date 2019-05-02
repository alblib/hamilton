#ifndef __HAM_INTFIXTYPES
#define __HAM_INTFIXTYPES 201805

#include <iterator>
#include "endian.hpp"
#include <type_traits>

namespace Hamilton {
    namespace intfixtypes_namespace{
        template <class Class, size_t Size>
        class endian_considered_array{
        private:
            Class defined[Size];
        public:
            /** Gives uninitialized array. */
            endian_considered_array(std::nullptr_t){}
            /** Gives initialized array. */
            constexpr endian_considered_array(): defined() {}
            
            #if __HAM_ENDIAN_ORDER == __HAM_ENDIAN_BIG
            using iterator       = ::std::reverse_iterator<Class *>;
            using const_iterator = ::std::reverse_iterator<const Class *>;
            #else
            using iterator       = Class *;
            using const_iterator = const Class *;
            #endif
            
            static constexpr const size_t size = Size;
            inline constexpr Class& operator [] (size_t index) &{
                #if __HAM_ENDIAN_ORDER == __HAM_ENDIAN_BIG
                return defined[size - 1 - index];
                #else
                return defined[index];
                #endif
            }
            inline constexpr Class&& operator [] (size_t index) &&{
                #if __HAM_ENDIAN_ORDER == __HAM_ENDIAN_BIG
                return defined[size - 1 - index];
                #else
                return defined[index];
                #endif
            }
            inline constexpr const Class& operator [] (size_t index) const &{
                #if __HAM_ENDIAN_ORDER == __HAM_ENDIAN_BIG
                return defined[size - 1 - index];
                #else
                return defined[index];
                #endif
            }
            inline constexpr const Class&& operator [] (size_t index) const &&{
                #if __HAM_ENDIAN_ORDER == __HAM_ENDIAN_BIG
                return defined[size - 1 - index];
                #else
                return defined[index];
                #endif
            }
            operator iterator(){
                return defined;
            }
            operator const_iterator() const{
                return defined;
            }
            
            void negate() {
                Class* start = defined;
                Class* end   = defined + Size;
                for(; start != end; ++start){
                    *start = ~*start;
                }
            }
            endian_considered_array negate_copy() const{
                endian_considered_array result(nullptr);
                Class* start = defined;
                Class* end   = defined + Size;
                Class* start2 = result.defined;
                for(; start != end; ++start, ++start2){
                    *start2 = ~*start;
                }
                return result;
            }
            void add(const endian_considered_array& op){
                iterator start = *this;
                iterator end   = start + Size;
                const_iterator start2 = op;
                bool round = false;
                for(; start != end; ++start, ++start2){
                    *start += (round ? (*start2 + 1) : *start2);
                    round = round ? (static_cast<std::make_unsigned<Class>>(*start2) >= static_cast<std::make_unsigned<Class>>(*start)) : (static_cast<std::make_unsigned<Class>>(*start2) > static_cast<std::make_unsigned<Class>>(*start));
                }
            }
            endian_considered_array add_copy(const endian_considered_array& op) const{
                endian_considered_array result(nullptr);
                const_iterator start  = *this;
                const_iterator end    = start + Size;
                const_iterator start2 = op;
                iterator start_result = result;
                bool round = false;
                for(; start != end; ++start, ++start2, ++start_result){
                    *start_result = *start + *start2 + (round ? 1 : 0);
                    round = round ? (static_cast<std::make_unsigned<Class>>(*start2) >= static_cast<std::make_unsigned<Class>>(*start_result)) : (static_cast<std::make_unsigned<Class>>(*start2) > static_cast<std::make_unsigned<Class>>(*start_result));
                }
                return result;
            }
        };
    }
}


#endif
