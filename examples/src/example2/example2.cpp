#include <FileLoader.h>
#include <Texture.h>
#include <Image.h>
#include <Stage.h>

using Stage = flash::display::Stage;
using Texture = flash::display::Texture;
using DisplayObject = flash::display::DisplayObject;

int main(int argc, const char** argv) {
    Stage stage(800, 600);

    /*DisplayObject obj1;
    obj1.setScaleX(80);
    obj1.setScaleY(20);
    obj1.setX(20);
    obj1.setY(20);

    DisplayObjectContainer parent;
    parent.setY(20);
    parent.addChild(&obj1);

    stage.addChild(&parent);*/

    flash::filesystem::FileLoader loader2;
    loader2.load("texture2.jpg");

    if (loader2.size()) {
        flash::display::Texture* texture = (Texture*) loader2.data();

        flash::display::Image bitmap;
        bitmap.setTexture(texture);
        bitmap.setX(10);
        bitmap.setY(300);
        bitmap.setWidth(100);
        bitmap.setHeight(100);
        stage.addChild(&bitmap);
    }

    flash::filesystem::FileLoader loader;
    loader.load("texture.jpg");

    if (loader.size()) {
        flash::display::Texture* texture = (Texture*) loader.data();

        flash::display::Image bitmap;
        bitmap.setTexture(texture);
        bitmap.setX(200);
        bitmap.setY(150);
        bitmap.setWidth(300);
        bitmap.setHeight(200);
        stage.addChild(&bitmap);
    }

    DisplayObject obj2;
    obj2.setWidth(160);
    obj2.setHeight(400);
    obj2.setX(600);
    obj2.setY(100);
    stage.addChild(&obj2);

    stage.start();

    return 0;
}
