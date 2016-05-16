#include "render_fixtures.h"

using namespace flash::display;

using Test = offscreen::Test;

char outputFolder[1024];
char path[1024];

Test* currentTest{nullptr};

int testIndex = 0;

const char* nextOffscreen() {
    if (currentTest) {
        currentTest->tearDown();
        delete currentTest;
        offscreen::stage->removeChildren();
    }

    if (testIndex < offscreen::tests.size()) {
        currentTest = offscreen::tests[testIndex].second;
        strcpy(path, outputFolder);
        strcat(path, offscreen::tests[testIndex].first);
    } else {
        offscreen::stage->stop();
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

/*int main(int argc, const char** argv) {
    Stage stage(800, 600);

    DisplayObject obj1;
    obj1.setScaleX(80);
    obj1.setScaleY(20);
    obj1.setX(20);
    obj1.setY(20);

    DisplayObjectContainer parent;
    parent.setY(20);
    parent.addChild(&obj1);

    stage.addChild(&parent);


    DisplayObject obj2;
    obj2.setScaleX(40);
    obj2.setScaleY(100);
    obj2.setX(740);
    obj2.setY(480);
    stage.addChild(&obj2);


    flash::filesystem::FileLoader loader;
    loader.load("texture_big.jpg");

    if (loader.size()) {
        flash::display::Texture* texture = (Texture*) loader.data();

        flash::display::Bitmap bitmap;
        bitmap.setTexture(texture);
        bitmap.setX(200);
        bitmap.setY(150);
        bitmap.setScaleX(400);
        bitmap.setScaleY(300);
        stage.addChild(&bitmap);
    }
    stage.start();

    return 0;
}*/
