#include <Stage.h>
#include <FileLoader.h>
#include <Texture.h>
#include <Bitmap.h>

using namespace flash::display;

/*int main(int argc, const char** argv) {
    unsigned mul = 1;
    Stage stage(10 * mul, 10 * mul);

    DisplayObject obj1;
    obj1.setScaleX(1 * mul);
    obj1.setScaleY(10 * mul);
    obj1.setX(0 * mul);
    obj1.setY(0 * mul);
    stage.addChild(&obj1);

    DisplayObject obj2;
    obj2.setScaleX(1 * mul);
    obj2.setScaleY(10 * mul);
    obj2.setX(9 * mul);
    obj2.setY(0 * mul);
    stage.addChild(&obj2);

    DisplayObject obj3;
    obj3.setScaleX(10 * mul);
    obj3.setScaleY(1 * mul);
    obj3.setX(0 * mul);
    obj3.setY(0 * mul);
    stage.addChild(&obj3);

    DisplayObject obj4;
    obj4.setScaleX(10 * mul);
    obj4.setScaleY(1 * mul);
    obj4.setX(0 * mul);
    obj4.setY(9 * mul);
    stage.addChild(&obj4);

    DisplayObject obj5;
    obj5.setScaleX(6 * mul);
    obj5.setScaleY(6 * mul);
    obj5.setX(2 * mul);
    obj5.setY(2 * mul);
    stage.addChild(&obj5);

    stage.start();

    return 0;
}*/

/*
int main(int argc, const char** argv) {
    unsigned mul = 10;
    Stage stage(10 * mul, 10 * mul);

    DisplayObject obj1;
    obj1.setScaleX(8 * mul);
    obj1.setScaleY(8 * mul);
    obj1.setX(1 * mul);
    obj1.setY(1 * mul);

    stage.addChild(&obj1);

    stage.start();

    return 0;
}
*/

/*int main(int argc, const char** argv) {
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

    return 0;
}*/

int main(int argc, const char** argv) {
    Stage stage(800, 600);

    DisplayObject obj1;
    obj1.setScaleX(80);
    obj1.setScaleY(20);
    obj1.setX(20);
//    obj1.setY(20);

    DisplayObjectContainer parent;
    parent.setY(20);
    parent.addChild(&obj1);

//    stage.addChild(&parent);


    DisplayObject obj2;
//    obj2.setWidth(40);
//    obj2.setHeight(100);
    obj2.setScaleX(40);
    obj2.setScaleY(100);
    obj2.setX(740);
    obj2.setY(480);
//    stage.addChild(&obj2);


    flash::filesystem::FileLoader loader;
    loader.load("wood_small.jpg");

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
}
