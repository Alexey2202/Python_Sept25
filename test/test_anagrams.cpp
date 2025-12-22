#include "gtest/gtest.h"

#include <string>
#include <algorithm>

#include "anagrams.h"

TEST(Anagrams, TestSameString)
{
    EXPECT_TRUE(AreAnagrams("eat", "eat"));
}

TEST(Anagrams, TestBasic)
{
    EXPECT_TRUE(AreAnagrams("eat", "tea"));
    EXPECT_FALSE(AreAnagrams("find", "search"));
    EXPECT_TRUE(AreAnagrams("master", "stream"));
}

TEST(Anagrams, TestMixedCase)
{
    EXPECT_TRUE(AreAnagrams("eat", "TEA"));
    EXPECT_FALSE(AreAnagrams("find", "SEARCH"));
    EXPECT_TRUE(AreAnagrams("mAsTeR", "stream"));
}

TEST(Anagrams, TestEmptyString)
{
    EXPECT_TRUE(AreAnagrams("", ""));
    EXPECT_FALSE(AreAnagrams("", "a"));
    EXPECT_FALSE(AreAnagrams("b", ""));
}

TEST(Anagrams, TestRepeatingChars)
{
    EXPECT_FALSE(AreAnagrams("Stressed", "Dessert"));
    EXPECT_TRUE(AreAnagrams("Stressed", "Desserts"));
    EXPECT_FALSE(AreAnagrams("aas", "ssa"));
}

TEST(Anagrams, TestSingleChar)
{
    EXPECT_FALSE(AreAnagrams("sss", "s"));
}

TEST(Anagrams, TestRandom)
{
    std::string str = "abcdef";
    std::string str_copy = "abcdef";
    std::random_shuffle(str.begin(), str.end());
    EXPECT_TRUE(AreAnagrams(str, str_copy));
}

int main(int arc, char **argv) 
{
    ::testing::InitGoogleTest(&arc, argv);
    return RUN_ALL_TESTS();
}
