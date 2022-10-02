# VectorMatrix

is a linear algebraic library contains vector and matrix for C++.  
This is a header only library.

## CI

|                                                                               Status                                                                                |       Environment        |
| :-----------------------------------------------------------------------------------------------------------------------------------------------------------------: | :----------------------: |
| [![Test](https://github.com/PANFACTORY/vectormatrix/actions/workflows/cmake.yml/badge.svg)](https://github.com/PANFACTORY/vectormatrix/actions/workflows/cmake.yml) | ubuntu-latest(g++ c++11) |

## Example

Create `main.cpp` and type the following code.

```
#include <iostream>

#include "src/vec.h"
#include "src/mat.h"

using namespace PANSFE;

int main() {
    Mat<double> A = {{1, 2}, {3, 4}};
    Vec<double> b = {5, 6};
    std::cout << A*b << std::endl;
    return 0;
}
```

Build and run with the following commands(, for example, use clang++).  

```
clang++ -I <Your Include Path> ./main.cpp
./a.exe
```

Then you can get the response as below.  

```
17
39
```

## Document
- [Document](https://panfactory.github.io/vectormatrix/)

## Dependency
- Google Test
- Doxygen

## License
- [MIT](https://github.com/PANFACTORY/vectormatrix/blob/main/LICENSE)
