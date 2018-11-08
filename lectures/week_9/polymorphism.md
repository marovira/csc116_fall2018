# Polymorphism
Last time we discussed implementation inheritance. Before we proceed to
interface inheritance (or polymorphism), we first need to talk about the order
of construction and destruction with derived classes.

## Construction and Destruction of Child classes
Recall that the order of construction is as follows:

1. A new block is created with the space necessary for the new object.
2. Blocks for each member variable is created in descending order of
   declaration.
3. If there is a constructor declaration that is not default and contains `:`,
   then the initializations take place in descending order of declaration. If
   any member variables is an object, their default constructors are invoked
   automatically (if available).
4. The code inside the `{}` gets executed (if any).

When dealing with a derived class, the same order of construction applies. The
only difference is that **before** step 3 happens, the base class will get
constructed. In other words, the base class constructor will always be invoked
**prior** to the initialization of the members. If the base class has a default
constructor, it gets invoked automatically. Otherwise it needs to be manually
invoked using `:`.

As expected, destruction works in reverse, with the members being destroyed
**before** the base class itself is destroyed.

## Interface Inheritance (Polymorphism)
Let us continue with our examples from the Legend of Zelda series. In this case,
we will examine the weapons available in Breath of the Wild. Consider the
following two images depicting an inventory from the game:

![alt-text](https://github.com/marovira/csc116-private/blob/master/lectures/images/tloz-bow-swords.jpg) 


In the first image, we have an inventory of swords that the player can use,
while the second showcases bows and arrows. Once again, we will ignore the
implementation details pertaining the game engine and its logic, opting for a
more high-level view of the techniques used.

Let us consider the swords first. Using what we have already learned, we could
propose the following implementation:

* Create a base class called `Sword`. This will contain all of the common data
  between the swords, such as attack power, durability, elemental properties,
  etc. Any common data will be declared protected, and relevant functions will
  be declared virtual.
* For each type of blade, create a class that inherits from the `Sword` and then
  override any functions that need to be modified.

The question we now face is the following: how do we represent a collection of
swords like the one shown in the image? 
Well, we could implement a class called `Bag` that contains a list of swords.
But this has a severe drawback: we would have to write *all* of the swords when
we implement the class. Moreover, any change would require us to re-compile the
code. It will also prevent new swords being dynamically added (such as DLC for
example). We also would have to *write* them all by hand. 

Seeing how we had implementation inheritance to re-use code, it seems reasonable
that we should have a similar trick for this. The trick is called interface
inheritance (or polymorphism).

## Defining the Interface
Let us examine how this could be done. First, notice that from the perspective
of Link, the *type* of the sword is irrelevant. The only thing that matters is
that we can use it to attack, that they have a durability, and any other
relevant information. The *specific* details of how the sword works are not
important, just its functionality. With this in mind, it would make sense to
treat all of the distinct swords as a **single** entity which we have already
defined: `Sword`. This class has now become the **interface** that all swords
have to follow in order for Link to use them. Lets see what the class
declaration would be:

```c++
class Sword
{
public:
    // Constructors here.
    virtual float getDurability() = 0;
    virtual std::string getElement() = 0;
    virtual int getAttackPower() = 0;

protected:
    // Any protected data goes here.
};
```

The functions defined here are called **pure** virtual functions. Recall that a
*virtual* function is one that can be overridden by the child classes, but there
is no obligation to do so. A **pure virtual** function **must** be overridden by
the child class. The reason is the following: pure virtual functions do **not**
have a definition! They only have a declaration. As a result, the compiler has
no idea what the functions even do, which means that it's up to the derived
classes to determine the behaviour of the functions.

## Using the Interface
Let us take an example sword and see how the new interface gets used:

```c++
class MasterSword : public Sword
{
public:
    // Constructors go here.

    float getDurability() override
    {
        return -1.0f;   // Cannot break.
    }
    float std::string getElement() override
    {
        return "Holy sword";
    }

    int getAttackPower() override
    {
        return 30;
    }

    // ...
};
```

Now let's use this in a simplified main:

```c++
int main()
{
    MasterSword sword;
    std::cout << sword.getDurability() << std::endl;
    return 0;
}
```

Up until now, everything is the same as with implementation inheritance. The
only real difference is that pure virtual functions need to be implemented. So
how does this help to solve the `Bag` problem? Consider the following code:

```c++
void attack(Sword& sw)
{
    // Attack with the sword.
}

int main()
{
    MasterSword sw;
    attack(sw);
}
```

So what just happened here? We have just transformed a `MasterSword` into a
`Sword`! How does this work?

It so happens that whenever we derive from a class, we are allowed to transform
the child class into the parent class through casting. This results in the
following:

* Any member functions and data that the child has but the parent doesn't is
  no longer accessible.
* Any virtual member functions that the child class has overridden will point to
  the child class. If they haven't been overridden (or aren't virtual) point to
  the base class.
* Any pure virtual functions in the base class will point to the child class.

There are some restrictions to this, mainly that this type of casting can only
be done through either references or pointers (safely). This is type of
behaviour is known as polymorphism.

## References vs Pointers
With the knowledge of polymorphism in hand, we can now solve the problem that we
encountered when trying to define the `Bag` class. We simply need to create a
vector of `Sword` objects and then insert all of the types of swords that we
currently have into it. Before we do this though, we need to discuss which type
of polymorphism we need: reference or pointers.

References can only be tied to existing objects, whereas pointers can point to
things that have just been created. In the specific case of the `Bag` class,
each sword instance that we push will only be created when we push them in, and
not as isolated variables (which is what we're trying to avoid in the first
place). With that in mind, the `Bag` class will look like this:

```c++
using SwordPtr = std::shared_ptr<Sword>;
class Bag
{
public:
    Bag()
    {
        mSwords.push_back(std::make_shared<MasterSword>());
        mSwords.push_back(std::make_shared<BiggoronSword>());
        // ...
    }

private:
    std::vector<SwordPtr> mSwords;
};
```

A few things are happening here. First we declared a new type called `SwordPtr`
as an alias to `std::shared_ptr<Sword>`. We will be discussing what these are
later on. For now, simply treat these as normal pointers as that is all that we
really need here. The constructor of `Bag` then creates new swords and adds them
to the list using `std::make_shared` (we will discuss what this does later, for
now just know that it creates a new pointer to the type that we provide in the
template parameter).

The `Bag` class is now able to loop through its list of swords and invoke any
function defined by the `Sword` interface, which will in turn invoke the
corresponding version from the child class.

## Explicit casts
These last two examples used implicit casts to convert from the child to the
parent class. If we wanted to be more explicit, we can do the following:

```c++
MasterSword sword;
Sword& sw = dynamic_cast<Sword&>(sword);        // Cast a reference

Sword* sw2 = dynamic_cast<Sword*>(&sword);  // Cast a pointer

```

`dynamic_cast` is a way to **explicitly** cast pointers and references up, down,
and sideways along the inheritance hierarchy. In this case, we used it to cast
upwards from the child (`MasterSword`) to the parent (`Sword`). We can also use
them to cast down:

```c++
MasterSword& sword = dynamic_cast<MasterSword&>(sw);
```

If the `dynamic_cast` is successful, then it will return either the pointer or
reference that we want. If it can't then it will fail, the manner of which
depends on the cast:

* If we are casting a reference, a `std::bad_cast` exception will be thrown.
  This makes sense, since references cannot be null, so the only way out is to
  throw.
* If we are casting a pointer, then the result will be `nullptr`.

> **Warning:**
> In modern C++, you should never use `NULL`. This is a C-idiom that introduces
> ambiguity as to its true meaning, while `nullptr` is **always** a null
> pointer.

So if we wanted to perform casts, we would need to either use a try/catch block
of a check for `nullptr` for safety. In general, we only really use
`dynamic_cast` when we want to either cast from the parent class to the child,
or if we want to turn one child into another (assuming that it's possible).
