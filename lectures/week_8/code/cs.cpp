#include <iostream>

class Complex
{
public:
    Complex() :
        mReal{0.0f},
        mImaginary{0.0f}
    {
        std::cout << "Default constructor" << std::endl;
    }

    Complex(float r, float i) :
        mReal{r},
        mImaginary{i}
    {
        std::cout << "Parametrized constructor" << std::endl;
    }

    Complex(Complex const& c) :
        mReal{c.mReal},
        mImaginary{c.mImaginary}
    {
        std::cout << "Copy constructor" << std::endl;
    }

    Complex& operator=(Complex const& rhs)
    {
        std::cout << "Copy assignment operator" << std::endl;
        mReal = rhs.mReal;
        mImaginary = rhs.mImaginary;
        return *this;
    }

    Complex& operator+=(float rhs)
    {
        mReal += rhs;
        return *this;
    }

    Complex operator+(float rhs)
    {
        Complex result{*this};
        result += rhs;
        return result;
    }

    void print() const
    {
        std::cout << mReal << " + " << mImaginary << "i" << std::endl;
    }

private:
    float mReal, mImaginary;
};

void foo(Complex const& c)
{
    c.print();
}

int main()
{
    Complex a;
    Complex b{1, 2};
    a = b;
    a += 5.0f;
    foo(b);
    return 0;
}
