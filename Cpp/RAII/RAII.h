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
    /* Ԫģ�壬�����const������ȥ��const���η� */
    template<typename T>
    struct no_const
    {
        using type = typename std::conditional<std::is_const<T>::value, typename std::remove_const<T>::type, T>::type;
    };


    ///  RAII��ʽ����������ͷ���Դ����
    /// ���󴴽�ʱ,ִ��acquire(������Դ)����(����Ϊ�պ���[]{})
    /// ��������ʱ,ִ��release(�ͷ���Դ)����
    /// ��ֹ���󿽱��͸�ֵ
    class RAII
    {
    public:
        typedef std::function<void()> FunctionType;

        /// release: ����ʱִ�еĺ���
        /// acquire: ���캯��ִ�еĺ���
        /// default_com:_commit,Ĭ��ֵ,����ͨ��commit()������������
        explicit RAII(FunctionType release, FunctionType acquire = [] {}, bool default_com = true) noexcept :
            _commit(default_com),
            _release(release)
        {
            acquire();
        }

        /// ��������ʱ����_commit��־ִ��_release����
        ~RAII() noexcept
        {
            if (_commit)
                _release();
        }

        /// �ƶ����캯�� ������ֵ��ֵ
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


    /// ����ʵ����Դ��RAII������
    /// TΪ��Դ����
    /// acquireΪ������Դ������������ԴT
    /// releaseΪ�ͷ���Դ����,�ͷ���ԴT
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

        /// �ƶ����캯��
        RAIIVar(RAIIVar&& rv) :
            _resource(std::move(rv._resource)),
            _release(std::move(rv._release))
        {
            rv._commit = false;//������ֵ��������ʱ����ִ��_release
        }

        /// ��������ʱ����_commit��־ִ��_release����
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



    /// ���� RAII ����,
    /// ��std::bind��M_REL,M_ACQ��װ��std::function<void()>����RAII����
    /// RES      ��Դ����
    /// M_REL    �ͷ���Դ�ĳ�Ա������ַ
    /// M_ACQ    ������Դ�ĳ�Ա������ַ
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
