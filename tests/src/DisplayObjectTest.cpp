#include <gmock/gmock-matchers.h>
#include <DisplayObject.h>

using namespace testing;
using namespace flash::display;

class DisplayObjectTest : public testing::Test {
public:
    void SetUp() override {
    }

    DisplayObject displayObject;
};

TEST_F(DisplayObjectTest, SetWidth) {
    displayObject.setWidth(100);
    ASSERT_EQ(displayObject.width(), 100);
    displayObject.setWidth(200);
    ASSERT_EQ(displayObject.width(), 200);
}

TEST_F(DisplayObjectTest, SetHeight) {
    displayObject.setHeight(100);
    ASSERT_EQ(displayObject.height(), 100);
    displayObject.setHeight(200);
    ASSERT_EQ(displayObject.height(), 200);
}

TEST_F(DisplayObjectTest, setVisible) {
    displayObject.setVisible(false);
    ASSERT_EQ(displayObject.visible(), false);
    displayObject.setVisible(true);
    ASSERT_EQ(displayObject.visible(), true);
}