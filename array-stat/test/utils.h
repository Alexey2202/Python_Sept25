#pragma once

#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
// #include <filesystem>
#include <cstdio>

template<typename T>
testing::AssertionResult ASSERT_NEAR_REL(
        const T& a, const T& b, double eps=1.e-8, double eps_rel=1.e-8) {
    const T abs_a = std::abs(a);
    const T abs_b = std::abs(b);
    const T abs_delta = std::abs(a - b);
    if (abs_a < eps && abs_b < eps || 2. * abs_delta / (abs_a + abs_b) < eps_rel)
        return testing::AssertionSuccess();
    return testing::AssertionFailure() << a << " != " << b;
} 


class TempFile {
    const std::string m_path;

 public:
    template <typename T>
    TempFile(const std::vector<T> &data, std::string path="test_data.txt")
            : m_path(std::move(path)) {
        std::ofstream file(m_path, std::ios::out | std::ios::trunc);
        // ASSERT_TRUE(file.good());

        file << data.size() << '\n';
        for (auto v : data) file << v << ' ';
        file << std::endl;
    }
    ~TempFile() {
        // std::filesystem::path path(m_path);
        // std::filesystem::remove(path);
        std::remove(m_path.c_str());
    }

    TempFile(const TempFile &) = delete;
    TempFile &operator=(const TempFile &) = delete;

    const std::string& name() const {
        return m_path;
    }
};

class Redir {
    std::ostringstream stream;
    std::streambuf *stdoutbuf;

 public:
    Redir() {
        stdoutbuf = std::cout.rdbuf(stream.rdbuf());
    }
    ~Redir() {
        std::cout.rdbuf(stdoutbuf);
    }
    std::string content() const {
        return stream.str();
    }
};
