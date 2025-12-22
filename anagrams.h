#pragma once
#include <map>
#include <string>
#include <cctype>

bool AreAnagrams(std::string a, std::string b) {
    // TODO: implement me
    if (a.size() != b.size()) return false;
    std::map<char, int> cnt;
    for (char& c : a) {
        if (std::isalpha(c)) cnt[std::tolower(c)]++;
    }
    for (char& c : b) {
        if (std::isalpha(c)) {
            char k = std::tolower(c);
            if (--cnt[k] < 0) return false;
        }
    }
    for (auto& p : cnt) {
        if (p.second != 0) return false;
    }
    return true;
}