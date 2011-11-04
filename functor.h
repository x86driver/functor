#ifndef FUNCTOR_H
#define FUNCTOR_H

template <typename R, typename... Args>
class FunctorImpl
{
public:
    virtual R operator()(Args...) const = 0;
    virtual FunctorImpl *clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename Fun, typename R, typename... Args>
class FunctorHandler : public FunctorImpl<R, Args...>
{
public:
    explicit FunctorHandler(const Fun &fun) : fun_(fun) {}
    R operator()(Args... args) const
    {
        return ((Fun&)fun_)(args...);
    }
    FunctorHandler *clone() const
    {
        return new FunctorHandler(*this);
    }
private:
    const Fun &fun_;
};

template <typename Fun, typename R, typename... Args>
class FunctorHandler<Fun*, R, Args...> : public FunctorImpl<R, Args...>
{
public:
    explicit FunctorHandler(const Fun *fun) : fun_(fun) {}
    R operator()(Args... args) const
    {
        return (const_cast<Fun*>(fun_))->operator()(args...);
    }
    FunctorHandler *clone() const
    {
        return new FunctorHandler(*this);
    }
private:
    const Fun *fun_;
};

template <typename PointerToObj, typename PointerToMemFn, typename R, typename... Args>
class MemFunHandler : public FunctorImpl<R, Args...>
{
public:
    MemFunHandler(const PointerToObj &obj, PointerToMemFn fn)
        : pobj(obj), pfn(fn) {}
    MemFunHandler *clone() const
    {
        return new MemFunHandler(*this);
    }
    R operator()(Args... args) const
    {
        return ((*pobj).*pfn)(args...);
    }
private:
    PointerToObj pobj;
    PointerToMemFn pfn;
};

template <typename Signature>
class Functor;

template <typename R, typename... Args>
class Functor<R (Args...)> {
public:

    ~Functor() { if (impl) delete impl; }

    template <class Fun> Functor(const Fun &fun)
        : impl(new FunctorHandler<Fun, R, Args...>(fun))
    {}

    template <class Fun> Functor(const Fun *fun)
        : impl(new FunctorHandler<Fun*, R, Args...>(fun))
    {}

    template <typename PtrObj, typename MemFn>
    Functor(const PtrObj &p, MemFn fn)
        : impl(new MemFunHandler<PtrObj, MemFn, R, Args...>(p, fn))
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
