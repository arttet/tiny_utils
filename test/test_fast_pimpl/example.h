#pragma once

#include <util/fast_pimpl.h>

struct example_t final
{
   explicit example_t(int x = 0) noexcept;
   ~example_t();

   int x() const noexcept;

private:
   struct implementation;
   static int constexpr lenght{ 4 };
   static int constexpr alignment{ 4 };
   util::fast_pimpl_t<implementation, lenght, alignment> impl_;
};