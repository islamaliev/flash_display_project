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

class DisplayObjectTest : public Test {
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

class ParentTest : public Test {
public:
    void setUp() override {
        m_child = new DisplayObject();
        m_parent = new DisplayObjectContainer();
        m_parent->addChild(m_child);
        stage->addChild(m_parent);
    }

    void tearDown() override {
        delete m_child;
        delete m_parent;
    };

protected:
    DisplayObject* m_child;
    DisplayObjectContainer* m_parent;
};

class ImageTest : public Test {
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

class InvisibleAndVisibleImages : public ImageTest {
    void setUp() override {
        ImageTest::setUp();
        Image* image = prepareImage("texture.jpg");
        image->setWidth(W * 0.5f);
        image->setHeight(H * 0.5f);
        image->setVisible(false);

        Image* image2 = prepareImage("texture2.jpg");
        image2->setX(W * 0.5f);
        image2->setY(H * 0.5f);
        image2->setWidth(W * 0.5f);
        image2->setHeight(H * 0.5f);
    }
};

void example1() {
    stage = new Stage(W, H);

    Test* test = new InvisibleAndVisibleImages();
    test->setUp();

    stage->start();
}

int main(int argc, const char** argv) {
    example1();
}
