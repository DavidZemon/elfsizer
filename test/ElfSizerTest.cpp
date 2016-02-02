/**
 * @file    ElfSizerTest.cpp
 *
 * @author  David Zemon
 */

#include <gtest/gtest.h>
#include <ElfSizer.h>

TEST(ElfSizerTest, HandlesBadInputFile) {
    ElfSizer elfSizer("/bogus/file");

    ASSERT_EQ(ElfSizer::ErrorCode::BAD_INPUT_FILE, elfSizer.run());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
