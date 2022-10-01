#include "vec.h"

using namespace PANSFE;

int main() {
    //  各種コンストラクタ
    Vec<int> a, b(3), c(4, 2), d = {1, 2, 3}, e = d;
    std::cout << a << std::endl
              << b << std::endl
              << c << std::endl
              << d << std::endl
              << e << std::endl;

    //  メンバへのアクセス
    std::cout << a.Size() << "\t" << d[1] << "\t" << e(2) << std::endl
              << std::endl;

    //  演算子
    std::cout << 2 * (e + d * 5) << std::endl;

    //  代入演算子, 複合代入演算子
    a = b;
    b -= d;
    e ^= d;
    std::cout << a << std::endl << b << std::endl << e << std::endl;
}
