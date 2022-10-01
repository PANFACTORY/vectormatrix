#include "mat.h"
#include "vec.h"

using namespace PANSFE;

int main() {
    Mat<int> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Vec<int> b = {1, 2, 3};
    std::cout << A * b << std::endl;

    Mat<int> B = {{1}, {3}, {5}};
    Vec<int> c = A * B;
    std::cout << c << std::endl;

    int d = B.Transpose() * B;
    std::cout << d << std::endl;

    std::cout << A.Hstack(b) << std::endl;
    std::cout << b.Hstack(b) << std::endl;
}
