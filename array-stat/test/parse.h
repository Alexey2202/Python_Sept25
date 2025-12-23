#pragma once

#include <string>
#include <vector>
#include <utility>


void replace_other(std::string *str, const char *srcs, char dst) {
    for (int i = 0; i < int(str->size()); ++i) {
        bool found = false;
        for (int j = 0; srcs[j] != '\0'; ++j) {
            if ((*str)[i] == srcs[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            (*str)[i] = dst;
        }
    }
}

std::vector<int> parse_int(std::string str) {
    std::vector<int> nums;

    replace_other(&str, "0123456789+-", ' ');

    int b = -1;
    for (int i = 0; i < int(str.size()); ++i) {
        if (str[i] != ' ') {
            if (b < 0) {
                b = i;
            }
        } else {
            if (b >= 0) {
                nums.push_back(atoi(str.substr(b, i - b).c_str()));
                b = -1;
            }
        }
    }
    if (b >= 0) {
        nums.push_back(atoi(str.substr(b, str.size() - b).c_str()));
    }
    
    return nums;
}
