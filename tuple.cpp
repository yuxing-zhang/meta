/*
 * The class template tuple acts as a container for types.
 * For tuple<type_0, type_1, ..., type_{n-1}>,
 * tuple::size = n, the number of types
 * tuple::type<i> = type_i, the i-th type
 */
#include <type_traits>

template<int N, class S, class...T>
struct get : get<N - 1, T...> {};

template<class S, class...T>
struct get<0, S, T...> {
    typedef S type;
};

template<int N, class S, class... T>
struct size : size<N + 1, T...> {};

template<int N, class T>
struct size<N, T> {
    static const int n = N + 1;
};

template<class... T>
struct tuple {
    static const int size = ::size<0, T...>::n;
    template<int N>
    using type = typename get<N, T...>::type;
};

typedef tuple<char, int, double> tp;
static_assert(tp::size == 3, "");
static_assert(std::is_same_v<tp::type<0>, char>, "");
static_assert(std::is_same_v<tp::type<1>, int>, "");
static_assert(std::is_same_v<tp::type<2>, double>, "");

int main() {}
