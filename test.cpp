#include <iostream>
#include <string>
#include "urltools.h"


int
main() {
    std::string c1 = u8"测试中文";
    std::string out = stun::urlencode(c1);

    std::cout << out << std::endl;

    return 0;
}
