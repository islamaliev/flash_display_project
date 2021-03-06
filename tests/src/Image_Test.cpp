#include "gmock/gmock-matchers.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Image.h"
#include "Texture.h"

using namespace testing;
using namespace flash::display;

class Image_Test : public testing::Test {
public:
    static constexpr unsigned W = 60;
    static constexpr unsigned H = 40;

protected:
    void SetUp() override {
        image.setTexture(&texture);
    }

    Image image;
    Texture texture{W, H};
};

TEST_F(Image_Test, ImageHasSizeOfTexture) {
    ASSERT_THAT(image.width(), Eq(W));
    ASSERT_THAT(image.height(), Eq(H));
}

TEST_F(Image_Test, ifWidthIsSet_scaleXIsAltered) {
    image.setWidth(image.width() * 2);
    ASSERT_THAT(image.scaleX(), Eq(2));
}

TEST_F(Image_Test, ifHeightIsSet_scaleYIsAltered) {
    image.setHeight(image.height() * 2);
    ASSERT_THAT(image.scaleY(), Eq(2));
}

TEST_F(Image_Test, ifScaleXIsSet_widthIsAltered) {
    image.setScaleX(2);
    ASSERT_THAT(image.width(), Eq(W * 2));
}

TEST_F(Image_Test, ifScaleYIsSet_heightIsAltered) {
    image.setScaleY(2);
    ASSERT_THAT(image.height(), Eq(H * 2));
}