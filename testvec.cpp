#include "vec.h"

using namespace PANSFE;

int main() {
    //  各種コンストラクタ
    Vec<int> a, b(3), c(4, 2), d = { 1, 2, 3 }, e = d;
    std::cout << a << std::endl << b << std::endl << c << std::endl << d << std::endl << e << std::endl;  

    //  メンバへのアクセス
    std::cout << a.Size() << "\t" << b.Size() << std::endl << std::endl;

    //  代入演算子
    a = b;
    std::cout << a << std::endl;
}