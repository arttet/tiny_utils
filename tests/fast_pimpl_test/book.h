#pragma once

#include <tiny_utils/fast_pimpl.h>

#include <string>

struct book_t final
{
    explicit book_t(std::string s);
    ~book_t() noexcept;

    book_t(book_t const & other) = delete;
    book_t(book_t && other) = delete;

    book_t & operator=(book_t const & other) = delete;
    book_t & operator=(book_t && other) = delete;

    std::string const & contents() const noexcept;

private:
    struct implementation;
    static int constexpr length = tiny_utils::length(40, 32, 24);
    static int constexpr alignment = alignof(void *);
    tiny_utils::fast_pimpl_t<implementation, length, alignment, false> impl_;
};
