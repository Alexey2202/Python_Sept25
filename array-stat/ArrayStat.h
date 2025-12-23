#ifndef ARRAYSTAT_H
#define ARRAYSTAT_H

#include <string>
#include <vector>
#include <stdexcept>

class ArrayStat {
public:
    explicit ArrayStat(const std::string& filename);

    int max() const;

    int min() const;

    double mean() const;

    double stdev() const;

    size_t countLarger(int a) const;

    void print() const;

private:
    std::vector<int> data_;
};

#endif