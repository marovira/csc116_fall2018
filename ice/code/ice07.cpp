/**
 * In-class exercise 7: Nienna
 * Given the vector class as defined below, write a syntactically correct C++
 * operator times (including the function signature) that implements the dot
 * product of two vectors. Recall that the dot product of two vectors is defined
 * as x1*x2 + y1*y2. Your solution must work with all inputs, not just the one
 * provided below.
 */
#include <iostream>

class Vector
{
public:
    Vector(float x, float y) :
        mX{x},
        mY{y}
    {  }

    // Your operator here.
    float operator*(Vector const& rhs)
    {
        return (mX * rhs.mX) + (mY * rhs.mY);
    }

private:
    float mX, mY;
};

int main()
{
    Vector x{1.0f, 3.0f}, y{2.0f, 4.0f};
    auto dot = x * y;
    std::cout << "x * y = " << dot << std::endl;
    return 0;
}
