#include "anagrams.h"
#include <iostream>
#include <string>

int main() {
    // TODO: implement me
    std::string a, b;
    std::getline(std::cin, a);
    std::getline(std::cin, b);
    std::cout << (AreAnagrams(a, b) ? "YES" : "NO") << std::endl;
    return 0;
}