# Development Environments for CSc 116

## Compilers and Build Environments
C++ development can be done in a variety of ways, and you are free to use
whichever method you prefer when developing and testing your code. The
environment in the labs is currently setup to work correctly with your
assignments, and may be easier than manually setting things up in your own
machine. That being said, it may be useful to have a setup in your own machine.
You can use an IDE such as Visual Studio (Windows), XCode (OSX), or others in
Linux, or you can use a simple text editor to edit and compile manually through
the command line. The labs will focus on this method.

There are many options for text editor, however we recommend the following:

* [Atom](https://atom.io/) (all platforms),
* [Sublime Text](https://www.sublimetext.com/3) (all platforms),
* [Notepad++](https://notepad-plus-plus.org/) (Windows only),
* [TextWrangler](https://www.barebones.com/products/textwrangler/) (OSX only)

Modal text editors such as Vim or Emacs are not recommended as they have a steep
learning curve. That said, if you are experienced in them, then they are a
fantastic choice.

## Sample program

Once you have your compiler and environment setup, it is a good idea to test the
compiler with a simple program to ensure that all the features are supported.
Some compilers require special flags to be passed in to enable certain features,
such as `-std=c++17` for `g++`. The following sample program contains some of
the features that will be required for this course. If it compiles and runs
correctly, then you can assume it will work for this course. That said, it is
advised that you check your code on the lab machines to ensure there are no
problems with your assignments.

```c++
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers{1, 2, 3, 4, 5};
    int sum{0};
    for (auto& num : numbers)
    {
        sum += num;
    }

    std::cout << "The sum is " << sum << std::endl;
    return 0;
}
```

## Command-line Compilation
The following command uses `g++` to compile a C++ source file called
`example.cpp` to a program called `example`. Note that the name of the program
can be changed to be anything you want, though you should be careful to not name
the program the same as your source file, as it will destroy the source code.

```sh
g++ -pedantic -Wall -Wextra --std=c++17 -o example example.cpp
```

If your compiler produces an error like `unrecognized command line option
--std=c++17` you may need to substitute `--std=c++1y` of `--std=c++14` for
`--std=c++17`.

`-Wall` and `-Wextra` enable extra warnings, while `-pedantic` forces the
compiler to treat all warnings as errors. You should remember that these flags
will be used during marking (and code that does not compile with the flags will
receive a mark of zero).

## Compiler and Development Environment Installation

### OSX
Depending on your setup, `g++` may already be installed. To check if this is the
case, open a Terminal window (`CMD + Space` and then type "terminal") and type
`g++`. If the output is `fatal error: no input files`, then `g++` is installed
on your system. Otherwise, you will need to install `g++`. To do so, go to the
App Store and download XCode. This will install all of the required tools.

### Windows
A prepackaged set of C++ tools has been prepared for you. The link is provided
through our conneX site under "WinC++". Follow the instructions there to setup
the compiler in your system.

If you wish to use Visual Studio, you can download it
[here](https://visualstudio.microsoft.com/downloads/) (choose the Community
edition). As far as the command-line options for Visual Studio, here are the
equivalences:

* `-Wall`, `-Wextra`: `/Wall`, `/W4` set this under 'Properties -> C/C++ ->
  General -> Warning Level'
* `-pedantic`: `/WX` set this under 'Properties -> C/C++ -> General -> Treat
  Warnings as errors'
* `--std=c++17`: `/std:c++17` set this under 'Properties -> C/C++ -> Language ->
  C++ Language Standard'

It is preferable that you employ the provided compiler, as it requires a lower
setup time. That said, if you wish to use Visual Studio and require help, you
may come to my office hours or make an appointment for assistance.
