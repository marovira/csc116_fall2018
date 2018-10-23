#include <iostream>
#include <vector>
#include <string>

class Widget
{
public:
    Widget() : 
        mNum{0},
        mVar{0},
        mVal{0.0f}
    {
        std::cout << "Size of mVec: " << mVec.size() << std::endl;
        std::cout << "Size of mStr: " << mStr.size() << std::endl;
        std::cout << "mNum = " << mNum << std::endl;
        std::cout << "mVar = " << mVar << std::endl;
        std::cout << "mVal = " << mVal << std::endl;
    }

    ~Widget()
    {
        std::cout << "In destructor" << std::endl;
    }

private:
    std::vector<int> mVec;
    std::string mStr;
    int mNum, mVar;
    float mVal;
};

int main()
{
    Widget w;
    return 0;
}
