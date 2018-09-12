# baselib

A simple library implementing low-level structures and algorithms for C. this library was designed for use on POSIX systems, and will likely not work as intended on non-POSIX systems. 

This library (at the moment) implements:

- linked lists
- array lists
- some list sorting methods
- basic string manipulation
- hash tables / dictionaries
- string building functions
- basic file tools
- unicode encoding (UTF-8, UTF-7, UTF16 (BE/LE), AND UTF-32 (BE/LE))
- ISO/IEC-8859 encoding (1 through 16)
- task / thread management (still unstable)
- integer parsing

This library will implement in the future:

- advanced string manipulation
- doubly linked lists


# To compile the library

Simply run `make` and then `sudo ./install.sh` in the project's root directory to compile and install, respectively


# To compile against the library

When using GCC, add the options `-lbaselib -lpthread`. Linking to pthread is required as
the posix threads library is used within baselib for the purposes of making the lists 
thread safe. The header file containing all the non-encapsulated declarations for the library
should be included via `#include <baselib/baselib.h>`

