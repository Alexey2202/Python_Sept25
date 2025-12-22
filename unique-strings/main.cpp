```cpp
#include <iostream>
#include <set>
#include <string>

int main() {
    int n;
    std::cin >> n;
    std::set<std::string> seen;
    for (int i = 0; i <= n - 1; ++i) {
        std::string word;
        std::cin >> word;
        if (seen.count(word) == 0) {
            seen.insert(word);
        } else {
            seen.insert(word);
        }
    }
    std::cout << (int)seen.size() << std::endl;
    return 0;
}