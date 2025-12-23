#include "ArrayStat.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <iostream>

int main() {
    return 0;
}

ArrayStat::ArrayStat(const std::string& filename) {
    // Implement class methods here
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    int n;
    file >> n;
    if (file.fail()) {
        throw std::runtime_error("Invalid format: cannot read N");
    }

    if (n < 0) {
        throw std::invalid_argument("N must be >= 0");
    }

    data_.reserve(n);
    for (int i = 0; i < n; ++i) {
        int val;
        if (!(file >> val)) {
            throw std::runtime_error("Invalid format: not enough integers or invalid data");
        }
        data_.push_back(val);
    }

    std::sort(data_.begin(), data_.end());
}

int ArrayStat::max() const {
    if (data_.empty()) {
        throw std::domain_error("max() called on empty array");
    }
    return data_.back();
}

int ArrayStat::min() const {
    if (data_.empty()) {
        throw std::domain_error("min() called on empty array");
    }
    return data_.front();
}

double ArrayStat::mean() const {
    if (data_.empty()) {
        throw std::domain_error("mean() called on empty array");
    }
    double sum = 0.0;
    for (int x : data_) {
        sum += x;
    }
    return sum / data_.size();
}

double ArrayStat::stdev() const {
    if (data_.empty()) {
        throw std::domain_error("stdev() called on empty array");
    }
    if (data_.size() == 1) {
        throw std::domain_error("stdev() requires at least 2 elements for unbiased estimator");
    }

    double m = mean();
    double sum_sq_diff = 0.0;
    for (int x : data_) {
        double diff = x - m;
        sum_sq_diff += diff * diff;
    }

    return std::sqrt(sum_sq_diff / (data_.size() - 1));
}

size_t ArrayStat::countLarger(int a) const {
    auto it = std::upper_bound(data_.begin(), data_.end(), a);
    return std::distance(it, data_.end());
}

void ArrayStat::print() const {
    for (size_t i = 0; i < data_.size(); ++i) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << data_[i];
    }
    std::cout << std::endl;
}