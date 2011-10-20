#include <stdio.h>
#include "functor.h"

#if 0
template <typename R, typename Parm1>
template <class Fun>
Functor<R, Parm1>::Functor(const Fun fun)
    : impl(new FunctorHandler<Functor, Fun>(fun))
{
}
#endif

struct TestFunctor {
    void operator()(int i) {
        printf("%s: %d\n", __FUNCTION__, i);
    }
};

void myFunction(int i)
{
    printf("%s: %d\n", __FUNCTION__, i);
}

int three(bool visible, double a)
{
    if (visible)
        printf("visible: %lf\n", a);
    else
        printf("invisible: %lf\n", a);
    return 10;
}

int main()
{
    TestFunctor f;
    Functor<void (int)> cmd1(myFunction);
    Functor<void (int)> cmd2(f);
    Functor<int (bool, double)> cmd3(three);

    cmd1(4);
    cmd2(5);

    printf("return: %d\n", cmd3(true, 123.45));
    return 0;
}
