#ifndef TAREA2_CORE_NUMERIC_H
#define TAREA2_CORE_NUMERIC_H

#include <concepts>
#include <iterator>
#include <cstddef>
#include <string>
#include <cmath>
#include <type_traits>
using namespace std;
namespace core_numeric {
    template <typename T, typename R>
    concept lambda_funciona = requires(R a, T b)
    {
        a(b);
    };

    template <typename C>
    concept Iterable = requires(C c) {
        std::begin(c);
        std::end(c);
    };

    template <typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> std::same_as<T>;
    };

    template <typename T>
    concept Divisible = requires(T a, std::size_t n) {
        { a / n } -> std::convertible_to<T>;
    };


    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a < b } -> std::convertible_to<bool>;
    };

    template <typename T>
    concept Arithmetic = std::integral<T> || std::floating_point<T>;

    template <Iterable C>
    requires Addable<typename C::value_type> && Arithmetic<typename C::value_type>
    auto sum(const C& container) {
        using T = typename C::value_type;
        if constexpr (std::is_integral_v<T>) {
            long long result = 0;
            for (const auto& value : container) {
                result += value;
            }
            return result;
        } else {
            T result{};
            for (const auto& value : container) {
                result = result + value;
            }
            return result;
        }
    }

    template <Iterable C>
    requires Addable<typename C::value_type> &&
             Divisible<typename C::value_type> &&
             Arithmetic<typename C::value_type>
    auto mean(const C& container) {
        std::size_t count = 0;
        for (const auto& value : container) {
            ++count;
        }
        return sum(container) / count;    }

    template <Iterable C>
    requires Addable<typename C::value_type> &&
             Divisible<typename C::value_type> &&
             Arithmetic<typename C::value_type>
    auto variance(const C& container) {
        using T = typename C::value_type;
        std::size_t count = 0;
        auto avg = mean(container);
        T result{};
        for (const auto& value : container) {
            T diff = value - avg;
            result = result + diff * diff;
            ++count;
        }
        return result / count;
    }

    template <Iterable C>
    requires Comparable<typename C::value_type> &&
         (!std::same_as<typename C::value_type, std::string>)
    auto max(const C& container) {
        auto it = std::begin(container);
        auto maximum = *it;
        ++it;
        for (; it != std::end(container); ++it) {
            if (maximum < *it) {
                maximum = *it;
            }
        }
        return maximum;
    }

    template <Iterable C,typename regla>
    requires  lambda_funciona<typename C::value_type, regla > &&
    Addable<typename C::value_type> && Arithmetic<typename C::value_type>
    auto transformacion(const C&container, regla func) {
        using T_in = typename C::value_type;
        using T_out = invoke_result_t<regla,T_in>;
        T_out result{};
        for (auto &valor:container) {
            result = result + func(valor);
        }
        return result;
    }

    template <typename... Args>
    requires (Arithmetic<Args>&&...) && (Addable<Args> && ...)
    auto sum_variadic (const Args... a) {
        using T_comun = common_type_t<Args...>;
        T_comun result{};
        result=(a + ...);
        return result;
    }

    template <typename... Args>
    requires (Arithmetic<Args>&&...) && (Addable<Args> && ...) && (Divisible<Args> && ...)
    auto mean_variadic( Args... a) {
        using T_comun = common_type_t<Args...>;
        if constexpr (std::is_integral_v<T_comun>) {
            return static_cast<double>((a + ...) ) / (sizeof...(Args));
        } else {
            return (a + ...) / static_cast<T_comun>((sizeof...(Args)));
        }
    }
    template<typename... Args>
    requires (Arithmetic<Args>&&...) && (Addable<Args> && ...) && (Divisible<Args> && ...)
    auto variance_variadic (Args... a) {
        using T_comun = common_type_t<Args...>;
        T_comun result{};
        auto count= (sizeof...(Args));
        auto avg = mean_variadic(a...);
        if constexpr (std::is_integral_v<T_comun>) {
            result = 0;
            ((result += pow(static_cast<double>(a) - avg, 2)), ...);
            return result / count;
        } else {
            ((result += (a - avg) * (a - avg)), ...);
            return result / count;
        }
    }

    template<typename T, typename... Args>
    requires (Arithmetic<T>)&&(Comparable<T>)&& (Arithmetic<Args>&&...) && (Comparable<Args>&&...)
    auto max_variadic(T primero, Args... rest) {
        auto maximum= primero;
        //condición ? valor_si_es_cierto : valor_si_es_falso
        ((maximum = (rest > maximum ? rest : maximum)), ...);
        return maximum;
    }




}
#endif //TAREA2_CORE_NUMERIC_H