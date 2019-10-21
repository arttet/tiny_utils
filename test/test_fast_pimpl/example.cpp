#include "example.h"

struct example_t::implementation
{
   explicit implementation(int x)
      : x_(x)
   {
   }

   ~implementation()
   {
      --x_;
   }

   int x() const noexcept
   {
      return x_;
   }

private:
   int x_;
};

example_t::example_t(int x) noexcept
   : impl_(x)
{
}

example_t::~example_t() = default;

int example_t::x() const noexcept
{
   return impl_->x();
}
