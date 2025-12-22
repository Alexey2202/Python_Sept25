#include "gtest/gtest.h"
#include "modular-sorting.h"

#include <vector>
#include <fstream>

std::vector<int> get_data(const std::string fname) {
    std::ifstream ifile("../../test/data/" + fname, std::ios::in);
    if (!ifile.good()) {
        std::cerr << "Can't read " << fname << std::endl;
        return {};
    }
    std::vector<int> array;
    int numb;
    while (ifile >> numb) array.push_back(numb);
    return array;
}

void check_modular_sorted(const std::vector<int>& vec) {
    if (vec.size() < 2) return;
    auto it = vec.begin();
    auto jt = std::next(it);
    while (jt != vec.end())
        ASSERT_LE(std::abs(*it++), std::abs(*jt++));
}

void run_test(const std::string& label) {
    auto idata = get_data(label + ".in");
    ModularSort(idata);
    check_modular_sorted(idata);
}

TEST(ModSort, SimpleTest1) {
    std::vector<int> input{-3, -18, 0, 9, 2, 4, -1};
    ModularSort(input);
    check_modular_sorted(input);
}

TEST(ModSort, SimpleTest2) {
    std::vector<int> input{3, -3, 0, -1, 1, 4, -4};
    ModularSort(input);
    check_modular_sorted(input);
}

TEST(ModSort, RandomLong) {
    run_test("long");
}

int main(int arc, char **argv) {
    ::testing::InitGoogleTest(&arc, argv);
    return RUN_ALL_TESTS();
}
