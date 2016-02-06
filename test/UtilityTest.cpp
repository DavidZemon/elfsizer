/**
 * @file    UtilityTest.cpp
 *
 * @author  David Zemon
 */

#include <gtest/gtest.h>
#include <Utility.h>

TEST(UtilityTest, WhitespaceSplit_EmptyVectorForEmptyString) {
    std::vector<std::string> *actual = Utility::whitespace_split("");
    ASSERT_EQ(0, actual->size());
}

TEST(UtilityTest, WhitespaceSplit_EmptyVectorForOnlyWhitespace) {
    std::vector<std::string> *actual = Utility::whitespace_split("    \t   \t");
    ASSERT_EQ(0, actual->size());
}

TEST(UtilityTest, WhitespaceSplit_OneNonEmptyElementAtStart) {
    std::vector<std::string> *actual = Utility::whitespace_split("asdf    \t   \t");
    ASSERT_EQ(1, actual->size());
    ASSERT_EQ("asdf", (*actual)[0]);
}

TEST(UtilityTest, WhitespaceSplit_OneNonEmptyElementAtEnd) {
    std::vector<std::string> *actual = Utility::whitespace_split("    \t   \t  asdf");
    ASSERT_EQ(1, actual->size());
    ASSERT_EQ("asdf", (*actual)[0]);
}

TEST(UtilityTest, WhitespaceSplit_OneNonEmptyElementInMiddle) {
    std::vector<std::string> *actual = Utility::whitespace_split("    \t  asdf \t  ");
    ASSERT_EQ(1, actual->size());
    ASSERT_EQ("asdf", (*actual)[0]);
}

TEST(UtilityTest, WhitespaceSplit_TwoElements) {
    std::vector<std::string> *actual = Utility::whitespace_split(";lj    \t  asdf \t  ");
    ASSERT_EQ(2, actual->size());
    ASSERT_EQ(";lj", (*actual)[0]);
    ASSERT_EQ("asdf", (*actual)[1]);
}

TEST(UtilityTest, WhitespaceSplit_ManyElements) {
    std::vector<std::string> *actual = Utility::whitespace_split("This is\ta test.    ");
    ASSERT_EQ(4, actual->size());
    ASSERT_EQ("This", (*actual)[0]);
    ASSERT_EQ("is", (*actual)[1]);
    ASSERT_EQ("a", (*actual)[2]);
    ASSERT_EQ("test.", (*actual)[3]);
}

TEST(UtilityTest, Find_CaseSensitive_NotFound) {
    ASSERT_FALSE(Utility::contains("This is a test", "TEST"));
}

TEST(UtilityTest, Find_CaseInsensitive_NotFound) {
    ASSERT_FALSE(Utility::contains("This is a test", "TEST.", false));
}

TEST(UtilityTest, Find_CaseSensitive_Found) {
    ASSERT_TRUE(Utility::contains("This is a test", "test"));
}

TEST(UtilityTest, Find_CaseInsensitive_Found) {
    ASSERT_TRUE(Utility::contains("This is a test", "TEST", false));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
