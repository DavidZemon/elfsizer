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

TEST_F(ElfSizerBuilderTest, HandlesNoInputFile) {
    const int argc = 1;
    const char *argv[argc] = {
        "foobar"
    };

    EXPECT_THROW(this->testable = ElfSizerBuilder::build(argc, argv), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
