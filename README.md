# baselib

A simple library implementing low-level structures and algorithms for C. this library was designed for use on POSIX systems, and will likely not work as intended on non-POSIX systems. 

This library (at the moment) implements:

- linked lists
- array lists
- basic string manipulation
- string building functions
- basic file tools
- unicode encoding (UTF-8, UTF16 (BE/LE), AND UTF-32 (BE/LE))
- task / thread management (still unstable)

This library will implement in the future:

- UTF-7 unicode encoding
- advanced string manipulation
- hash tables / dictionaries
- Doubly linked lists


# To compile the library

Simply run `build.sh` and then `sudo ./install.sh` in the project's root directory


# To compile against the library

When using GCC, add the options `-lbaselib -lpthread`. Linking to pthread is required as
the posix threads library is used within baselib for the purposes of making the lists 
thread safe. The header file containing all the non-encapsulated declarations for the library
should be included via `#include <baselib/baselib.h>`

