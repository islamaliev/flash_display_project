#include "render_fixtures.h"

using namespace flash::display;

using Test = offscreen::Test;

char outputFolder[1024];
char path[1024];

Test* currentTest{nullptr};

int testIndex = 0;

const char* nextOffscreen() {
    if (currentTest) {
        offscreen::stage->removeChildren();
        currentTest->tearDown();
    }

    if (testIndex < offscreen::tests.size()) {
        currentTest = offscreen::tests[testIndex].second;
        strcpy(path, outputFolder);
        strcat(path, offscreen::tests[testIndex].first);
    } else {
        offscreen::stage->stop();
        offscreen::clearFixtures();
        return "";
    }
    currentTest->setUp();

    ++testIndex;
    return path;
}

int main(int argc, const char** argv) {
    if (argc > 1) {
        strcpy(outputFolder, argv[1]);
        size_t n = strlen(argv[1]);
        outputFolder[n] = '/';
        outputFolder[n + 1] = '\0';
    }

    offscreen::initFixtures();

    offscreen::stage->start();

    return 0;
}