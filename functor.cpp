#include <stdio.h>
#include "functor.h"

template <typename R, typename Parm1>
template <class Fun>
Functor<R, Parm1>::Functor(const Fun &fun)
    : impl(new FunctorHandler<Functor, Fun>(fun))
{
}

struct TestFunctor {
    void operator()(int i) {
        printf("%s: %d\n", __FUNCTION__, i);
    }
};

int main()
{
    TestFunctor f;
    Functor<void, int> cmd(f);
    cmd(4);

    return 0;
}
