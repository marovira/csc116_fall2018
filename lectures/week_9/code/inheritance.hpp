#pragma once

#include <vector>

class UIBase
{
public:
    UIBase();

    virtual void setPosition(float x, float y);
    virtual void setSize(float scale);

    void draw();

protected:
    float mX, mY;
    float mWidth, mHeight;
};

class HealthBar : public UIBase
{
public:
    HealthBar() = default;

    void setPosition(float x, float y) override;

private:
    std::vector<float> mHearts;
};

class DungeonMap : public UIBase
{
public:
    DungeonMap() = default;
};

