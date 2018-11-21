#include "polymorphism.hpp"

void attack(Sword& sw)
{
    sw.attack();
}

int main()
{
    // Make a Master Sword instance.
    MasterSword masterSword;

    // Now pass it to attack.
    attack(masterSword);

    // We can also cast it into it's parent.
    SwordPtr sw = std::make_shared<MasterSword>();

    std::cout << "Power: " << sw->attackPower() << std::endl;

    // Now let's cast it back to the child
    MasterSword* ms = dynamic_cast<MasterSword*>(sw.get());
    if (ms != nullptr)
    {
        std::cout << "Successful cast" << std::endl;
    }

    // We can do the same thing with references.
    Sword& sw2 = masterSword;

    try
    {
        auto ms2 = dynamic_cast<MasterSword&>(sw2);
    }
    catch (std::exception& e)
    {
        // Notice how we are using polymorphism on exceptions too.
        std::cout << e.what() << std::endl;
    }

    return 0;
}

