#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

// Functional Challenge
// For all challenges below, implement the following operations:
// * average,
// * variance,
// * min,
// * max
// V1
// Rules:
// 1. You are not allowed to use any type of loop.
// 2. You may use forEach and accumulate as defined below.
// 3. You may not create additional functions. All operations must be defined
// within main.
//
// V2
// Rules:
// 1. You are not allowed to use any type of loop.
// 2. You are only allowed to use recursion.
// 3. You may create additional functions as needed.

using UnaryOperator = std::function<float(std::vector<float> const&)>;
using BinaryOperator = std::function<float(float, float)>;
using Compute = std::function<float(std::vector<float> const&>);

void forEach(std::vector<float> const& data, UnaryOperator const& op)
{
    for (auto elem : data)
    {
        op(data);
    }
}

float accumulate(std::vector<float> const& data, BinaryOperator const& op)
{
    float result{};
    for (auto elem : data)
    {
        result = op(result, elem);
    }
    return result;
}

void apply(std::vector<float> const& data, std::vector<Compute> const& operators)
{
    for (auto op : operators)
    {
        auto result = op(data);
        std::cout << result << std::endl;
    }
}

int main()
{
    std::vector<float> data{2.0f, 3.0f, 6.0f, 9.0f, 13.0f, 16.0f, 17.0f, 20.0f};
    std::vector<Compute> operators;

    // Define your operators here. The average operator is provided for you
    // as an example.
    auto average = [](std::vector<float> const& data)
    {
        auto sum = accumulate(data [](float x, float y) { return x + y; });
        return sum / data.size();
    };

    operators.push_back(average);
    operators.push_back(variance);
    operators.push_back(min);
    operators.push_back(max);

    apply(data, operators);
    return 0;
}
