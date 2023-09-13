# leopard

_leopard_ is a linear, symmetric, positive definite or indefinite solver.
The basis of the algorithm is a multifrontal factorization, that can handle indefinite cases with numerical pivoting.

The solver itself consists of a single header `leopard.h` describing the API and an accompanying `.so` file containing the code.
Any programming language able to call C-functions should be able to use the header and `.so` file to use the solver.

# Running the examples
From the root folder of the project
```
mkdir build
cd build
cmake ..
make
./leopard-test
```


# How to use
Generally speaking there are two things that need to be done:
1. Include the `leopard.h` header to expose the _leopard_-API to your application.
2. Link your application with `libleopard.so` so that the final binary can run _leopard_ code.

A `.zip` with `leopard.h` and `libleopard.so` is available at: https://leopard-releases.mortenlysgaard.com/leopard-v0.1.0.zip

## CMake integration
See `CMakeLists.txt` for an example of how to integrate the solver into your CMake project.

## Custom build system integration
For other build systems, a similar approach to what is done in `CMakeLists.txt` can be used.
I would really like to see _leopard_ being used in the wild, and thus I would be happy to assist and help in integrating into your specific build system.
