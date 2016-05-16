#pragma once

#include <Stage.h>
#include <vector>

#define RENDER(TestClass) tests.emplace_back(#TestClass, new TestClass());

#ifdef DEFINE_OFFSCREEN
    #define EXTERN
#else
    #define EXTERN extern
#endif

namespace offscreen {
    const unsigned W = 100;
    const unsigned H = 100;

    void initFixtures();

    class Test {
    public:
        virtual ~Test() {};

        virtual void setUp() {}

        virtual void tearDown() {}
    };

    EXTERN flash::display::Stage* stage;

    EXTERN std::vector<std::pair<const char*, offscreen::Test*>> tests;
}

