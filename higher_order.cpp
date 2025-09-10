// Higher-order metafunctions.
// compose<F, G>::of is the composition of F and G.
//  e.g. compose<add_pointer, add_const>::of<int> = const int*
// fn<F, N>::of is the N-th functional power of F.
//  e.g. fn<add_pointer, 3>::of<int> = int***

template<template<class> class F, template<class> class G>
struct compose {
    template<class T>
    using of = F<G<T>>;
};

template<class T>
using identity = T;

template<template<class> class F, int N, template<class> class G = identity>
struct fn : fn<F, N - 1, compose<F, G>::template of> {};

template<template<class> class F, template<class> class G>
struct fn<F, 0, G> {
    template<class T>
    using of = G<T>;
};

template<class T>
T* try_add_pointer(int) {}
template<class T>
T try_add_pointer(...) {}
template<class T>
using add_pointer = decltype(try_add_pointer<T>(0));

template<class T>
using add_const = const T;

template<class S, class T>
constexpr bool is_same = false;
template<class T>
constexpr bool is_same<T, T> = true;

static_assert(is_same<compose<add_pointer, add_const>::of<int>, const int*>);
static_assert(is_same<compose<add_const, add_pointer>::of<int>, int* const>);
static_assert(is_same<fn<add_pointer, 0>::of<int>, int>);
static_assert(is_same<fn<add_pointer, 3>::of<int>, int***>);
