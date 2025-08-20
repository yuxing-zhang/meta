/* compile-time generation of the fibonacci sequence, implemented as a variable
 * template.
 */

#include <iostream>

template<int I>
constexpr size_t a = a<I - 1> + a<I - 2>;

template<>
constexpr size_t a<0> = 0;
template<>
constexpr size_t a<1> = 1;

int main() {
    []<size_t ...I>(std::index_sequence<I...>) {
        (..., (std::cout << a<I> << ' ')); }(std::make_index_sequence<94>{});
}
