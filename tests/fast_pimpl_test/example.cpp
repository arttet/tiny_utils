#include "example.h"

struct example_t::implementation final
{
    explicit implementation(int const x) noexcept
        : x_(x)
    {
    }

    implementation(implementation const & other) = delete;
    implementation(implementation && other) = delete;

    implementation & operator=(implementation const & other) = delete;
    implementation & operator=(implementation && other) = delete;

    ~implementation() noexcept
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

example_t::~example_t() noexcept = default;

int example_t::x() const noexcept
{
    return impl_->x();
}
