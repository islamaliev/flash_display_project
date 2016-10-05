#include <Stage.h>
#include <FileLoader.h>
#include <Texture.h>
#include <Image.h>
#include <Shape.h>

using namespace flash::display;


const unsigned W = 100;
const unsigned H = 100;

const unsigned DEFAULT_SIZE = 20;

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
        m_obj = new Shape();
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
        m_child = new Shape();
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

class ObjectsTest : public Test {
public:
    virtual void tearDown() override {
        for (auto object : m_objects) {
            delete object;
        }
    }

protected:
    Shape* prepareShape(float x = 0, float y = 0, float width = DEFAULT_SIZE, float height = DEFAULT_SIZE, DisplayObjectContainer* parent = nullptr) {
        Shape* shape = new Shape();
        shape->setX(x);
        shape->setY(y);
        shape->setWidth(width);
        shape->setHeight(height);
        if (!parent)
            parent = stage;
        parent->addChild(shape);
        m_objects.push_back(shape);
        return shape;
    }
    
    DisplayObjectContainer* prepareContainer(float x = 0, float y = 0, DisplayObjectContainer* parent = nullptr) {
        DisplayObjectContainer* container = new DisplayObjectContainer();
        container->setX(x);
        container->setY(y);
        if (!parent)
            parent = stage;
        parent->addChild(container);
        m_objects.push_back(container);
        return container;
    }

private:
    std::vector<DisplayObject*> m_objects;
};

class ImageTest : public ObjectsTest {
public:
    Image* prepareImage(const char* texturePath, float x = 0, float y = 0, float width = DEFAULT_SIZE, float height = DEFAULT_SIZE, DisplayObjectContainer* parent = nullptr) {
        flash::filesystem::FileLoader loader;
        loader.load(texturePath);

        if (loader.size()) {
            Texture* texture = (Texture*) loader.data();
            Image* image = new Image();
            image->setTexture(texture);
            image->setX(x);
            image->setY(y);
            image->setWidth(width);
            image->setHeight(height);
            if (!parent)
                parent = stage;
            parent->addChild(image);
            m_images.push_back(image);
            m_textures.push_back(texture);
            return image;
        }
        return nullptr;
    }

    void tearDown() override {
        ObjectsTest::tearDown();
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

class FullscreenImage: public ImageTest {
public:
    void setUp() override {
        ImageTest::setUp();
        Image* image = prepareImage("texture1.jpg");
        image->setX(0);
        image->setY(0);
        image->setWidth(W);
        image->setHeight(H);
    }
};

class DepthSortingWithMovedTree : public ImageTest {
    void setUp() override {
        ImageTest::setUp();
        
//        DisplayObjectContainer* cont = prepareContainer();
        DisplayObjectContainer* cont = stage;
        DisplayObjectContainer* blueRect = prepareRect("blue.jpg", 0, 0, cont);
        DisplayObjectContainer* greenRect = prepareRect("green.jpg", W * 0.05f, H * 0.05f, cont);
        DisplayObjectContainer* yellowRect = prepareRect("yellow.jpg", W * 0.1f, H * 0.1f, cont);
        DisplayObjectContainer* magentaRect = prepareRect("magenta.jpg", W * 0.15f, H * 0.15f, cont);
        DisplayObjectContainer* whiteRect = prepareRect("white.jpg", W * 0.2f, H * 0.2f, cont);
    
        auto shape1 = prepareShape(W * 0.4f, H * 0.4f, W * 0.05f, H * 0.7f);
        auto shape2 = prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        /*prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);
        prepareShape(W * 0.4f, H * 0.4f, W * 0.7f, H * 0.05f);*/
    
        /*stage->addChild(cont);
//        cont->addChild(shape1);
//        cont->addChild(shape2);
        cont->addChild(blueRect);
        cont->addChild(greenRect);
        cont->addChild(yellowRect);
        cont->addChild(magentaRect);
        cont->addChild(whiteRect);*/
    
        /*cont->addChild(greenRect);
        cont->addChild(shape1);
        cont->addChild(shape2);
        cont->addChild(magentaRect);
        cont->addChildAt(yellowRect, 1);
        cont->addChild(whiteRect);
        stage->addChild(cont);
        stage->addChildAt(blueRect, 0);*/
    }
    
    DisplayObjectContainer* prepareRect(const char* texturePath, float x = 0, float y = 0, DisplayObjectContainer* parent = nullptr) {
        DisplayObjectContainer* container = prepareContainer(x, y, parent);
    
        prepareImage(texturePath, 0, 0, W * 0.05f, H * 0.7f, container);
        prepareImage(texturePath, 0, 0, W * 0.7f, H * 0.05f, container);
        prepareImage(texturePath, W * 0.65f, 0, W * 0.05f, H * 0.7f, container);
        prepareImage(texturePath, 0, H * 0.65f, W * 0.7f, H * 0.05f, container);
    
        return container;
    }
    
};

class InvisibleAndVisibleImages : public ImageTest {
    void setUp() override {
        ImageTest::setUp();
        Image* image = prepareImage("texture1.jpg");
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

    Test* test = new DepthSortingWithMovedTree();
    test->setUp();

    stage->start();
}

int main(int argc, const char** argv) {
    example1();
}
