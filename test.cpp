#include <iostream>
#include <string>
#include "src/urltools.h"


int
main() {
    std::string c1 = u8"a测d试中文";
    std::string out = stun::urlencode(c1);

    std::cout << out << std::endl;

    std::string c2 = stun::urldecode(out);
    std::cout << c2 << std::endl;

    int cmp = c1.compare(c2);
    if (0 == cmp) {
        std::cout << "matched" << std::endl;
    }

    return 0;
}
