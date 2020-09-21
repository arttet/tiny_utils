/**
 * @file fast_pimpl.h
 * @author Artyom Tetyukhin
 * @brief Implementation of the C++ idiom "Fast Pointer To Implementation"
 * @version 1.0
 * @date 2019-10-10
 *
 * @copyright Copyright (c) 2020 Artyom Tetyukhin
 *
 */
#pragma once

#include "numeric_traits.h"

#include <cstddef>
#include <new>
#include <type_traits>

namespace tiny_utils
{
/**
 * @brief Implementation of the C++ idiom "Fast Pointer To Implementation"
 *
 * Zero overhead cost implementation
 *
 * @tparam T the incomplete type to implementation
 * @tparam Length the size, in bytes, of the object representation of T
 * @tparam Alignment the alignment, in bytes, required for any instance of the type indicated by T
 * @tparam IsNoThrow false if constructor of the type T can throw an exception otherwise true.
 *  Defaults to true.
 *
 * Example of usage
 * @code{.cpp}
 * struct implementation;
 * static int constexpr length{24};
 * static int constexpr alignment{8};
 * tiny_utils::fast_pimpl_t<implementation, length, alignment, false> impl_;
 * @endcode
 *
 * @see https://en.wikibooks.org/wiki/C%2B%2B_Programming/Idioms#Pointer_To_Implementation_(pImpl)/
 */
template <class T, std::size_t Length, std::size_t Alignment, bool IsNoThrow = true>
struct fast_pimpl_t final
{
    /**
     * @brief Construct a new fast_pimpl_t object
     *
     */
    fast_pimpl_t() noexcept(IsNoThrow)
    {
        static_assert(std::is_nothrow_default_constructible<T>::value == IsNoThrow, "T should be noexcept");
        new (&storage_) T;
    }

    /**
     * @brief Construct a new fast_pimpl_t object
     *
     * @tparam Args list of types with which an instance of T will be constructed.
     * @param args list of arguments with which an instance of T will be constructed.
     */
    template <class... Args>
    explicit fast_pimpl_t(Args &&... args) noexcept(IsNoThrow)
    {
        static_assert(std::is_nothrow_constructible<T, Args...>::value == IsNoThrow, "T should be noexcept");
        new (&storage_) T(std::forward<Args>(args)...);
    }

    fast_pimpl_t(fast_pimpl_t & other) = delete;
    fast_pimpl_t(fast_pimpl_t && other) = delete;

    fast_pimpl_t & operator=(fast_pimpl_t & other) = delete;
    fast_pimpl_t & operator=(fast_pimpl_t && other) = delete;

    /**
     * @brief Destroy the fast_pimpl_t object
     *
     */
    ~fast_pimpl_t() noexcept
    {
        static_assert(is_same_number_v<Length, sizeof(T)>, "Length mismatch");
        static_assert(is_same_number_v<Alignment, alignof(T)>, "Alignment mismatch");

        reinterpret_cast<T *>(&storage_)->~T();
    }

    /**
     * @brief Dereferences pointer to the managed object
     *
     * Provide access to the object owned by *this
     *
     * @return T& the object owned by *this
     */
    T & operator*() noexcept
    {
        return reinterpret_cast<T &>(storage_);
    }

    /**
     * @brief Dereferences pointer to the managed object
     *
     * Provide access to the object owned by *this
     *
     * @return T const& the object owned by *this
     */
    T const & operator*() const noexcept
    {
        return reinterpret_cast<T const &>(storage_);
    }

    /**
     * @brief Dereferences pointer to the managed object
     *
     * Provide access to the object owned by *this
     *
     * @return T* a pointer to the object owned by *this
     */
    T * operator->() noexcept
    {
        return reinterpret_cast<T *>(&storage_);
    }

    /**
     * @brief Dereferences pointer to the managed object
     *
     * Provide access to the object owned by *this
     *
     * @return T const* a pointer to the object owned by *this
     */
    T const * operator->() const noexcept
    {
        return reinterpret_cast<T const *>(&storage_);
    }

private:
    using storage_t = typename std::aligned_storage<Length, Alignment>::type;
    storage_t storage_;
};

constexpr int length(int const msvc_debug_size, int const x64_size, int const x86_size)
{
#if defined(_MSC_VER) && defined(_DEBUG) && defined(_WIN64)
    static_cast<void>(x64_size);
    static_cast<void>(x86_size);
    return msvc_debug_size;
#elif defined(__APPLE__)
    static_cast<void>(msvc_debug_size);
    static_cast<void>(x64_size);
    return x86_size;
#else
    static_cast<void>(msvc_debug_size);
    return alignof(void *) == 8 ? x64_size : x86_size;
#endif
}

} // namespace tiny_utils
