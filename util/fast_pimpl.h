#pragma once

#include <type_traits>
#include <new>

namespace util
{
   template <class T, std::size_t Length, std::size_t Alignment>
   struct fast_pimpl_t final
   {
      explicit fast_pimpl_t() noexcept
      {
         new (&storage_) T;
      }

      template <class... Args>
      explicit fast_pimpl_t(Args &&... args) noexcept
      {
         new (&storage_) T(std::forward<Args>(args)...);
      }

      explicit fast_pimpl_t(fast_pimpl_t & other) noexcept = default;
      fast_pimpl_t& operator=(fast_pimpl_t & other) noexcept = default;

      explicit fast_pimpl_t(fast_pimpl_t && other) noexcept = delete;
      fast_pimpl_t& operator=(fast_pimpl_t && other) noexcept = delete;

      ~fast_pimpl_t()
      {
         static_assert(Length == sizeof(T), "Length mismatch");
         static_assert(Alignment == alignof(T), "Alignment mismatch");

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
