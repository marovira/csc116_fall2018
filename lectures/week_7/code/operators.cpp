#include <iostream>

class Complex
{
public:
    Complex() :
        mReal{0.0f},
        mImaginary{0.0f}
    {  }

    Complex(float r, float i) :
        mReal{r},
        mImaginary{i}
    {  }

    void print() const
    {
        std::cout << mReal << " + " << mImaginary << "i" << std::endl;
    }

    // plus operator. Remember that the left-hand side operand is the class
    // itself.
    Complex operator+(float rhs)
    {
        Complex c{mReal + rhs, mImaginary};
        return c;
    }

    Complex operator+(Complex const& rhs)
    {
        Complex c{mReal + rhs.mReal, mImaginary + rhs.mImaginary};
        return c;
    }

    // Declaration of the friend operator.
    friend Complex operator+(float lhs, Complex const& rhs);

private:
    float mReal, mImaginary;
};

// Now we provide the implementation of the friend operator.
Complex operator+(float lhs, Complex const& rhs)
{
    Complex c{rhs.mReal + lhs, rhs.mImaginary};
    return c;
}

int main()
{
    Complex u, v{1.0f, 2.0f};
    u.print();
    v.print();

    u = u + 2.0f;       // Fine, lhs is Complex, use member operator.
    u.print();

    v = u + v;          // Fine, lhs and rhs are Complex, use other operator.
    u.print();

    v = 5.0f + v;       // Fine, lhs is now float, use friend operator.
    v.print();

    return 0;
}
