#include <iostream>
#include <type_traits>
#include <vector>

template <typename T, typename UnaryFunction>
void forEach(T data, UnaryFunction f)
{
    for (auto elem : data)
    {
        f(elem);
    }
}

template <typename T, typename BinaryFunction, typename U>
U acculumate(T data, BinaryFunction f, U init)
{
    U result{init};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}

template <typename T, typename BinaryFunction>
auto accumulate2(T data, BinaryFunction f)
{
    typename T::value_type result{};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}

template <typename T, typename BinaryFunction>
auto accumulate3(T data, BinaryFunction f) -> typename std::remove_reference<decltype(*data.begin())>::type
{
    typename std::remove_reference<decltype(*data.begin())>::type result{};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}

template <typename T,
         typename std::enable_if<std::is_arithmetic<T>::value>>
T abs(T x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

int main()
{
    std::vector<int> data{1, 2, 3, 4};
    auto sum = [](int x, int y) { return x + y; };
    std::cout << acculumate(data, sum, 0) << std::endl;
    std::cout << accumulate2(data, sum) << std::endl;
    std::cout << accumulate3(data, sum) << std::endl;

    auto a = abs(3.0f);

    return 0;
}
