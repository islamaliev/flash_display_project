#include "gmock/gmock-matchers.h"
#include "Stage.h"

using namespace testing;

using Stage = flash::display::Stage;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 20;
}

class StageTest : public Test {
public:
    StageTest()
        : stage(WIDTH, HEIGHT) {}

    Stage stage;
};

TEST_F(StageTest, Constructor) {
    ASSERT_EQ(stage.width(), WIDTH);
    ASSERT_EQ(stage.height(), HEIGHT);
}

