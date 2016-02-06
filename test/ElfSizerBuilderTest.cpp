/**
 * @file    ElfSizerBuilderTest
 *
 * @author  David Zemon
 */

#include <gtest/gtest.h>
#include <ElfSizerBuilder.h>

class ElfSizerBuilderTest: public ::testing::Test {
    protected:
        virtual void TearDown() {
            if (nullptr == this->testable) {
                delete this->testable;
                this->testable = nullptr;
            }
        }

    protected:
        ElfSizer *testable;
};

TEST_F(ElfSizerBuilderTest, HandlesNoArgs) {
    const int  argc        = 1;
    const char *argv[argc] = {
        "foobar"
    };

    EXPECT_THROW(ElfSizerBuilder::build(argc, argv), std::invalid_argument);
}

TEST_F(ElfSizerBuilderTest, HandlesNoInputFile) {
    const int  argc        = 2;
    const char *argv[argc] = {
        "foobar",
        "-ofile2"
    };

    EXPECT_THROW(ElfSizerBuilder::build(argc, argv), std::invalid_argument);
}

TEST_F(ElfSizerBuilderTest, HandlesNoObjdump) {
    const int  argc        = 2;
    const char *argv[argc] = {
        "foobar",
        "-ifile"
    };

    EXPECT_THROW(ElfSizerBuilder::build(argc, argv), std::invalid_argument);
}

TEST_F(ElfSizerBuilderTest, NoError_ShortArgs_NoSpace) {
    const int  argc        = 3;
    const char *argv[argc] = {
        "foobar",
        "-ifile",
        "-ofile2"
    };

    this->testable = ElfSizerBuilder::build(argc, argv);
    ASSERT_EQ("file", this->testable->get_input());
    ASSERT_EQ("file2", this->testable->get_objdump());
}

TEST_F(ElfSizerBuilderTest, NoError_ShortArg_WithSpace) {
    const int  argc        = 5;
    const char *argv[argc] = {
        "foobar",
        "-i",
        "file",
        "-o",
        "file2"
    };

    this->testable = ElfSizerBuilder::build(argc, argv);
    ASSERT_EQ("file", this->testable->get_input());
    ASSERT_EQ("file2", this->testable->get_objdump());
}

TEST_F(ElfSizerBuilderTest, NoError_LongArg_WithSpace) {
    const int  argc        = 5;
    const char *argv[argc] = {
        "foobar",
        "--input",
        "file",
        "--objdump",
        "file2"
    };

    this->testable = ElfSizerBuilder::build(argc, argv);
    ASSERT_EQ("file", this->testable->get_input());
    ASSERT_EQ("file2", this->testable->get_objdump());
}

TEST_F(ElfSizerBuilderTest, NoError_LongArg_WithEquals) {
    const int  argc        = 3;
    const char *argv[argc] = {
        "foobar",
        "--input=file",
        "--objdump=file2"
    };

    this->testable = ElfSizerBuilder::build(argc, argv);
    ASSERT_EQ("file", this->testable->get_input());
    ASSERT_EQ("file2", this->testable->get_objdump());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
