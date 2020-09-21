#pragma once

#include <tiny_utils/fast_pimpl.h>

struct example_t final
{
    explicit example_t(int x = 0) noexcept;

    example_t(example_t const & other) = delete;
    example_t(example_t && other) = delete;

    example_t & operator=(example_t const & other) = delete;
    example_t & operator=(example_t && other) = delete;

    ~example_t() noexcept;

    int x() const noexcept;

private:
    struct implementation;
    static int constexpr length{4};
    static int constexpr alignment{4};
    tiny_utils::fast_pimpl_t<implementation, length, alignment> impl_;
};
