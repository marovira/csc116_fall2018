#include <iostream>

class Widget
{
public:
    Widget() :
        mX{0},
        mY{0}
    {  }

    ~Widget() = default;

    void updateWidget(int x, int y)
    {
        mX = x;
        mY = y;
    }

    int const& getX() const
    {
        return mX;
    }

    int& getX() 
    {
        return mX;
    }

    void printPosition() const
    {
        std::cout << mX << ", " << mY << std::endl;
    }

private:
    int mX, mY;

};

int main()
{
    Widget w;

    w.updateWidget(10, 50);
    w.printPosition();

    return 0;
}
