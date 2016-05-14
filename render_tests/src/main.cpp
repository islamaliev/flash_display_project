#include <Stage.h>
#include <FileLoader.h>
#include <Texture.h>
#include <Bitmap.h>
#include <iostream>

using namespace flash::display;

Stage stage = Stage(100, 100);

DisplayObject* obj1;
DisplayObject* obj2;
DisplayObject* obj3;
DisplayObject* obj5;
DisplayObject* obj4;

void test1() {
    constexpr unsigned mul = 10;

    obj1 = new DisplayObject();
    obj1->setScaleX(1 * mul);
    obj1->setScaleY(10 * mul);
    obj1->setX(0 * mul);
    obj1->setY(0 * mul);
    stage.addChild(obj1);

    obj2 = new DisplayObject();
    obj2->setScaleX(1 * mul);
    obj2->setScaleY(10 * mul);
    obj2->setX(9 * mul);
    obj2->setY(0 * mul);
    stage.addChild(obj2);

    obj3 = new DisplayObject();
    obj3->setScaleX(10 * mul);
    obj3->setScaleY(1 * mul);
    obj3->setX(0 * mul);
    obj3->setY(0 * mul);
    stage.addChild(obj3);

    obj4 = new DisplayObject();
    obj4->setScaleX(10 * mul);
    obj4->setScaleY(1 * mul);
    obj4->setX(0 * mul);
    obj4->setY(9 * mul);
    stage.addChild(obj4);

    obj5 = new DisplayObject();
    obj5->setScaleX(6 * mul);
    obj5->setScaleY(6 * mul);
    obj5->setX(2 * mul);
    obj5->setY(2 * mul);
    stage.addChild(obj5);
}

int testIndex = -1;

void offscreenCallback() {
    std::cout << "offscreenCallback" << std::endl;
    if (++testIndex == 0) {
        test1();
    } else {
        std::terminate();
    }
}

int main(int argc, const char** argv) {
    stage.start();

    return 0;
}

void test2() {
    unsigned mul = 10;
    Stage stage(10 * mul, 10 * mul);

    DisplayObject obj1;
    obj1.setScaleX(8 * mul);
    obj1.setScaleY(8 * mul);
    obj1.setX(1 * mul);
    obj1.setY(1 * mul);

    stage.addChild(&obj1);

    stage.start();
}

void tets3() {
    Stage stage(100, 100);

    DisplayObject obj1;
    obj1.setScaleX(20);
    obj1.setScaleY(20);
    obj1.setX(10);
    obj1.setY(10);

    stage.addChild(&obj1);

    DisplayObject obj2;
    obj2.setScaleX(40);
    obj2.setScaleY(40);
    obj2.setX(50);
    obj2.setY(50);
    stage.addChild(&obj2);

    stage.start();
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
