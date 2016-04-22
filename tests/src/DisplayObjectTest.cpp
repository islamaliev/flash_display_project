#include <gmock/gmock-matchers.h>
#include <DisplayObject.h>
#include "gtest/gtest.h"

using namespace testing;

class DisplayObjectTest : public testing::Test {
public:
    void SetUp() override {
    }

    DisplayObject displayObject;
};

TEST_F(DisplayObjectTest, SetWidth) {
    displayObject.setWidth(100);
    ASSERT_EQ(displayObject.width(), 100);
}

TEST_F(DisplayObjectTest, SetHeight) {
    displayObject.setHeight(100);
    ASSERT_EQ(displayObject.height(), 100);
}