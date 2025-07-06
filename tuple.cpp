/*
 * A basic tuple implementation.
 */

#include <iostream>

template<class... T>
struct tuple {};

template<class S, class... T>
struct tuple<S, T...> : tuple<T...> {
    S s;
    tuple(S s, T... t) : s(s), tuple<T...>(t...) {}
};

template<size_t N, class T>
struct tuple_element;

template<size_t N, class S, class... T>
struct tuple_element<N, tuple<S, T...>> : tuple_element<N - 1, tuple<T...>> {};

template<class S, class... T>
struct tuple_element<0, tuple<S, T...>> { typedef S type; };

template<class T>
struct tuple_size;

template<class... T>
struct tuple_size<tuple<T...>> { const static size_t value = sizeof...(T); };

template<class... T>
struct tuple_size<const tuple<T...>> {
    const static size_t value = sizeof...(T);
};

template<size_t N, class S, class... T>
typename tuple_element<N, tuple<S, T...>>::type& get(tuple<S, T...>& t) {
    if constexpr (N > 0) { tuple<T...>& t_ = t; return get<N - 1, T...>(t_); }
    else return t.s;
}

template<size_t N, class S, class... T>
const typename tuple_element<N, tuple<S, T...>>::type&
        get(const tuple<S, T...>& t) {
    if constexpr (N > 0) {
        const tuple<T...>& t_ = t; return get<N - 1, T...>(t_);
    }
    else return t.s;
}

int main() {
    const tuple<int, char, bool> t{0, 'a', true};
    std::cout << tuple_size<decltype(t)>::value << get<0>(t) << get<1>(t);
}
