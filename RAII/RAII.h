#pragma once
//
// RAII.h
//
// Library: Foundation
// Package: Core
// Module:  RAII
//
// Definition of the RAII template class and friends.
//
//



#include <type_traits>
#include <functional>


namespace Wishbone
{
    /* 元模板，如果是const类型则去除const修饰符 */
    template<typename T>
    struct no_const
    {
        using type = typename std::conditional<std::is_const<T>::value, typename std::remove_const<T>::type, T>::type;
    };


    ///  RAII方式管理申请和释放资源的类
    /// 对象创建时,执行acquire(申请资源)动作(可以为空函数[]{})
    /// 对象析构时,执行release(释放资源)动作
    /// 禁止对象拷贝和赋值
    class RAII
    {
    public:
        typedef std::function<void()> FunctionType;

        /// release: 析构时执行的函数
        /// acquire: 构造函数执行的函数
        /// default_com:_commit,默认值,可以通过commit()函数重新设置
        explicit RAII(FunctionType release, FunctionType acquire = [] {}, bool default_com = true) noexcept :
            _commit(default_com),
            _release(release)
        {
            acquire();
        }

        /// 对象析构时根据_commit标志执行_release函数
        ~RAII() noexcept
        {
            if (_commit)
                _release();
        }

        /// 移动构造函数 允许右值赋值
        RAII(RAII&& rv) noexcept :
            _commit(rv._commit),
            _release(rv._release)
        {
            rv._commit = false;
        };

        ///
        RAII& commit(bool c = true) noexcept;

    protected:
        std::function<void()> _release;

    private:
        RAII(const RAII&);
        RAII& operator=(const RAII&) = delete;

        bool _commit;


    }; /* RAII */


    /// inlins
    inline RAII& RAII::commit(bool c = true) noexcept
    {
        _commit = c; return *this;
    };


    /// 用于实体资源的RAII管理类
    /// T为资源类型
    /// acquire为申请资源动作，返回资源T
    /// release为释放资源动作,释放资源T
    template<typename T>
    class RAIIVar
    {
    public:
        typedef std::function<T()> AcquireType;
        typedef std::function<void(T&)> ReleaseType;


        ///
        explicit RAIIVar(AcquireType acquire, ReleaseType release) noexcept :
            _resource(acquire()),
            _release(release)
        {
        }

        /// 移动构造函数
        RAIIVar(RAIIVar&& rv) :
            _resource(std::move(rv._resource)),
            _release(std::move(rv._release))
        {
            rv._commit = false;//控制右值对象析构时不再执行_release
        }

        /// 对象析构时根据_commit标志执行_release函数
        ~RAIIVar() noexcept
        {
            if (_commit)
                _release(_resource);
        }

        RAIIVar<T>& commit(bool c = true) noexcept
        {
            _commit = c;
            return *this;
        };

        T& get() noexcept
        {
            return _resource;
        }

        T& operator*() noexcept
        {
            return get();
        }

        template<typename _T = T>
        typename std::enable_if<std::is_pointer<_T>::value, _T>::type operator->() const noexcept
        {
            return _resource;
        }

        template<typename _T = T>
        typename std::enable_if<std::is_class<_T>::value, _T*>::type operator->() const noexcept
        {
            return std::addressof(_resource);
        }

    private:
        bool        _commit = true;
        T           _resource;
        ReleaseType _release;
    };



    /// 创建 RAII 对象,
    /// 用std::bind将M_REL,M_ACQ封装成std::function<void()>创建RAII对象
    /// RES      资源类型
    /// M_REL    释放资源的成员函数地址
    /// M_ACQ    申请资源的成员函数地址
    template<typename RES, typename M_REL, typename M_ACQ>
    RAII make_raii(RES& res, M_REL rel, M_ACQ acq, bool default_com = true) noexcept
    {
        static_assert(std::is_class<RES>::value, "RES is not a class or struct type.");
        static_assert(std::is_member_function_pointer<M_REL>::value, "M_REL is not a member function.");
        static_assert(std::is_member_function_pointer<M_ACQ>::value, "M_ACQ is not a member function.");
        assert(nullptr != rel && nullptr != acq);
        auto p_res = std::addressof(const_cast<typename no_const<RES>::type&>(res));
        return RAII(std::bind(rel, p_res), std::bind(acq, p_res), default_com);
    }

    template<typename RES, typename M_REL>
    RAII make_raii(RES& res, M_REL rel, bool default_com = true) noexcept
    {
        static_assert(std::is_class<RES>::value, "RES is not a class or struct type.");
        static_assert(std::is_member_function_pointer<M_REL>::value, "M_REL is not a member function.");
        assert(nullptr != rel);
        auto p_res = std::addressof(const_cast<typename no_const<RES>::type&>(res));
        return RAII(std::bind(rel, p_res), [] {}, default_com);
    }

} // namespace Wishbone
