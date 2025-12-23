#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <array>
#include <iostream>

#include "table.h"

bool check_table_size(const std::pair<size_t, size_t>& sizes, int n_rows, int n_cols){
    return (sizes == std::pair<size_t, size_t>{n_rows, n_cols});
}

template <typename T>
bool simple_test_one_table(const T& value, size_t rows, size_t cols) {
    Table<T> t(rows, cols);
    EXPECT_TRUE(check_table_size(t.Size(), rows, cols));
    for(size_t i = 0; i < rows; i++)
        for(size_t j = 0; j < cols; j++){
            t[i][j] = value;
            EXPECT_TRUE(t[i][j]==value);
        }
    t.Resize(cols, rows);
    EXPECT_TRUE(check_table_size(t.Size(), cols, rows));
    for(size_t i = 0; i < std::min(rows, cols); i++){
        for(size_t j = 0; j < std::min(cols, rows); j++){
            EXPECT_TRUE(t[i][j]==value);
        }
    }
    return true;
}

TEST(TABLE, Empty) {
    std::cout << "Test Empty table" << std::endl;
    simple_test_one_table((int)1, 0, 0);
}

TEST(TABLE, Init) {
    std::random_device rd;
    std::uniform_int_distribution<size_t> dist(1, 100);
    for(int i=0; i<20; i++){
        size_t rows = dist(rd);
        size_t cols = dist(rd);
        simple_test_one_table(32, rows, cols);
        simple_test_one_table(false, rows, cols);
        simple_test_one_table(std::string{"str"}, rows, cols);
        simple_test_one_table(std::vector<std::string>{"one", "two", "three"}, rows, cols);
        simple_test_one_table(std::pair<std::array<int, 3>, int>{{1, 2, 5}, 88}, rows, cols);
    }
}

TEST(TABLE, Int) {
    std::cout << "Complex test of Table<int>" << std::endl;
    Table<int> t(1, 1);
    EXPECT_TRUE(check_table_size(t.Size(), 1, 1));
    t[0][0] = 42;
    ASSERT_EQ(t[0][0], 42);

    t.Resize(3, 4);
    EXPECT_TRUE(check_table_size(t.Size(), 3, 4));
    ASSERT_EQ(t[0][0], 42);
}

TEST(TABLE, String) {
    std::cout << "Complex test of Table<std::string>" << std::endl;
    size_t rows = 5, cols = 7;
    Table<std::string> t(rows, cols);
    EXPECT_TRUE(check_table_size(t.Size(), rows, cols));
    for(size_t i = 0; i < rows; i++)
        for(size_t j = 0; j < cols; j++){
            std::string input_str = std::to_string(i) + std::to_string(j);
            t[i][j] = input_str;
            ASSERT_EQ(t[i][j], input_str);
        }

    t.Resize(13, 10);
    EXPECT_TRUE(check_table_size(t.Size(), 13, 10));
    for(size_t i = 0; i < rows; i++)
        for(size_t j = 0; j < cols; j++){
            std::string input_str = std::to_string(i) + std::to_string(j);
            ASSERT_EQ(t[i][j], input_str);
        }

    rows = 4; 
    cols = 3;
    t.Resize(rows, cols);
    EXPECT_TRUE(check_table_size(t.Size(), rows, cols));
    for(size_t i = 0; i < rows; i++)
        for(size_t j = 0; j < cols; j++){
            std::string input_str = std::to_string(i) + std::to_string(j);
            ASSERT_EQ(t[i][j], input_str);
        }
}

TEST(TABLE, ConstTable) {
    std::cout << "Complex test of const Table<int>" << std::endl;
    Table<int> t(1, 1);
    t[0][0] = 15;
    const Table<int> t_const(std::move(t));
    EXPECT_TRUE(check_table_size(t_const.Size(), 1, 1)); 
    ASSERT_EQ(t_const[0][0], 15);
}

int main(int arc, char **argv) {
    ::testing::InitGoogleTest(&arc, argv);
    return RUN_ALL_TESTS();
}
