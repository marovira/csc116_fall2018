# Constructors
We have seen what constructors are, and we know that the compiler can generate a
default set for us. What we will focus on know is in *how* constructors go about
creating the new instance of the object. Consider the following example:

```c++
class Widget
{
public:
    Widget() :
        mNum{0}
    {
        std::cout << "In constructor" << std::endl;
    }

private:
    int mNum;
};
```

Suppose that we ran this code. The question is the following: what happens
first? Does `mNum` get initialized *before* or *after* the print statement
inside the constructor?

The way constructors work is as follows:

1. A new block is created with the space necessary for the new object.
2. Blocks for each member variable is created in *descending* order of
   declaration.
3. If there is a constructor declaration that is **not** default and contains
   `:`, then the initializations marked here take place. These are performed in
   *descending* order of declaration.
4. The code inside the `{}` (if any) of the constructor is executed.

## Order of Initialization
There are a few points to touch on with this process. First is the notion of the
order in which member variables are created/initialized. Since there is no
sensible way in which the compiler should be required to create and initialize
variables, the standard elects to follow the order of declaration in the class.
This means that the compiler will create (and initialize) variables starting
with the first one, and so on until the final variable is created.

If the user does not provide a constructor or marks a constructor as default,
then the compiler is **not** required to initialize any variables. In some
instances, some compilers may choose to initialize regardless, but you should
not assume this is always the case (g++ and clang certainly don't).

Say that we have the following class declaration:

```c++
class Widget
{
public:

private:
    int mNum, mVar;
    float mFloat;
};
```

Then the compiler will create the member variables in this order: `mNum`,
`mVar`, `mFloat`. Now suppose that we write our own constructor and we
write the following:

```c++
class Widget
{
public:
    Widget() :
        mNum{0},
        mVar{0},
        mFloat{0.0f}
    {  }

    //...

};
```

Then the variables will be initialized in the order provided (notice that this
matches the order in which the variables are declared). The issue here is that
the user could very well decide to initialize *some* variables (or none of
them). Furthermore, the variables could be initialized in a different order than
the one they were declared in. 

In the first case, the variables that are not *explicitly* initialized will be
left in an uninitialized state (again, the compiler may elect to initialize the
rest, but you should not assume this to be the case). But what if the variables
are initialized in a different order?

```c++
class Widget
{
public:
    Widget() :
        mFloat{0.0f},   // Warning: field mVar will be initialized after mFloat
        mNum{0},
        mVar{0}
    {  }

    //...

};
```

This is as far as the compiler will warn us in the event that we initialize the
variables in a different order. As a general rule the compiler is smart enough
to re-organize this itself to make sure the order is consistent, though this may
not always happen. The reason why this is such a problem is because the order of
creation/intialization is closely tied to the order of destruction. So closely
in fact, that the order of destruction is the **reverse** of the order of
creation. 

If we think about this for a minute, it makes sense. Once we create member
variables, it makes sense to destroy them in reverse order, starting with the
last variable that we created and ending with the first. This is the reason why
the compiler gives a warning about initializing in a different order: because
the order of intialization no longer matches the order of creation (and
therefore doesn't match the order of destruction). Again, normally this is not a
problem since the compiler is smart enough to figure this out (hence why this is
just a warning and not an error) but it should still be avoided regardless.

The same rule applies to any member variables that are themselves objects. The
difference here is that the compiler will initialize them even if the user
doesn't do so directly. This is accomplished by invoking their own constructors.
Consider the following:

```c++
class Widget
{
public:
    Widget() = default;     // Fine, mStr and mVec have their own constructors.

private:
    std::string mStr;
    std::vector<int> mVec;
};
```

In this example, because `mStr` and `mVec` are ultimately objects themselves,
then the compiler will invoke their own constructors in the default constructor
(even if we haven't done this ourselves). The order is still the same as before,
but they get called automatically without our intervention.

## Static Member Functions
All member variables and functions are ultimately tied to a specific instance of
an object. That said, there are times when we want to create functions that
aren't tied to an object instance. To accomplish this, we simply mark a function
as `static`. Typically these functions are used as helpers for the main class,
or can be used to create instances of the class under specific circumstances.
Consider the following example:

```c++
class Mesh
{
public:
    Mesh();

    static bool fromFile(std::string const& filename, Mesh& mesh);

};
```

Without diving into the details of the Mesh class itself, let us try to
understand why `fromFile` is declared as static. In computer graphics, a mesh is
a collection of vertices which form triangles. These can then be used to
represent objects (such as trees, characters, etc.). Generally, we create meshes
by loading them from files. Since opening and parsing a file is such a complex
process that has several things that can go wrong, it is probably not a good
idea to have this be a constructor. Recall that constructors are not allowed to
fail unless its by exception. In this instance, failing to open a file should
not lead to an exception. Instead, we simply ignore the file and the mesh is not
loaded. This presents us with a bit of a problem: we want to create a mesh from
a file, but we don't want to have this as a constructor. While we could have it
as a member function, it would require us to make the Mesh "aware" of the fact
that it can be loaded from a file, which it shouldn't need to know. This results
in the function being marked as `static`. It enables us to have a function that
does **not** require an instance of a class, but still have access to it's data
members (since it's in the same scope) and perform operations on **any**
instance of the class (or anything really). 

> **Aside:**
> The existence of `static` member functions allows the creation of a very
> common (and much maligned) patter called the static singleton. This is
> commonly used to wrap classes that need to be **globally** accessible.
> Examples of this are logging systems, asset databases, etc.
