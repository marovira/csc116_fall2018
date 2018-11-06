# Inheritance
We begin our discussion of inheritance with an example. Suppose that we wished
to design some code to represent the interface of Legend of Zelda: Twilight
Princess. Consider the following reference image:

![alt-text](https://github.com/marovira/csc116_fall2018/blob/master/lectures/images/tloz-tp.jpeg) 

For the sake of simplicity, we are not going to be discussing how things
ultimately get rendered on to the final frame, nor will we be discussing the
design of a game engine. Instead, we will be examining a very simplified version
of the behaviour that the UI elements need to have. In summary, we need the
following:

* An element for the health,
* An element with the minimap, collection screen, and Midna,
* An element for the dungeon map,
* An element for the rupee count, and
* An element for the items we have mapped to our buttons.

For each of these elements, we would want to be able to do the following:

1. Set the position of the item on the screen. For the sake of simplicity,
   assume that we can specify the position as two floating-point values
   representing x and y.
2. A way to set the size of the element.

With this in mind, we could come up with the following design for the health
bar:

```c++
class HealthBar
{
public:
    // Constructors go here.

    void setPosition(float x, float y)
    {
        mX = x;
        mY = y;
    }

    void setSize(float scale)
    {
        mHeight *= scale;
        mWidth *= scale;
    }
    
private:
    float mX, mY;
    float mHeight, mWidth;
    // More data here.
};
```

Notice that the implementation for the `setPosition` and `setSize` functions
would be *identical* for all elements in the UI. Implementing this by hand would
be incredibly tedious, as we would have to copy the same code over and over. Is
there an easier way of doing this?

## Uses of Inheritance
This showcases a classic example where inheritance is very helpful. We first
begin by defining what we mean by inheritance. The concept that objects are
related to one another in a *hierarchy* is called **inheritance**. The hierarchy
is represented by two main elements:

* **Base objects:** also known as parent or super-classes. These represent all
  of the common elements (data and functions) that all other elements in the
  hierarchy have.
* **Derived objects:** also known as child or sub-classes. These will *inherit*
  their common traits from the parent class.

There are two main types of inheritance in C++:

* *Implementation Inheritance:* This is used to avoid having to copy shared
  functions (or data) across related classes. Instead, we bundle everything into
  a single base class and the remaining classes simply inherit from it, gaining
  all of the shared functionality.
* *Interface Inheritance:* also referred to as polymorphism. This is the concept
  that the base class simply represents a list of requirements that all others
  that follow the interface must follow. 

We will focus on implementation inheritance first, leaving polymorphism for
later.

## Implementation Inheritance
Let us return to our example from Twilight Princess. Since all elements in our
list need to have the same two functions, we can use implementation inheritance
to bundle these two functions (and indeed the data itself) into a common base
class. The elements themselves then become child classes and inherit from this
base. Let us see how this would be setup.

```c++
class UIBase
{
public:
    // Constructors go here.

    void setPosition(float x, float y)
    {
        // Same as above.
    }

    void setSize(float scale)
    {
        // Ditto.
    }

private:
    float mX, mY;
    float mHeight, mWidth;
};
```

Our `HealthBar` class would then become the following:

```c++
class HealthBar : public UIBase
{
public:
    // Constructors here.

};
```

By adding `: public UIBase` we have now made `HealthBar` a child of `UIBase`.
That means that it now has access to any and all member functions and data that
the parent class defines that is *accessible* to the child class. 

## `protected` Members
So what do we mean by any member functions and data that is *accessible*? Well,
clearly the child has access to any member defined as `public`. But what about
`private`? We can answer this question easily by noting that the child class is
**not** defined inside the scope of the parent class. As a result, it does
**not** have access to any functions or data marked as `private`. This
represents a problem, since we might need access to the private members of the
base class. 

Let us look at the equipped item element, which we will define in the
`EquippedItems` class. We have 4 images, all of which need to be placed around a
central point, with one offset slightly. Suppose that each button is a separate
image (fairly common in video games). In order to determine the position of each
image we need to know the centre. Assuming that the centre is represented by the
position coordinates, then we need access to the coordinate variables, which
unfortunately are declared as `private`. Making these `public` is not an option,
since it violates encapsulation, so we need a different option: `protected`.

Recall that:

* `public`: anyone outside the class can access.
* `private`: only things declared in the class-scope can access.

Then `protected` means that only things declared in the class-scope and that
**inherit** from the class can access. With this in mind we can simply change
the `UIBase` to the following:

```c++
class UIBase
{
public:
    // Constructors go here.

    void setPosition(float x, float y)
    {
        // Same as above.
    }

    void setSize(float scale)
    {
        // Ditto.
    }

protected:
    float mX, mY;
    float mHeight, mWidth;
};
```

The `EquippedItems` class now has access to the data and can do whatever it
needs with it.

## Overriding our Parent
Let us go back to the `HealthBar` class and consider the `setPosition` function.
Suppose that the position that is currently held by the base class represents
the centre of the health bar. Since we also need to set the position of the
hearts, we would need to modify the `setPosition` function to allow us to do
this as well (or at least invoke a separate function that does it). The question
is: how do we do this?

A first attempt would be to simply define a `setPosition` function inside the
`HealthBar` class and make it do what we want. This would look as follows:

```c++
class HealthBar : public UIBase
{
public:
    // Constructors here.

    void setPosition(float x, float y)
    {
        // Do stuff here.
    }

};
```

This seems to solve the problem, but we have accidentally created another.
Suppose that the `UIBase` class also has a function called `draw()`. Without
getting into the semantics of how elements are rendered, suppose that the `draw`
function needs to invoke `setPosition`. The declaration of `UIBase` now looks
like this:

```c++
class UIBase
{
public:
    // Constructors go here.

    void setPosition(float x, float y);

    void setSize(float scale);
    void draw();

protected:
    float mX, mY;
    float mHeight, mWidth;
};
```

And the implementation (`.cpp` file) looks like this:

```c++
void UIBase::setPosition(float x, float y)
{
    // ...
}

void UIBase::setSize(float scale) 
{
    // ...
}

void UIBase::draw()
{
    // ...
    setPosition(x, y);
    // ...
}
```

Given that we have re-implemented `setPosition` in the child, which version gets
invoked in the parent?

As it happens, the parent will invoke its *own* version of `setPosition`,
**not** the child's. This is a problem, since we do want the base class to use
our version of the function.

## `virtual` and `override`
The solution to this problem is to declare the `setPosition` function as
`virtual`. The `virtual` keyword has the following effect: any child class that
wishes to override the function can do it, but **there is no requirement to do
so**. The declaration of `UIBase` now looks like this:

```c++
class UIBase
{
public:
    // Constructors go here.

    // Child classes can now override this.
    virtual void setPosition(float x, float y);

    void setSize(float scale);
    void draw();

protected:
    float mX, mY;
    float mHeight, mWidth;
};
```

And the `HealthBar` class now looks like this:

```c++
class HealthBar : public UIBase
{
public:
    // Constructors here.

    void setPosition(float x, float y) override;

};
```

The `HealthBar` class is now free to override the virtual function declared in
the base class and this ensures that the child's version gets invoked.

> **Note:**
> The `override` keyword acts in a similar way to uniform initialization. If we
> omit it, the compiler will not complain. However, by adding it we force the
> compiler to check if the function we are overriding was indeed virtual. As a
> general rule, it is a good idea to always add this keyword when you override a
> virtual function.

> **Warning:**
> Do not override functions that are not declared `virtual`. For the reasons we
> have seen, this leads to a lot of confusion and hard to find bugs.

Once a function has been overriden, we can do whatever we want inside. That
said, there are times we don't necessarily want to rewrite the parent function,
we only want to *extend* its functionality. Since copying the same code is not
advisable, we can instead invoke the base class' version of the function inside
the child. Going back to our example, the `HealthBar` class still needs to set
the provided position in `mX` and `mY`, in addition to setting the positions of
the hearts. So instead of re-writing the code for it, we just do this:

```c++
// This is in the .cpp file
void HealthBar::setPosition(float x, float y)
{
    UIBase::setPosition(x, y);  // Invoke the parent's version of setPosition.
    // Now do the rest.
}
```

## Last keyword: `final`
We have seen how we can inherit one class for another. This chain can go on for
as long as we want/need. But what if we have a class that we don't want
**anyone** to inherit from?
To accomplish this, we simply mark the class as `final` like this:

```c++
class A final : public Base
{
    // ...
};
```

By doing this, we are saying that this class cannot be inherited from, and it
will be enforced by the compiler.
