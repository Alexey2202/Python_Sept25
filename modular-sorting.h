#pragma once
#include <vector>
#include <algorithm>
#include <cmath>

void ModularSort(std::vector<int>& v) {
    // TODO: implement me
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return abs(a) < abs(b);
    });
}