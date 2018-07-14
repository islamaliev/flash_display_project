#include "gmock/gmock.h"
#include "Color.h"

using namespace testing;

using Color = flash::core::Color;

class Color_Test : public Test {
public:
    Color_Test() {}

    void assertColor(unsigned char r, unsigned char g, unsigned char b) {
        ASSERT_TRUE(false);
        //ASSERT_THAT(color.r, Eq(r));
        //ASSERT_THAT(color.g, Eq(g));
        //ASSERT_THAT(color.b, Eq(b));
    }

    Color color;
};

class Color_ScalarTest : public Color_Test {};

TEST_F(Color_Test, DefaultConstructor) {
    assertColor(0, 0, 0);
}

TEST_F(Color_Test, ValuesConstructor) {
    color = Color(10, 100, 200);
    assertColor(10, 100, 200);
}

TEST_F(Color_Test, Plus) {
    color = Color(10, 100, 200) + Color(4, 50, 16);
    assertColor(14, 150, 216);
}

TEST_F(Color_Test, PlusAssign) {
    color = Color(10, 100, 200);
    color += Color(4, 50, 16);
    assertColor(14, 150, 216);
}

TEST_F(Color_Test, Minus) {
    color = Color(10, 100, 200) - Color(5, 30, 100);
    assertColor(5, 70, 100);
}

TEST_F(Color_Test, MinusAssign) {
    color = Color(10, 100, 200);
    color -= Color(5, 30, 100);
    assertColor(5, 70, 100);
}

TEST_F(Color_Test, Multiply) {
    color = Color(0, 30, 45) * Color(56, 5, 4);
    assertColor(0, 150, 180);
}

TEST_F(Color_Test, MultiplyAssign) {
    color = Color(0, 30, 45);
    color *= Color(56, 5, 4);
    assertColor(0, 150, 180);
}

TEST_F(Color_Test, Devide) {
    color = Color(20, 0, 240) / Color(2, 23, 4);
    assertColor(10, 0, 60);
}

TEST_F(Color_Test, DevideAssign) {
    color = Color(20, 0, 240);
    color /= Color(2, 23, 4);
    assertColor(10, 0, 60);
}

TEST_F(Color_ScalarTest, Plus) {
    color = Color(10, 100, 200) + 40;
    assertColor(50, 140, 240);
}

TEST_F(Color_ScalarTest, PlusAssign) {
    color = Color(10, 100, 200);
    color += 40;
    assertColor(50, 140, 240);
}

TEST_F(Color_ScalarTest, Minus) {
    color = Color(40, 100, 200) - 40;
    assertColor(0, 60, 160);
}

TEST_F(Color_ScalarTest, MinusAssign) {
    color = Color(40, 100, 200);
    color -= 40;
    assertColor(0, 60, 160);
}

/*TEST_F(Color_ScalarTest, Multiply) {
    color = Color(0, 50, 100) * 0.6f;
    assertColor(0, 30, 60);
}

TEST_F(Color_ScalarTest, MultiplyAssign) {
    color = Color(0, 50, 100);
    color *= 0.6;
    assertColor(0, 30, 60);
}

TEST_F(Color_ScalarTest, Devide) {
    color = Color(0, 10, 20) / 0.1;
    assertColor(0, 100, 200);
}

TEST_F(Color_ScalarTest, DevideAssign) {
    color = Color(0, 10, 20);
    color /= 0.1;
    assertColor(0, 100, 200);
}*/

TEST_F(Color_Test, ConversationToUint) {
    unsigned r = Color(0xFF, 0, 0).uint();
    unsigned g = Color(0, 0xFF, 0).uint();
    unsigned b = Color(0, 0, 0xFF).uint();
    unsigned mix = Color(196, 64, 128).uint();
    ASSERT_THAT(r, Eq(16711680));
    ASSERT_THAT(g, Eq(65280));
    ASSERT_THAT(b, Eq(255));
    ASSERT_THAT(mix, Eq((196 << 16) | (64 << 8) | 128));
}

TEST_F(Color_Test, IntegerConstructor) {
    color = Color(0xFF << 16);
    assertColor(0xFF, 0, 0);
    color = Color(0xFF << 8);
    assertColor(0, 0xFF, 0);
    color = Color(0xFF);
    assertColor(0, 0, 0xFF);
}

TEST_F(Color_Test, SetBytes) {
    float R = 0.1;
    float G = 0.5;
    float B = 0.9;
    color.setR(R);
    color.setG(G);
    color.setB(B);
    unsigned converter = 0xFF;
    assertColor(R * converter, G * converter, B * converter);
}

TEST_F(Color_Test, GetBytes) {
    float R = 0.1;
    float G = 0.5;
    float B = 0.9;
    color.setR(R);
    color.setG(G);
    color.setB(B);
    ASSERT_THAT(color.R(), FloatNear(R, 0.02));
    ASSERT_THAT(color.G(), FloatNear(G, 0.02));
    ASSERT_THAT(color.B(), FloatNear(B, 0.02));
}