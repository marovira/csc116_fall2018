/**
 * In-class exercise 9: Vaire
 * What is the output of the syntactically correct C++ program below?
 */

#include <iostream>
#include <memory>

class SwordBag
{
public:
    SwordBag() :
        swordCount{0}
    {
        std::cout << "Found sword bag" << std::endl;
    }

    ~SwordBag()
    {
        std::cout << "Lost sword bag" << std::endl;
    }

    int swordCount;
};

using BagPtr = std::shared_ptr<SwordBag>;

void trade(BagPtr const& bag)
{
    std::cout << "Traded sword" << std::endl;
    bag->swordCount--;
}

int main()
{
    std::cout << "Start" << std::endl;
    BagPtr bag = std::make_shared<SwordBag>();
    bag->swordCount += 2;
    {
        auto bag2 = bag;
        trade(bag2);
    }
    std::cout << "End" << std::endl;
    return 0;
}
