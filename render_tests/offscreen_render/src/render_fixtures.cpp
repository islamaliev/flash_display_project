#define DEFINE_OFFSCREEN

#include "render_fixtures.h"
#include <FileLoader.h>
#include <Texture.h>
#include <Image.h>
#include <Shape.h>

using namespace offscreen;
using namespace flash::display;

namespace {
    const unsigned DEFAULT_SIZE = 20;
}

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

class SizedChild : public DisplayObjectTest {
public:
    void setUp() override {
        DisplayObjectTest::setUp();
        m_obj->setWidth(W * 0.5f);
        m_obj->setHeight(H * 0.5f);
    }
};

class ScaledChild : public DisplayObjectTest {
public:
    void setUp() override {
        DisplayObjectTest::setUp();
        m_obj->setScaleX(2);
        m_obj->setScaleY(2);
    }
};

class SizedScaledMovedChild : public DisplayObjectTest {
public:
    void setUp() override {
        DisplayObjectTest::setUp();
        m_obj->setScaleX(2);
        m_obj->setWidth(W * 0.4f);
        m_obj->setHeight(H * 0.4f);
        m_obj->setScaleY(2);
        m_obj->setX(W * 0.1f);
        m_obj->setY(H * 0.1f);
    }
};

class TwoChildrenAtCorners : public Test {
public:
    void setUp() override {
        m_obj1 = new Shape();
        m_obj1->setWidth(W * 0.2f);
        m_obj1->setHeight(H * 0.2f);
        m_obj1->setX(W * 0.1f);
        m_obj1->setY(H * 0.1f);

        stage->addChild(m_obj1);

        m_obj2 = new Shape();
        m_obj2->setWidth(W * 0.4f);
        m_obj2->setHeight(H * 0.4f);
        m_obj2->setX(W * 0.5f);
        m_obj2->setY(H * 0.5f);
        stage->addChild(m_obj2);
    }

    void tearDown() override {
        delete m_obj1;
        delete m_obj2;
    }

private:
    DisplayObject* m_obj1;
    DisplayObject* m_obj2;
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

class ChildInMovedContainer : public ParentTest {
public:
    void setUp() override {
        ParentTest::setUp();
        m_child->setWidth(W * 0.5f);
        m_child->setHeight(H * 0.5f);

        m_parent->setX(W * 0.25f);
        m_parent->setY(H * 0.25f);
    }
};

class MovedChildInScaledContainer : public ParentTest {
public:
    void setUp() override {
        ParentTest::setUp();
        m_child->setWidth(W * 0.2f);
        m_child->setHeight(H * 0.2f);
        m_child->setX(W * 0.2f);
        m_child->setY(H * 0.1f);
        m_parent->setScaleX(2);
        m_parent->setScaleY(4);
    }
};

class GrandParentTest : public Test {
public:
    void setUp() override {
        m_child = new Shape();
        m_parent = new DisplayObjectContainer();
        m_grandparent = new DisplayObjectContainer();
        m_parent->addChild(m_child);
        m_grandparent->addChild(m_parent);
        stage->addChild(m_grandparent);
    }

    void tearDown() override {
        delete m_child;
        delete m_parent;
        delete m_grandparent;
    };

protected:
    DisplayObject* m_child;
    DisplayObjectContainer* m_parent;
    DisplayObjectContainer* m_grandparent;
};

class ChildInMovedParentAndGrandParent : public GrandParentTest {
public:
    void setUp() override {
        GrandParentTest::setUp();

        m_child->setWidth(W * 0.4f);
        m_child->setHeight(H * 0.4f);

        m_parent->setX(W * 0.2f);
        m_parent->setY(H * 0.2f);

        m_grandparent->setX(W * 0.2f);
        m_grandparent->setY(H * 0.2f);
    }
};

class ChildInScaledParentAndGrandParent : public GrandParentTest {
public:
    void setUp() override {
        GrandParentTest::setUp();

        m_child->setWidth(W * 0.1f);
        m_child->setHeight(H * 0.1f);

        m_parent->setScaleX(2);
        m_parent->setScaleY(2);

        m_grandparent->setScaleX(2);
        m_grandparent->setScaleY(2);
    }
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
        prepareImage("texture1.jpg", 0, 0, W, H);
    }
};

class ImageAndDisplayObject : public ImageTest {
public:
    void setUp() override {
        ImageTest::setUp();
        
        prepareImage("texture1.jpg", W * 0.1f, H * 0.1f, W * 0.8f, H * 0.4f);
        prepareShape(W * 0.1f, H * 0.6f, W * 0.8f, H * 0.3f);
    }

    virtual void tearDown() override {
        ImageTest::tearDown();
        delete m_displayObject;
    }

private:
    DisplayObject* m_displayObject{nullptr};
};

class TwoImages : public ImageTest {
public:
    void setUp() override {
        ImageTest::setUp();
        prepareImage("texture1.jpg", 0, H * 0.5f, W * 0.5f, H * 0.5f);
        prepareImage("texture2.jpg", W * 0.5f, 0, W * 0.5f, H * 0.5f);
    }
};

class ObjectWithPivot : public DisplayObjectTest {
public:
    void setUp() override {
        DisplayObjectTest::setUp();
        m_obj->setWidth(W * 0.25f);
        m_obj->setHeight(H * 0.25f);
        m_obj->setX(W * 0.5f);
        m_obj->setY(H * 0.5f);
        m_obj->setPivotX(W * 0.25f);
        m_obj->setPivotY(H * 0.25f);
    }
};

class ScaledObjectWithPivot : public DisplayObjectTest {
public:
    void setUp() override {
        DisplayObjectTest::setUp();
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

class InvisibleObject : public DisplayObjectTest {
    void setUp() override {
        DisplayObjectTest::setUp();
        m_obj->setVisible(false);
    }
};

class InvisibleParent : public ParentTest {
    void setUp() override {
        ParentTest::setUp();
        m_parent->setVisible(false);
    }
};

class InvisibleAndVisibleImages : public ImageTest {
    void setUp() override {
        ImageTest::setUp();
        prepareImage("texture1.jpg", 0, 0, W * 0.5f, H * 0.5f)->setVisible(false);

        prepareImage("texture2.jpg", W * 0.5f, H * 0.5f, W * 0.5f, H * 0.5f);
    }
};

class ExceedsMaxTextureUnit : public ImageTest {
    void setUp() override {
        ImageTest::setUp();
        
        prepareImage("texture1.jpg", 0, 0, W * 0.3f, H * 0.5f);
        prepareImage("texture2.jpg", W * 0.5f, H * 0.5f, W * 0.5f, H * 0.5f);
        prepareImage("texture3.jpg", W, 0, W * 0.3f, H * 0.5f)->setPivotX(W);
        prepareImage("texture4.jpg", 0, H * 0.5f, W * 0.5f, H * 0.5f);
        
        prepareShape(W * 0.5f, 0, W * 0.4f, H * 0.5f)->setPivotX(W * 0.2f);
    }
};

class DepthSorting : public ImageTest {
public:
    void setUp() override {
        ImageTest::setUp();
        
        Image* image1 = prepareImage("texture1.jpg",  W * 0.6f, H * 0.6f, W * 0.4f, H * 0.4f);
        Image* image2 = prepareImage("texture2.jpg", W * 0.2f, H * 0.2f, W * 0.4f, H * 0.4f);
        Image* image3 = prepareImage("texture3.jpg", W * 0.8f, H * 0.8f, W * 0.2f, H * 0.2f);
        Image* image4 = prepareImage("texture4.jpg", W * 0.0f, H * 0.0f, W * 0.4f, H * 0.4f);
        
        Shape* shape = prepareShape(W * 0.4f, H * 0.4f, W * 0.4f, H * 0.4f);
        
        stage->addChild(image4);
        stage->addChild(image2);
        stage->addChild(shape);
        stage->addChild(image1);
        stage->addChild(image3);
    }
};

class DepthSortingWithMovedTree : public ImageTest {
    void setUp() override {
        ImageTest::setUp();
        
        DisplayObjectContainer* cont = prepareContainer();
        DisplayObjectContainer* blueRect = prepareRect("blue.jpg", 0, 0, cont);
        DisplayObjectContainer* greenRect = prepareRect("green.jpg", W * 0.05f, H * 0.05f, cont);
        DisplayObjectContainer* yellowRect = prepareRect("yellow.jpg", W * 0.1f, H * 0.1f, cont);
        DisplayObjectContainer* magentaRect = prepareRect("magenta.jpg", W * 0.15f, H * 0.15f, cont);
        DisplayObjectContainer* whiteRect = prepareRect("white.jpg", W * 0.2f, H * 0.2f, cont);
        
        auto tlh = prepareShape(0, H * 0.5f, W * 0.4f, H * 0.05f);
        auto tlv = prepareShape(W * 0.35f, H * 0.5f, W * 0.05f, H * 0.5f);
        
        auto brh = prepareShape(W * 0.5f, H * 0.35f, W * 0.5f, H * 0.05f);
        auto brv = prepareShape(W * 0.5f, 0, W * 0.05f, H * 0.4f);
        
        auto trh = prepareShape(W * 0.5f, H * 0.5f, W * 0.5f, H * 0.05f);
        auto trv = prepareShape(W * 0.5f, H * 0.5f, W * 0.05f, H * 0.5f);
        
        auto blh = prepareShape(0, H * 0.35f, W * 0.4f, H * 0.05f);
        auto blv = prepareShape(W * 0.35f, 0, W * 0.05f, H * 0.4f);
        
        stage->addChild(blueRect);
        stage->addChild(cont);
        cont->addChild(greenRect);
        cont->addChild(tlh);
        cont->addChild(tlv);
        cont->addChild(yellowRect);
        cont->addChild(trh);
        cont->addChild(trv);
        cont->addChild(magentaRect);
        cont->addChild(blh);
        cont->addChild(blv);
        cont->addChild(whiteRect);
        cont->addChild(brh);
        cont->addChild(brv);
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

void offscreen::initFixtures() {
    stage = new flash::display::Stage(W, H);
    RENDER(SizedChild);
    RENDER(ScaledChild);
    RENDER(SizedScaledMovedChild);
    RENDER(TwoChildrenAtCorners);
    RENDER(ChildInMovedContainer);
    RENDER(MovedChildInScaledContainer);
    RENDER(ChildInMovedParentAndGrandParent);
    RENDER(ChildInScaledParentAndGrandParent);
    RENDER(FullscreenImage);
    RENDER(ImageAndDisplayObject);
    RENDER(TwoImages);
    RENDER(ObjectWithPivot);
    RENDER(ScaledObjectWithPivot);
    RENDER(InvisibleObject);
    RENDER(InvisibleParent);
    RENDER(InvisibleAndVisibleImages);
    RENDER(ExceedsMaxTextureUnit);
    RENDER(DepthSorting);
    RENDER(DepthSortingWithMovedTree);
}

void offscreen::clearFixtures() {
    delete stage;
    tests.clear();
}
