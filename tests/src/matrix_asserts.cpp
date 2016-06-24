#include "matrix_asserts.h"

std::string toString(const flash::math::Mat4& m) {
    char buf[160];
    sprintf(buf, "[%.2f, %.2f, %.2f, %.2f,   %.2f, %.2f, %.2f, %.2f,   %.2f, %.2f, %.2f, %.2f,   %.2f, %.2f, %.2f, %.2f]"
            , m.v1.x, m.v1.y, m.v1.z, m.v1.w, m.v2.x, m.v2.y, m.v2.z, m.v2.w
            , m.v3.x, m.v3.y, m.v3.z, m.v3.w, m.vt.x, m.vt.y, m.vt.z, m.vt.w);
    return std::string(buf);
}

::testing::AssertionResult MatrixEQ(const flash::math::Mat4& actual, const flash::math::Mat4& expected) {
    if (!actual.isEqual(expected)) {
        return ::testing::AssertionFailure() << "\nactual matrix:   " << toString(actual)
               << "\nexpected matrix: " << toString(expected);
    }
    return ::testing::AssertionSuccess();
}
