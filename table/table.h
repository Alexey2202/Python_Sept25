#pragma once
#include <vector>
#include <utility>

template<typename T>
class Table {
    // TODO: impolement me
    std::vector<std::vector<T>> data;
    size_t rows, cols;

public:
    Table(size_t r = 0, size_t c = 0) : rows(r), cols(c) {
        data.resize(rows);
        for(auto& row : data) row.resize(cols);
    }

    std::pair<size_t, size_t> Size() const { return {rows, cols}; }

    void Resize(size_t new_rows, size_t new_cols) {
        data.resize(new_rows);
        for(auto& row : data) row.resize(new_cols);
        rows = new_rows; cols = new_cols;
    }

    std::vector<T>& operator[](size_t i) { return data[i]; }
    const std::vector<T>& operator[](size_t i) const { return data[i]; }
};