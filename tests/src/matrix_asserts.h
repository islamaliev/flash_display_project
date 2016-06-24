#pragma once

#include <string>
#include "Mat4.h"
#include "gtest/gtest.h"

namespace testing {
    class AssertionResult;
};

extern std::string toString(const flash::math::Mat4& m);

extern ::testing::AssertionResult MatrixEQ(const flash::math::Mat4& actual, const flash::math::Mat4& expected);

