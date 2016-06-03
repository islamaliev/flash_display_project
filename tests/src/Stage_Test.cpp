#include "gmock/gmock-matchers.h"
#include "Stage.h"

using namespace testing;

using Stage = flash::display::Stage;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 20;
}

class Stage_Test : public Test {
public:
    Stage_Test()
        : stage(WIDTH, HEIGHT) {}

    Stage stage;
};

TEST_F(Stage_Test, Constructor) {
    ASSERT_EQ(stage.width(), WIDTH);
    ASSERT_EQ(stage.height(), HEIGHT);
}

