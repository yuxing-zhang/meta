/*
 * Another minimal implementation of compile-time integer sequences, using
 * integral_constants to bypass the constraint that non-type template
 * parameters with a dependent type cannot be specialized.
 */

#include <type_traits>

template<class T, T ...N>
struct integer_sequence {}; 

template<std::size_t ...N>
using index_sequence = integer_sequence<std::size_t, N...>;

template<class... T>
struct IS;
template<class T, T I, T ...N>
struct IS<T, std::integral_constant<T, I>, std::integral_constant<T, N>...>
        : IS<T, std::integral_constant<T, I - 1>,
        std::integral_constant<T, I - 1>, std::integral_constant<T, N>...> {};
template<class T, T ...N>
struct IS<T, std::integral_constant<T, 0>, std::integral_constant<T, N>...> {
    typedef integer_sequence<T, N...> type;
};
template<class T, T N>
using make_integer_sequence
        = typename IS<T, std::integral_constant<T, N>>::type;

template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

static_assert(std::is_same_v<make_index_sequence<3>,
        integer_sequence<std::size_t, 0, 1, 2>>);

int main() {}
