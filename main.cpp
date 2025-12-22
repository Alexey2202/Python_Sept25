#include "modular-sorting.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> vec(N);
    for (int& item : vec) {
        cin >> item;
    }
    ModularSort(vec);
    for (int item : vec) {
        cout << item << ' ';
    }
    return 0;
}
