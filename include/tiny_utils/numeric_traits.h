/**
 * @file numeric_traits.h
 * @author Artyom Tetyukhin
 * @brief Numeric traits define a compile-time template-based interface
 * @version 1.0
 * @date 2019-10-10
 *
 * @copyright Copyright (c) 2020 Artyom Tetyukhin
 *
 */
#pragma once

#include <type_traits>

namespace tiny_utils
{
namespace detail
{

constexpr int abs_val(int const x) noexcept
{
    return x < 0 ? -x : x;
}

constexpr int num_digits(int const x) noexcept
{
    return x < 0 ? 1 + num_digits(-x) : x < 10 ? 1 : 1 + num_digits(x / 10);
}

template <char... args>
struct metastring_t final
{
    const char data[sizeof...(args)] = {args...};
};

template <int size, int x, char... args>
struct numeric_builder_t final
{
    using type = typename numeric_builder_t<size - 1, x / 10, '0' + abs_val(x) % 10, args...>::type;
};

template <int x, char... args>
struct numeric_builder_t<2, x, args...> final
{
    using type = metastring_t < x<0 ? '-' : '0' + x / 10, '0' + abs_val(x) % 10, args...>;
};

template <int x, char... args>
struct numeric_builder_t<1, x, args...> final
{
    typedef metastring_t<'0' + x, args...> type;
};

template <int N>
struct trigger_overflow_warning_t final
{
    static constexpr char value() noexcept
    {
        return N + 256;
    }
};

template <int lhs, int rhs, typename _ = void>
struct is_same_number final
{
    static constexpr bool value = true;
};

template <int lhs, int rhs>
struct is_same_number<lhs, rhs, typename std::enable_if<lhs != rhs>::type>
{
    static constexpr bool value = trigger_overflow_warning_t<lhs>::value() == trigger_overflow_warning_t<rhs>::value();
};

} // namespace detail

/**
 * @brief Converts an integer number to the string at compile-time.
 *
 * @tparam x an integer number
 */
template <int x>
struct numeric_string_t final
{
    static constexpr const char * data() noexcept
    {
        return value.data;
    }

private:
    using type = typename detail::numeric_builder_t<detail::num_digits(x), x, '\0'>::type;
    static constexpr type value{};
};

/**
 * @brief Compares two strings at compile-time.
 *
 * @param lhs argument to the left-hand side
 * @param rhs argument to the right-hand side
 * @return true if the strings equal, and false otherwise.
 */
constexpr bool strings_equal(char const * lhs, char const * rhs)
{
    return *lhs == *rhs && (*lhs == '\0' || strings_equal(lhs + 1, rhs + 1));
}

template <int x>
constexpr typename numeric_string_t<x>::type numeric_string_t<x>::value;

/**
 * @brief Compares two integers at compile-time and shows values if they do not equal.
 */
template <int lhs, int rhs>
constexpr bool is_same_number_v = detail::is_same_number<lhs, rhs>::value;

} // namespace tiny_utils
