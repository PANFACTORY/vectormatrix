#include "mat.h"

using namespace PANSFE;

int main() {
    //  各種コンストラクタ
    Mat<int> a, b(2, 3), c(2, 3, 2), d = c;
    std::cout << a << std::endl << b << std::endl << c << std::endl << d << std::endl;

    //  メンバへのアクセス
    b[1][2] = 2.0;
    c(0, 1) = 3.0;
    std::cout << b << std::endl << c << std::endl;

    Mat<int> e = { { 1 }, { 2 }, { 3 } };
    std::cout << e << std::endl;
}