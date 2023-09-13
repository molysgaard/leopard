# Leopard - Robust and fast sparse symmetric matrix factorization
Leopard is a fast, modern implementation of sparse, multifrontal symmetric indefinite matrix factorization.
It lets you factorize and solve for large sparse matrices _much_ faster than what is possible using dense methods.

Sparse symmetric indefinite matrices are crucial for efficient constrained optimization. Most available solvers for these
systems are both closed source and have "call us" pricing.
I believe that this has hampered development of constrained optimization solvers quite a lot, as the barrier for experimenting with new
algorithms becomes large both with respect to time, calling and making an appointment for a license, and in money as these linear solvers
cost considerable money to license.

Leopard is free to download and use as you see fit, without any strings attached.


# Installation:

## Ubuntu/Debian
Leopard is distributed as a `.deb` package, see [Releases](https://github.com/molysgaard/leopard/releases)

Leopard is compiled in a portable way, and the same `.deb` is tested to run on Ubuntu 16.04, 18.04, 20.04, 22.04, and 23.04, and Debian Buster, Bullseye and Bookworm.

## Manual installation
Download a release of Leopard from the [Releases](https://github.com/molysgaard/leopard/releases) section.
Copy `libleopard.so` and `leopard.h` to the desired location, e.g. `/usr/lib/libleopard.so` and `/usr/include/leopard.h`.
You can now use `#include <leopard.h>` in your `C/C++` project, remember to link with `-lleopard`. For other languages, standard FFI functionality will let you use Leopard, eg. Fortran, Python, Java, etc. *If you would like to see first class support for a specific language, please file an [issue](https://github.com/molysgaard/leopard/issues/new) and I will give it priority.*

# How to use leopard in your aplication:
*I would like to see Leopard being used in all sorts of exciting applications!*

*Please crate an issue if you want to see a new feature, or an example of how to integrate Leopard into your build system or programming language*

## CMake (C++/C/Fortran)
See example at [./cmake](./cmake)

## Universal C-api
Leopard is exposed as a `C`-header, and a Linux compatible dynamic library.
It has no system dependencies except `libc, libm, and pthreads`, and should run on any recent Linux distro.
If not, please file an [issue](https://github.com/molysgaard/leopard/issues/new).

To use Leopard, you will need to include the `leopard.h` header file into your project, and link your resulting executable with the `libleopard.so` library.
If you have any issues using the library, please file an [issue](https://github.com/molysgaard/leopard/issues/new)

# Documentation

## Examples
There is a basic self-contained example in the `cmake` subdirectory: [cmake/src/example.cpp](cmake/src/example.cpp).

## API-documentation
The header `leopard.h` contains the required API-documentation for solving sparse linear systems.
If you find anything confusing, please file an [issue](https://github.com/molysgaard/leopard/issues/new).

# Source code
Leopard is free to use, the source is closed.

I am developing Leopard as a passion project, and believe that the library can bring utility
to a lot of software developers even though the source is closed.

Software that is not used is not usefull.
If you require new features or functionality from the library, I would be excited to add them. Please file an [issue](https://github.com/molysgaard/leopard/issues/new) and I will help you out.

Leopard is a from-scratch development, containing no GPL or similarly licenced code.