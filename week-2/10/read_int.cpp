#include "read_int.h"
#include <iostream>

int read_int(const char *prompt) {
    int n = 0;
    std::cout << prompt;
    std::cin >> n;
    std::cin.get();
    return n;
}
