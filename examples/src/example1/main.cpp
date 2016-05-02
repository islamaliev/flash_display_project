#include <Stage.h>

int main(int argc, const char** argv) {
    flash::display::Stage stage(800, 600);

    flash::display::DisplayObject obj1;
    obj1.setWidth(80);
    obj1.setHeight(20);
    obj1.setX(20);
    obj1.setY(20);
    stage.addChild(&obj1);

    flash::display::DisplayObject obj2;
    obj2.setWidth(40);
    obj2.setHeight(100);
    obj2.setX(740);
    obj2.setY(480);
    stage.addChild(&obj2);

    stage.start();

    return 0;
}