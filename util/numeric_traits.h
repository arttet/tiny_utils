#pragma once

#include <type_traits>

namespace utils
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

        template<char... args>
        struct metastring_t final
        {
            const char data[sizeof ... (args)] = { args... };
        };

        template<int size, int x, char... args>
        struct numeric_builder_t final
        {
            using type = typename numeric_builder_t<size - 1, x / 10, '0' + abs_val(x) % 10, args...>::type;
        };

        template<int x, char... args>
        struct numeric_builder_t<2, x, args...> final
        {
            using type = metastring_t< x < 0 ? '-' : '0' + x / 10, '0' + abs_val(x) % 10, args...>;
        };

        template<int x, char... args>
        struct numeric_builder_t<1, x, args...> final
        {
            typedef metastring_t<'0' + x, args...> type;
        };

        template<int N>
        struct trigger_overflow_warning_t final
        {
            static constexpr char value() noexcept
            {
                return N + 256;
            }
        };
    }

    template<int x>
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

    template<int x>
    constexpr typename numeric_string_t<x>::type numeric_string_t<x>::value;

    template <int N, int M, typename Enable = void>
    struct is_same_number_t final
    {
        static constexpr bool value = true;
    };

    template <int N, int M>
    struct is_same_number_t<N, M, typename std::enable_if<N != M>::type>
    {
        static constexpr bool value = detail::trigger_overflow_warning_t<N>::value() == detail::trigger_overflow_warning_t<M>::value();
    };
}
