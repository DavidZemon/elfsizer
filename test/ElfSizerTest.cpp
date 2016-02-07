/**
 * @file    ElfSizerTest.cpp
 *
 * @author  David Zemon
 */

#include <gtest/gtest.h>
#include <ElfSizer.h>
#include <Utility.h>
#include <teamcity_messages.h>
#include <teamcity_gtest.h>

const std::string TEST_FILE = "Welcome.elf";
std::string       OBJDUMP_PATH;

class ElfSizerTest: public ::testing::Test {
    protected:
        virtual void SetUp() {
            this->testable = new ElfSizer(TEST_FILE, OBJDUMP_PATH);
        }

        virtual void TearDown() {
            if (nullptr != this->testable)
                delete this->testable;
        }

    protected:
        ElfSizer *testable;
};

TEST_F(ElfSizerTest, HandlesBadInputFile) {
    ElfSizer elfSizer("/bogus/file", OBJDUMP_PATH);

    EXPECT_THROW(elfSizer.run(), std::ios_base::failure);
}

TEST_F(ElfSizerTest, InputFile_UserExpanded) {
    ElfSizer elfSizer("~/file", OBJDUMP_PATH);

    std::string expectedPath = std::getenv("HOME");
    expectedPath += "/file";
    ASSERT_EQ(expectedPath, elfSizer.get_input());
}

TEST_F(ElfSizerTest, HandlesBadObjdump) {
    ElfSizer elfSizer(TEST_FILE, "/bogus/file");

    EXPECT_THROW(elfSizer.run(), std::ios_base::failure);
}

TEST_F(ElfSizerTest, Objdump_UserExpanded) {
    ElfSizer elfSizer(TEST_FILE, "~/file");

    std::string expectedPath = std::getenv("HOME");
    expectedPath += "/file";
    ASSERT_EQ(expectedPath, elfSizer.get_objdump());
}

TEST_F(ElfSizerTest, ReadsMap) {
    const ElfSizer::Map actualMap = this->testable->run();

    ASSERT_EQ(8132, actualMap.codeSize);
    ASSERT_EQ(8336, actualMap.totalSize);
}

int main(int argc, char **argv) {
    assert(2 <= argc);
    assert(strlen(argv[1]));
    OBJDUMP_PATH = argv[1];
    assert(Utility::exists(OBJDUMP_PATH));
    assert(Utility::exists(TEST_FILE));

    testing::InitGoogleTest(&argc, argv);
    if (jetbrains::teamcity::underTeamcity()) {
        ::testing::TestEventListeners &listeners = ::testing::UnitTest::GetInstance()->listeners();
        listeners.Append(new jetbrains::teamcity::TeamcityGoogleTestEventListener());
    }
    return RUN_ALL_TESTS();
}
