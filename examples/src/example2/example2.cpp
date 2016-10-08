#include <FileLoader.h>
#include <Texture.h>
#include <Image.h>
#include <Stage.h>
#include <Shape.h>

using Stage = flash::display::Stage;
using Texture = flash::display::Texture;
using Shape = flash::display::Shape;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;
using Image = flash::display::Image;

int main(int argc, const char** argv) {
    Stage stage(800, 600);
//    stage.init();

    Shape obj1;                         // 1
    obj1.setWidth(300);
    obj1.setHeight(100);
    obj1.setX(20);
    obj1.setY(20);

    stage.addChild(&obj1);

    flash::filesystem::FileLoader loader;
    loader.load("texture1.jpg");

    Image* image1;
    if (loader.size()) {
        flash::display::Texture* texture = (Texture*) loader.data();

        image1 = new Image();           // 2
        image1->setTexture(texture);
        image1->setX(10);
        image1->setY(300);
        image1->setWidth(100);
        image1->setHeight(100);
        stage.addChild(image1);
    }

    flash::filesystem::FileLoader loader2;
    loader2.load("texture2.jpg");

    /**/
    Image* image2;
    if (loader2.size()) {
        flash::display::Texture* texture = (Texture*) loader2.data();

        image2 = new Image();           // 3
        image2->setTexture(texture);
        image2->setX(200);
        image2->setY(250);
        image2->setWidth(300);
        image2->setHeight(200);
        stage.addChild(image2);
    }
    
    DisplayObjectContainer parent2;     // 4
    parent2.setX(600);
    stage.addChild(&parent2);
    
    DisplayObjectContainer parent3;     // 5
    parent2.setY(100);
    parent2.addChild(&parent3);

    Shape obj2;                         // 6
    obj2.setWidth(160);
    obj2.setHeight(400);
    parent3.addChild(&obj2);

    flash::filesystem::FileLoader loader3;
    loader3.load("texture2.jpg");

    Image* image3;
    if (loader3.size()) {
        flash::display::Texture* texture = (Texture*) loader3.data();

        image3 = new Image();           // 7
        image3->setTexture(texture);
        image3->setX(-80);
        image3->setY(0);
        image3->setWidth(50);
        image3->setHeight(200);
        parent3.addChild(image3);
    }

    stage.start();

    return 0;
}
