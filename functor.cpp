#include <stdio.h>
#include "tuple.h"
#include "functor.h"

struct TestFunctor {
    TestFunctor() : count(0) {}
    void operator()(int i) {
        printf("%s: %d, count: %d\n", __FUNCTION__, i, count);
        ++count;
    }
    void set(int x) { count = x; }
    int count;
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

class Parrot {
public:
    void Eat() {
        printf("Parrot eat!\n");
    }
    void Speak() {
        printf("Parrot speak!\n");
    }
};

int main2()
{
    TestFunctor f;
    Functor<void (int)> cmd1(f);

    auto cmd2 = cmd1;

    f.set(10);

    cmd1(0);
    cmd2(0);

    return 0;
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

    f.set(100);
    cmd2(9);

    TestFunctor *myfunc = new TestFunctor;
    Functor<void (int)> mycmd(myfunc);
    mycmd(3);
    myfunc->set(7);
    mycmd(4);
    delete myfunc;

    Parrot geronimo;
    Functor<void (void)> cmd_parrot1(&geronimo, &Parrot::Eat);
    cmd_parrot1();

    return 0;
}
