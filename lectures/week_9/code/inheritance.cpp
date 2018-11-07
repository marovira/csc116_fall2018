#include <iostream>
#include "inheritance.hpp"

UIBase::UIBase() :
    mX{0.0f},
    mY{0.0f},
    mWidth{1.0f},
    mHeight{1.0f}
{  }

void UIBase::setPosition(float x, float y)
{
    mX = x;
    mY = y;
    std::cout << "Position: (" << mX << ", " << mY << ")" << std::endl;
}

void UIBase::setSize(float scale)
{
    mWidth *= scale;
    mHeight *= scale;
    std::cout << "Size: " << mWidth << " x " << mHeight << std::endl;
}

void HealthBar::setPosition(float x, float y)
{
    // Invoke the parent's setPosition.
    UIBase::setPosition(x, y);

    // Now set the hearts.
    float const delta = 1.0f;
    int i = 0;
    for (auto& heart : mHearts)
    {
        heart = x + (i * delta);
        ++i;
    }
    std::cout << "Hearts set" << std::endl;
}

int main()
{
    DungeonMap map;
    map.setPosition(1.0f, 3.0f);
    map.setSize(5.0f);

    HealthBar bar;
    bar.setPosition(0.0f, 10.0f);
    bar.setSize(3.0f);

    return 0;
}
