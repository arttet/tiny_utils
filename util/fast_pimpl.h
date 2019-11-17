#pragma once

#include <type_traits>
#include <new>

#include "numeric_traits.h"

namespace utils
{
    template <class T, std::size_t Length, std::size_t Alignment, bool is_nothrow = true>
    struct fast_pimpl_t final
    {
        explicit fast_pimpl_t() noexcept(is_nothrow)
        {
            static_assert(std::is_nothrow_default_constructible<T>::value == is_nothrow, "T should be noexcept");
            new (&storage_) T;
        }

        template <class... Args>
        explicit fast_pimpl_t(Args &&... args) noexcept(is_nothrow)
        {
            static_assert(std::is_nothrow_constructible<T, Args...>::value == is_nothrow, "T should be noexcept");
            new (&storage_) T(std::forward<Args>(args)...);
        }

        explicit fast_pimpl_t(fast_pimpl_t & other) = delete;
        fast_pimpl_t& operator=(fast_pimpl_t & other) = delete;

        explicit fast_pimpl_t(fast_pimpl_t && other) = delete;
        fast_pimpl_t& operator=(fast_pimpl_t && other) = delete;

        ~fast_pimpl_t()
        {
            static_assert(is_same_number_t<Length, sizeof(T)>::value, "Length mismatch");
            static_assert(is_same_number_t<Alignment, alignof(T)>::value, "Alignment mismatch");

            reinterpret_cast<T*>(&storage_)->~T();
        }

        T & operator*() noexcept
        {
            return reinterpret_cast<T&>(storage_);
        }

        T const & operator*() const noexcept
        {
            return reinterpret_cast<T const&>(storage_);
        }

        T* operator->() noexcept
        {
            return reinterpret_cast<T*>(&storage_);
        }

        T const* operator->() const noexcept
        {
            return reinterpret_cast<T const*>(&storage_);
        }

    private:
        using storage_t = typename std::aligned_storage<Length, Alignment>::type;
        storage_t storage_;
    };
}
