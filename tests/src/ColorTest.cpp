#include "gmock/gmock.h"
#include "Color.h"

using namespace testing;

using Color = flash::core::Color;

class ColorTest : public Test {
public:
    ColorTest() {}

    void assertColor(float r, float g, float b) {
        ASSERT_THAT(color.r, FloatEq(r));
        ASSERT_THAT(color.g, FloatEq(g));
        ASSERT_THAT(color.b, FloatEq(b));
    }

    Color color;
};

class ColorScalarTest : public ColorTest {};

TEST_F(ColorTest, DefaultConstructor) {
    assertColor(0, 0, 0);
}

TEST_F(ColorTest, ValuesConstructor) {
    color = Color(0.1, 0.5, 0.9);
    assertColor(0.1, 0.5, 0.9);
}

TEST_F(ColorTest, Plus) {
    color = Color(0.1, 0.2, 0.3) + Color(0.4, 0.5, 0.6);
    assertColor(0.5, 0.7, 0.9);
}

TEST_F(ColorTest, PlusAssign) {
    color = Color(0.1, 0.2, 0.3);
    color += Color(0.4, 0.5, 0.6);
    assertColor(0.5, 0.7, 0.9);
}

TEST_F(ColorTest, Minus) {
    color = Color(0.4, 0.7, 1) - Color(0.1, 0.2, 0.3);
    assertColor(0.3, 0.5, 0.7);
}

TEST_F(ColorTest, MinusAssign) {
    color = Color(0.4, 0.7, 1);
    color -= Color(0.1, 0.2, 0.3);
    assertColor(0.3, 0.5, 0.7);
}

TEST_F(ColorTest, Multiply) {
    color = Color(0, 0.5, 1) * Color(0.6, 0.6, 0.6);
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorTest, MultiplyAssign) {
    color = Color(0, 0.5, 1);
    color *= Color(0.6, 0.6, 0.6);
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorTest, Devide) {
    color = Color(0, 0.1, 0.6) / Color(0.6, 0.1, 1);
    assertColor(0, 1, 0.6);
}

TEST_F(ColorTest, DevideAssign) {
    color = Color(0, 0.1, 0.6);
    color /= Color(0.6, 0.1, 1);
    assertColor(0, 1, 0.6);
}

TEST_F(ColorScalarTest, Plus) {
    color = Color(0.1, 0.2, 0.3) + 0.4;
    assertColor(0.5, 0.6, 0.7);
}

TEST_F(ColorScalarTest, PlusAssign) {
    color = Color(0.1, 0.2, 0.3);
    color += 0.4;
    assertColor(0.5, 0.6, 0.7);
}

TEST_F(ColorScalarTest, Minus) {
    color = Color(0.4, 0.7, 1) - 0.4;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, MinusAssign) {
    color = Color(0.4, 0.7, 1);
    color -= 0.4;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, Multiply) {
    color = Color(0, 0.5, 1) * 0.6;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, MultiplyAssign) {
    color = Color(0, 0.5, 1);
    color *= 0.6;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, Devide) {
    color = Color(0, 0.1, 0.05) / 0.1;
    assertColor(0, 1, 0.5);
}

TEST_F(ColorScalarTest, DevideAssign) {
    color = Color(0, 0.1, 0.05);
    color /= 0.1;
    assertColor(0, 1, 0.5);
}

TEST_F(ColorTest, ConversationToUint) {
    unsigned r = Color(1, 0, 0).uint();
    unsigned g = Color(0, 1, 0).uint();
    unsigned b = Color(0, 0, 1).uint();
    unsigned mix = Color(0.8, 0.2, 0.4).uint();
    ASSERT_THAT(r, Eq(16711680));
    ASSERT_THAT(g, Eq(65280));
    ASSERT_THAT(b, Eq(255));
    ASSERT_THAT(mix, Eq(13382502));
}

TEST_F(ColorTest, IntegerConstructor) {
    color = Color(16711680);
    assertColor(1, 0, 0);
    color = Color(65280);
    assertColor(0, 1, 0);
    color = Color(255);
    assertColor(0, 0, 1);
}

TEST_F(ColorTest, Clamp) {
    color = Color(0.3, 1.6, 3);
    color.clamp();
    assertColor(0.3, 1, 1);
}

TEST_F(ColorTest, SetBytes) {
    unsigned char R = 10;
    unsigned char G = 55;
    unsigned char B = 200;
    color.setR(R);
    color.setG(G);
    color.setB(B);
    float converter = 1.f / 0xFF;
    assertColor(R * converter, G * converter, B * converter);
}

TEST_F(ColorTest, GetBytes) {
    unsigned char R = 10;
    unsigned char G = 55;
    unsigned char B = 200;
    color.setR(R);
    color.setG(G);
    color.setB(B);
    float converter = 1.f / 0xFF;
    ASSERT_THAT(color.R(), Eq(R));
    ASSERT_THAT(color.G(), Eq(G));
    ASSERT_THAT(color.B(), Eq(B));
}