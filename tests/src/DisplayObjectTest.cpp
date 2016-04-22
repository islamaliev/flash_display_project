#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"

using namespace testing;

class DisplayObjectTest : public testing::Test {
public:
    void SetUp() override {
    }
};

TEST_F(DisplayObjectTest, Bla) {
    ASSERT_EQ(0, 0);
}
