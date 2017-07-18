# baselib

A simple library implementing low-level structures and algorithms for C

This library is still growing, but for the moment it implements:

- Linked Lists
- Array Lists


# To compile: the library

Simply run `build.sh' and then `sudo ./install.sh' in the project's root directory


# To compile: against the library

When using GCC, add the options `-lbaselib -lpthread'. Linking to pthread is required as
the posix threads is used within baselib for the purposes of making the lists thread-access safe

