#include <Stage.h>
#include <FileLoader.h>
#include <Texture.h>
#include <Image.h>

using namespace flash::display;


const unsigned W = 100;
const unsigned H = 100;

flash::display::Stage* stage;

class Test {
public:
    virtual ~Test() {};

    virtual void setUp() {}

    virtual void tearDown() {}
};

class DisplayObject_Test : public Test {
public:
    virtual void setUp() override {
        m_obj = new DisplayObject();
        stage->addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

protected:
    DisplayObject* m_obj;
};

class TextureTest : public Test {
public:
    void setUp() override {
    }

    Image* prepareImage(const char* texturePath) {
        flash::filesystem::FileLoader loader;
        loader.load(texturePath);

        if (loader.size()) {
            Texture* texture = (Texture*) loader.data();
            Image* image = new Image();
            image->setTexture(texture);
            stage->addChild(image);
            m_images.push_back(image);
            m_textures.push_back(texture);
            return image;
        }
        return nullptr;
    }

    virtual void tearDown() override {
        for (auto texture : m_textures) {
            texture->dispose();
        }
        for (auto image : m_images) {
            delete image;
        }
    }

protected:
    std::vector<Image*> m_images;
    std::vector<Texture*> m_textures;
};

class TextureAndDisplayObject : public TextureTest {
public:
    void setUp() override {
        TextureTest::setUp();
        Image* image = prepareImage("texture.jpg");
//        image->setX(W * 0.1f);
//        image->setY(H * 0.1f);
        image->setWidth(W * 0.5f);
        image->setHeight(H * 0.5f);

        m_displayObject = new DisplayObject();
        m_displayObject->setX(W * 0.1f);
        m_displayObject->setY(H * 0.6f);
        m_displayObject->setScaleX(W * 0.8f);
        m_displayObject->setScaleY(H * 0.3f);
        stage->addChild(m_displayObject);
    }

    virtual void tearDown() override {
        TextureTest::tearDown();
        delete m_displayObject;
    }

private:
    DisplayObject* m_displayObject{nullptr};
};

class BlaTest : public DisplayObject_Test {
public:
    void setUp() override {
        DisplayObject_Test::setUp();
        m_obj->setWidth(W * 0.1f);
        m_obj->setHeight(H * 0.1f);
        m_obj->setX(W * 0.5f);
        m_obj->setY(H * 0.5f);
        m_obj->setScaleX(5);
        m_obj->setScaleY(5);
        m_obj->setPivotX(W * 0.05f);
        m_obj->setPivotY(H * 0.05f);
    }
};

void example1() {
    stage = new Stage(W, H);

    Test* test = new BlaTest();
//    Test* test = new TextureAndDisplayObject();
    test->setUp();

    stage->start();
}

void example2() {
    Stage stage(800, 600);

    DisplayObject obj1;
    obj1.setScaleX(200);
    obj1.setScaleY(80);
    obj1.setX(100);
    obj1.setY(450);

    stage.addChild(&obj1);


    DisplayObject obj2;
    obj2.setScaleX(80);
    obj2.setScaleY(80);
    obj2.setX(40);
    obj2.setY(80);
//    stage.addChild(&obj2);


    flash::filesystem::FileLoader loader;
    loader.load("texture_big.jpg");

    if (loader.size()) {
        flash::display::Texture* texture = (Texture*) loader.data();
//        texture->bindData();

        flash::display::Image image;
        image.setTexture(texture);
        image.setX(100);
        image.setY(100);
        image.setScaleX(300);
        image.setScaleY(200);
        stage.addChild(&image);
    }

    loader.load("texture2_big.jpg");

    if (loader.size()) {
        flash::display::Texture* texture = (Texture*) loader.data();
//        texture->bindData();

        flash::display::Image image;
        image.setTexture(texture);
        image.setX(500);
        image.setY(200);
        image.setScaleX(200);
        image.setScaleY(200);
        stage.addChild(&image);
    }

    stage.start();
}

int main(int argc, const char** argv) {
    example1();
//    example2();
}
