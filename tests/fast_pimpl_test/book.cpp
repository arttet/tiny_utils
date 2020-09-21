#include "book.h"

#include <utility>

struct book_t::implementation final
{
    explicit implementation(std::string s)
        : s_(std::move(s))
    {
    }

    implementation(implementation const & other) = delete;
    implementation(implementation && other) = delete;

    implementation & operator=(implementation const & other) = delete;
    implementation & operator=(implementation && other) = delete;

    ~implementation() noexcept = default;

    std::string const & contents() const noexcept
    {
        return s_;
    }

private:
    std::string s_;
};

book_t::book_t(std::string s)
    : impl_(std::move(s))
{
}

book_t::~book_t() noexcept = default;

std::string const & book_t::contents() const noexcept
{
    return impl_->contents();
}
