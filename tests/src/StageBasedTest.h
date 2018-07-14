#pragma once

#include "gmock/gmock-matchers.h"
#include "Stage.h"

using namespace testing;

using Stage = flash::display::Stage;

#define STAGE_WIDTH 40
#define STAGE_HEIGHT 40

class StageBasedTest : public Test {
public:
    static Stage& stage() {
        static Stage stageInstance(STAGE_WIDTH, STAGE_HEIGHT);
        return stageInstance;
    }
    
    ~StageBasedTest() {
        stage().removeChildren();
    }
};