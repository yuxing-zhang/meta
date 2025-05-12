/*
 * Curiously Recurring Template Pattern
 * The pattern is such that a class is derived from a template base class whose
 * template parameter is the derived class. This can be used to implement
 * compile-time polymorphism.
 */

#include <iostream>

template<class T>
struct B {
    typedef T type;
    void f() { static_cast<T*>(this)->g(); }
};

struct C : B<C> {
    void g() { std::cout << 'c'; }
};
struct D : B<D> {
    void g() { std::cout << 'd'; }
};

static_assert(std::is_same_v<C::type, C>, "");
static_assert(std::is_same_v<D::type, D>, "");

int main() {
    C c;
    D d;
    c.f();
    d.f();
}
