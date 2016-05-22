#define DEFINE_OFFSCREEN

#include "render_fixtures.h"
#include <FileLoader.h>
#include <Texture.h>
#include <Image.h>

using namespace offscreen;
using namespace flash::display;

class SizedChild : public Test {
public:
    void setUp() override {
        m_obj = new DisplayObject();
        m_obj->setWidth(W * 0.5f);
        m_obj->setHeight(H * 0.5f);
        stage->addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

private:
    DisplayObject* m_obj;
};

class ScaledChild : public Test {
public:
    void setUp() override {
        m_obj = new DisplayObject();
        m_obj->setScaleX(2);
        m_obj->setScaleY(2);
        stage->addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

private:
    DisplayObject* m_obj;
};

class SizedScaledMovedChild : public Test {
public:
    void setUp() override {
        m_obj = new DisplayObject();
        m_obj->setScaleX(2);
        m_obj->setWidth(W * 0.4f);
        m_obj->setHeight(H * 0.4f);
        m_obj->setScaleY(2);
        m_obj->setX(W * 0.1f);
        m_obj->setY(H * 0.1f);
        stage->addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

private:
    DisplayObject* m_obj;
};

class TwoChildrenAtCorners : public Test {
public:
    void setUp() override {
        m_obj1 = new DisplayObject();
        m_obj1->setWidth(W * 0.2f);
        m_obj1->setHeight(H * 0.2f);
        m_obj1->setX(W * 0.1f);
        m_obj1->setY(H * 0.1f);

        stage->addChild(m_obj1);

        m_obj2 = new DisplayObject();
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
        m_child = new DisplayObject();
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

class FullscreenTexture : public TextureTest {
public:
    void setUp() override {
        TextureTest::setUp();
        Image* image = prepareImage("texture.jpg");
        image->setX(0);
        image->setY(0);
        image->setWidth(W);
        image->setHeight(H);
    }
};

class TextureAndDisplayObject : public TextureTest {
public:
    void setUp() override {
        TextureTest::setUp();
        Image* image = prepareImage("texture.jpg");
        image->setX(W * 0.1f);
        image->setY(H * 0.1f);
        image->setWidth(W * 0.8f);
        image->setHeight(H * 0.4f);

        m_displayObject = new DisplayObject();
        m_displayObject->setX(W * 0.1f);
        m_displayObject->setY(H * 0.6f);
        m_displayObject->setWidth(W * 0.8f);
        m_displayObject->setHeight(H * 0.3f);
        stage->addChild(m_displayObject);
    }

    virtual void tearDown() override {
        TextureTest::tearDown();
        delete m_displayObject;
    }

private:
    DisplayObject* m_displayObject{nullptr};
};

class TwoTextures : public TextureTest {
public:
    void setUp() override {
        TextureTest::setUp();
        Image* image = prepareImage("texture.jpg");
        image->setX(0);
        image->setY(H * 0.5f);
        image->setWidth(W * 0.5f);
        image->setHeight(H * 0.5f);

        Image* image2 = prepareImage("texture2.jpg");
        image2->setX(W * 0.5f);
        image2->setY(0);
        image2->setWidth(W * 0.5f);
        image2->setHeight(H * 0.5f);
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
    RENDER(FullscreenTexture);
    RENDER(TextureAndDisplayObject);
    RENDER(TwoTextures);
}

void offscreen::clearFixtures() {
    delete stage;
    for (auto it = tests.rbegin(); it != tests.rend(); ++it) {
        delete (*it).second;
    }
}
