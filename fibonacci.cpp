/* compile-time generation of the fibonacci sequence.
 * fibonacci<N> is an alias for the std::index_sequence whose template
 * parameters are the first N + 2 fibonacci numbers.
 */

#include <iostream>

template<std::size_t ...N>
using IS = std::index_sequence<N...>;

template<class, class>
struct reverse;

template<std::size_t ...I, std::size_t J, std::size_t ...K>
struct reverse<IS<I...>, IS<J, K...>> : reverse<IS<J, I...>, IS<K...>> {};

template<std::size_t ...I>
struct reverse<IS<I...>, IS<>> { typedef IS<I...> type; };

template<std::size_t N, std::size_t I, std::size_t J, std::size_t ...K>
struct Fib : Fib<N - 1, I + J, I, J, K...> {};

template<std::size_t I, std::size_t J, std::size_t ...K>
struct Fib<0, I, J, K...> {
    typedef typename reverse<IS<>, IS<I, J, K...>>::type type;
};

template<std::size_t N>
using fibonacci = typename Fib<N, 1, 0>::type;

int main() {
    []<std::size_t ...N>(IS<N...>) { ((std::cout << N << ' '), ...); } (
            fibonacci<100>{}); 
}
