/**
 * @file    ElfSizerTest.cpp
 *
 * @author  David Zemon
 */

#include <gtest/gtest.h>
#include <ElfSizer.h>

class ElfSizerTest: public ::testing::Test {

};

TEST_F(ElfSizerTest, HandlesBadInputFile) {
    ElfSizer elfSizer("/bogus/file");

    ASSERT_EQ(ElfSizer::ErrorCode::BAD_INPUT_FILE, elfSizer.run());
}

TEST_F(ElfSizerTest, InputFile_UserExpanded) {
    ElfSizer elfSizer("~/file");

    std::string expectedPath = std::getenv("HOME");
    expectedPath += "/file";
    ASSERT_EQ(expectedPath, elfSizer.get_input());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
