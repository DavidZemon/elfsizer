/**
 * @file    ElfSizerTest.cpp
 *
 * @author  David Zemon
 */

#include <gtest/gtest.h>
#include <ElfSizer.h>
#include <Utility.h>

const std::string TEST_FILE = "Welcome.elf";

class ElfSizerTest: public ::testing::Test {
    protected:
        virtual void SetUp() {
            this->testable = new ElfSizer(TEST_FILE);
        }

        virtual void TearDown() {
            if (nullptr != this->testable)
                delete this->testable;
        }

    protected:
        ElfSizer *testable;
};

TEST_F(ElfSizerTest, HandlesBadInputFile) {
    ElfSizer elfSizer("/bogus/file");

    EXPECT_THROW(elfSizer.run(), std::ios_base::failure);
}

TEST_F(ElfSizerTest, InputFile_UserExpanded) {
    ElfSizer elfSizer("~/file");

    std::string expectedPath = std::getenv("HOME");
    expectedPath += "/file";
    ASSERT_EQ(expectedPath, elfSizer.get_input());
}

TEST_F(ElfSizerTest, ReadsMap) {
    ASSERT_TRUE(Utility::exists(TEST_FILE));

    const ElfSizer::Map actualMap = this->testable->run();

    ASSERT_EQ(8132, actualMap.codeSize);
    ASSERT_EQ(8336, actualMap.totalSize);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
