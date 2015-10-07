#include <gmpxx.h>
#include <iostream>

int main () {
    std::cout << "Hello, world!" << std::endl;
    mpz_class a, b, c;
    a = "123";
    b = 456;
    c = a + b;
    std::cout << c << std::endl;
    return 0;
}