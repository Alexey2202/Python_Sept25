#include "table.h"
#include <iostream>

int main() {

    Table<int> t(5, 5);
    auto size = t.Size();
    for(size_t i=0; i < size.first; i++){
        for(size_t j=0; j < size.second; j++)
            t[i][j] = i + j;
    }

    std::cout << "Table" << std::endl;
    for(size_t i=0; i < size.first; i++){
        for(size_t j=0; j < size.second; j++)
            std::cout << t[i][j] << '\t';
        std::cout << std::endl;
    }

    t.Resize(4, 8);
    size = t.Size();
    std::cout << "Resized table" << std::endl;
    for(size_t i=0; i < size.first; i++){
        for(size_t j=0; j < size.second; j++)
            std::cout << t[i][j] << '\t';
        std::cout << std::endl;
    }

    return 0;
}
