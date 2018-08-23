# clang-list-include-headers

## how to use
```
./clang-list-include-headers main.cpp -- -std=c++11 -Wno-everything 
```

## note

if you found an error like below, run clang with '-v' option to know stdlib header path
```
main.cpp:1:10: fatal error: 'iostream' file not found
#include <iostream>
         ^~~~~~~~~~
1 error generated.
```

e.g. mac os x
```
/usr/local/Cellar/llvm/6.0.1/include/c++/v1
/usr/local/include
/usr/local/Cellar/llvm/6.0.1/lib/clang/6.0.1/include
/usr/include
/System/Library/Frameworks (framework directory)
/Library/Frameworks (framework directory)
```
