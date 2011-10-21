#ifndef FUNCTOR_H
#define FUNCTOR_H

template <typename R, typename... Args>
class FunctorImpl
{
public:
    virtual R operator()(Args...) = 0;
    virtual FunctorImpl *clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename Fun, typename R, typename... Args>
class FunctorHandler : public FunctorImpl<R, Args...>
{
public:
    explicit FunctorHandler(const Fun &fun) : fun_(fun) {}
    R operator()(Args... args)
    {
        return fun_(args...);
    }
    FunctorHandler *clone() const
    {
        return new FunctorHandler(*this);
    }
private:
    Fun fun_;
};

template <typename Signature>
class Functor;

template <typename R, typename... Args>
class Functor<R (Args...)> {
public:

    ~Functor() { if (impl) delete impl; }

    template <class Fun> Functor(const Fun fun)
        : impl(new FunctorHandler<Fun, R, Args...>(fun))
    {}

    Functor(const Functor &f)
        : impl(f.impl->clone())
    {}

    Functor& operator=(const Functor &f)
    {
        if (impl)
            delete impl;
        impl = f.impl->clone();
        return *this;
    }

    R operator()(Args... args)
    {
        return (*impl)(args...);
    }

private:
    Functor();
    FunctorImpl<R, Args...> *impl;
};

#endif
