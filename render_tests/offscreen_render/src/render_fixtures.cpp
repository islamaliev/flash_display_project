#define DEFINE_OFFSCREEN

#include "render_fixtures.h"
#include <FileLoader.h>
#include <Texture.h>
#include <Bitmap.h>

using namespace offscreen;
using namespace flash::display;

class ScaledChild : public Test {
public:
    void setUp() override {
        m_obj = new DisplayObject();
        m_obj->setScaleX(W / 2);
        m_obj->setScaleY(H / 2);
        stage->addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

private:
    DisplayObject* m_obj;
};

class ScaledMovedChild : public Test {
public:
    void setUp() override {
        m_obj = new DisplayObject();
        m_obj->setScaleX(W / 2);
        m_obj->setScaleY(H / 2);
        m_obj->setX(W / 4);
        m_obj->setY(H / 4);
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
        m_obj1->setScaleX(W * 0.2f);
        m_obj1->setScaleY(H * 0.2f);
        m_obj1->setX(W * 0.1f);
        m_obj1->setY(H * 0.1f);

        stage->addChild(m_obj1);

        m_obj2 = new DisplayObject();
        m_obj2->setScaleX(W * 0.4f);
        m_obj2->setScaleY(H * 0.4f);
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

class ChildInMovedContainer : public Test {
public:
    void setUp() override {
        m_child = new DisplayObject();
        m_child->setScaleX(50);
        m_child->setScaleY(50);

        m_parent = new DisplayObjectContainer();
        m_parent->setX(25);
        m_parent->setY(25);

        m_parent->addChild(m_child);
        stage->addChild(m_parent);
    }

    void tearDown() override {
        delete m_child;
        delete m_parent;
    };

private:
    DisplayObject* m_child;
    DisplayObjectContainer* m_parent;
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

        m_child->setScaleX(40);
        m_child->setScaleY(40);

        m_parent->setX(20);
        m_parent->setY(20);

        m_grandparent->setX(20);
        m_grandparent->setY(20);
    }
};

class ChildInScaledParentAndGrandParent : public GrandParentTest {
public:
    void setUp() override {
        GrandParentTest::setUp();

        m_child->setScaleX(10);
        m_child->setScaleY(10);

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

    Bitmap* prepareBitmap(const char* texturePath) {
        flash::filesystem::FileLoader loader;
        loader.load(texturePath);

        if (loader.size()) {
            Texture* texture = (Texture*) loader.data();
            Bitmap* bitmap = new Bitmap();
            bitmap->setTexture(texture);
            stage->addChild(bitmap);
            m_bitmaps.push_back(bitmap);
            m_textures.push_back(texture);
            return bitmap;
        }
        return nullptr;
    }

    virtual void tearDown() override {
        for (auto texture : m_textures) {
            texture->dispose();
        }
        for (auto bitmap : m_bitmaps) {
            delete bitmap;
        }
    }

protected:
    std::vector<Bitmap*> m_bitmaps;
    std::vector<Texture*> m_textures;
};

class FullscreenTexture : public TextureTest {
public:
    void setUp() override {
        TextureTest::setUp();
        Bitmap* bitmap = prepareBitmap("texture.jpg");
        bitmap->setX(0);
        bitmap->setY(0);
        bitmap->setScaleX(W);
        bitmap->setScaleY(H);
    }
};

class TextureAndDisplayObject : public TextureTest {
public:
    void setUp() override {
        TextureTest::setUp();
        Bitmap* bitmap = prepareBitmap("texture.jpg");
        bitmap->setX(W * 0.1f);
        bitmap->setY(H * 0.1f);
        bitmap->setScaleX(W * 0.8f);
        bitmap->setScaleY(H * 0.4f);

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

class TwoTextures : public TextureTest {
public:
    void setUp() override {
        TextureTest::setUp();
        Bitmap* bitmap = prepareBitmap("texture.jpg");
        bitmap->setX(0);
        bitmap->setY(H * 0.5f);
        bitmap->setScaleX(W * 0.5f);
        bitmap->setScaleY(H * 0.5f);

        Bitmap* bitmap2 = prepareBitmap("texture2.jpg");
        bitmap2->setX(W * 0.5f);
        bitmap2->setY(0);
        bitmap2->setScaleX(W * 0.5f);
        bitmap2->setScaleY(H * 0.5f);
    }
};

void offscreen::initFixtures() {
    stage = new flash::display::Stage(W, H);
    RENDER(ScaledChild);
    RENDER(ScaledMovedChild);
    RENDER(TwoChildrenAtCorners);
    RENDER(ChildInMovedContainer);
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
