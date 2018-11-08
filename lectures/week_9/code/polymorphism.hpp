#pragma once

#include <memory>
#include <string>
#include <iostream>

class Sword
{
public:
    Sword()
    {
        std::cout << "Forging sword" << std::endl;
    }

    virtual ~Sword()
    {
        std::cout << "Destroying sword" << std::endl;
    }

    virtual int attackPower() = 0;
    virtual std::string element() = 0;
    virtual int durability() = 0;

    virtual void attack()
    {
        std::cout << "Attacking" << std::endl;
    }
};

using SwordPtr = std::shared_ptr<Sword>;

class MasterSword : public Sword
{
public:
    MasterSword()
    {
        std::cout << "Making Master Sword" << std::endl;
    }

    ~MasterSword()
    {
        std::cout << "Destroying Master Sword" << std::endl;
    }

    int attackPower() override
    {
        return 30;
    }

    std::string element() override
    {
        return "Light";
    }

    int durability() override
    {
        return -1;
    }

    void attack() override
    {
        std::cout << "Light beams" << std::endl;
    }
};
