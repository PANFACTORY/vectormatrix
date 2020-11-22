#include "mat.h"

using namespace PANSFE;

int main() {
    //  各種コンストラクタ
    Mat<int> a, b(2, 3), c(2, 3, 2), d = c;
    std::cout << a << std::endl << b << std::endl << c << std::endl << d << std::endl;  

}