#include <stdio.h>
#include "tuple.h"
#include "functor.h"

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

class Button {
public:
    typedef std::tuple_element<0, std::tuple<void (void)> >::type CallbackType;
    Button(Functor<CallbackType> &func) : func(func) {}
    void clicked() { func(); }
    void setClicked(Functor<CallbackType> &func) {
        this->func = func;
    }
private:
    Functor<CallbackType> func;
};

void nofunc()
{
    printf("I'm in nofunc!\n");
}

template<typename T, typename U>
auto myFunc( T& t, U& u)-> decltype( t + u ){

  return t + u;

};

template <typename Signature>
class NoCommand;

template <typename R, typename... Args>
class NoCommand<R (Args...)> {
public:
    R operator()(Args...) {
    }
};

void abc()
{
}

int main()
{
    TestFunctor f;
    Functor<void (int)> cmd1(myFunction);
    Functor<void (int)> cmd2(f);
    Functor<int (bool, double)> cmd3(three);
    Functor<void (void)> cmd4(nofunc);

    Button btn(cmd4);
    btn.clicked();

    cmd1(4);
    cmd2(5);

    printf("return: %d\n", cmd3(true, 123.45));

    auto cmd5 = cmd1;
    cmd5 = cmd2;
    cmd5(10);

    return 0;
}
