#include <memory>
#include <iostream>

using IntPtr = std::shared_ptr<int>;

void foo(IntPtr ptr)
{
    (*ptr)++;
}

void bar(IntPtr const& ptr)
{
    std::cout << *ptr << std::endl;
}

int main()
{
   IntPtr p = std::make_shared<int>(10);    // Counter is now 1.
   auto c = p;                              // Copy made. Counter is 2.
   {
       auto d = c;                          // Copy made. Counter is 3. 
   }
                                            // d is destroyed. Counter is 2.
   foo(c);                                  // c is passed by copy. Counter is 3.
                                            // copy destroyed. Counter is 2.

    bar(c);                                 // c is passed by const&. Counter is 2.
    return 0;
    // Destruction occurs in reverse order of creation.
    // Destroy c first. Counter is 1.
    // Destroy p next. Counter is now 0. Data is now cleared.
}
