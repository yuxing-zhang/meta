/* A multidimensional array.
 * Marray<T, N_0, N_1, ..., N_{n - 1}> is an alias for
 * std::array<std::array<...<std::array<T, N_{n - 1}>, ...>, N_1>, N_0>
 */

#include <array>

template<class, std::size_t ...>
struct F;

template<class T>
struct F<T> { typedef T type; };

template<class T, std::size_t I, std::size_t ...N>
struct F<T, I, N...> {
    typedef std::array<typename F<T, N...>::type, I> type;
};

template<class T, std::size_t ...N>
using Marray = typename F<T, N...>::type;

static_assert(std::is_same_v<Marray<int, 2, 3, 4>, void>);
