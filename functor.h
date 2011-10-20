#ifndef FUNCTOR_H
#define FUNCTOR_H

template <typename R, typename P1>
class FunctorImpl
{
public:
    virtual R operator()(P1) = 0;
//    virtual FunctorImpl* Clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename Parm1>
class Functor {
private:
    typedef FunctorImpl<R, Parm1> Impl;
public:
    Functor();
    ~Functor() { if (impl) delete impl; }
    template <class Fun> Functor(const Fun fun);
    Functor(const Functor &);
    Functor& operator=(const Functor &);
//    explicit Functor(Impl *impl);
    R operator()(Parm1 p1) {
        return (*impl)(p1);
    }
    typedef R ResultType;
    typedef Parm1 PType1;
private:
//    typedef FunctorImpl<R, Parm1> Impl;
    Impl *impl;
};

template <class ParentFunctor, typename Fun>
class FunctorHandler : public FunctorImpl
    <
        typename ParentFunctor::ResultType,
        typename ParentFunctor::PType1
    >
{
public:
    typedef typename ParentFunctor::ResultType ResultType;
    FunctorHandler(const Fun &fun) : fun_(fun) {}
    ResultType operator()(typename ParentFunctor::PType1 p1)
    {
        return fun_(p1);
    }
private:
    Fun fun_;
};

#endif
