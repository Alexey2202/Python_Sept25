#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>
#include <random>

#include <cmath>

#include "utils.h"
#include "parse.h"

#include "ArrayStat.h"

constexpr double DEFAULT_EPS = 1e-8;

std::vector<int> make_array(size_t size, int begin, int end) {
    static std::minstd_rand rng(0xDEADBEEF);
    std::uniform_int_distribution<> rand_int(begin, end - 1);
    std::vector<int> v(size);
    std::generate(v.begin(), v.end(), [&rand_int](){return rand_int(rng);});
    return v;
}

using TestFcn = std::function<void(const std::vector<int>&, const std::string&)>;

void run_files_test(TestFcn test_func) {
    {
        std::vector<int> data;
        TempFile tfile(data);
        test_func(data, tfile.name());
    }

    {
        std::vector<int> data = make_array(1, -5, 10);
        TempFile tfile(data);
        test_func(data, tfile.name());
    }

    {
        std::vector<int> data = make_array(100, -500, 1000);
        TempFile tfile(data);
        test_func(data, tfile.name());
    }

    {
        std::vector<int> data = make_array(1000000, -50000000, 100000000);
        TempFile tfile(data);
        test_func(data, tfile.name());
    }
}

TEST(TestStatArray, NotExists) {
    try {
        ArrayStat stat("out/nonexistent.txt");
    } catch (...) {
        return;
    }
    ASSERT_TRUE(false);
}

TEST(TestStatArray, Ctor) {
    run_files_test([](const std::vector<int>&, const std::string& fname) {
        try {
            ArrayStat stat(fname);
        } catch (...) {
            ASSERT_TRUE(false);
        }
    });
}

TEST(TestStatArray, MinMax) {
    run_files_test([](const std::vector<int>& data, const std::string& fname) {
        ArrayStat stat(fname);

        if (data.size() == 0) {
            try {
                stat.min();
            } catch (...) {
                try {
                    stat.max();
                } catch (...) {
                    return;
                }
            }
            ASSERT_TRUE(false);
        }

        const int min = *std::min_element(data.begin(), data.end());
        const int max = *std::max_element(data.begin(), data.end());

        ASSERT_NEAR(stat.min(), min, DEFAULT_EPS);
        ASSERT_NEAR(stat.max(), max, DEFAULT_EPS);
    });
}

TEST(TestStatArray, Mean) {
    run_files_test([](const std::vector<int>& data, const std::string& fname) {
        ArrayStat stat(fname);

        if (data.empty()) {
            try {
                stat.mean();
            } catch (...) {
                return;
            }
            ASSERT_TRUE(false);
        }

        double mean = 0.;
        for (auto& item : data) mean += item;
        mean /= data.size();

        ASSERT_NEAR(stat.mean(), mean, DEFAULT_EPS);
    });
}

TEST(TestStatArray, StdDev) {
    run_files_test([](const std::vector<int>& data, const std::string& fname) {
        ArrayStat stat(fname);

        if (data.size() <= 1) {
            try {
                stat.stddev();
            } catch (...) {
                return;
            }
            ASSERT_TRUE(false);
        }

        double mean = 0.;
        for (int x : data) mean += x;
        mean /= data.size();

        ASSERT_NEAR(stat.mean(), mean, DEFAULT_EPS);

        double stddev = 0.;
        for (int x : data) stddev += (x - mean) * (x - mean);
        stddev = std::sqrt(stddev / (data.size() - 1));

        ASSERT_NEAR(stat.stddev(), stddev, 100 * DEFAULT_EPS);
    });
}


TEST(TestStatArray, CountLarger) {
    run_files_test([](const std::vector<int>& data, const std::string& fname) {
        ArrayStat stat(fname);

        std::vector<int> sorted_data(data);
        std::sort(sorted_data.begin(), sorted_data.end());

        int lval = 0;
        size_t lcnt = 0;
        for (size_t j = 0; j < data.size(); ++j) {
            size_t i = data.size() - j - 1;
            int val = sorted_data[i];
            if (j == 0 || lval != val) {
                lval = val;
                lcnt = j;
            }
            ASSERT_EQ(stat.countLarger(val), lcnt);

            if (j != 0) {
                int diff = sorted_data[i + 1] - val;
                if (diff >= 2) {
                    ASSERT_EQ(stat.countLarger(val + diff / 2), lcnt);
                }
            }
        }
    });
}

TEST(TestStatArray, Print) {
    run_files_test([](const std::vector<int>& data, const std::string& fname) {
        std::string output;

        {
            Redir redir;
            ArrayStat stat(fname);
            stat.print();
            output = redir.content();
        }

        std::vector<int> sorted_data(data);
        std::sort(sorted_data.begin(), sorted_data.end());
        std::vector<int> parsed = parse_int(output);

        ASSERT_EQ(data.size(), parsed.size());
        for (size_t i = 0; i < data.size(); ++i) {
            ASSERT_EQ(sorted_data[i], parsed[i]);
        }
    });
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
