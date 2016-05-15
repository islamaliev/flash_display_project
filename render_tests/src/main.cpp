#include <Stage.h>
#include <FileLoader.h>
#include <Texture.h>
#include <Bitmap.h>
#include <vector>

using namespace flash::display;

class Test {
public:
    virtual ~Test() = default;

    virtual void setUp() {}
    
    virtual void tearDown() {}
};

std::vector<std::pair<const char*, Test*>> tests;

Stage stage = Stage(100, 100);

Test* currentTest{nullptr};

int testIndex = 0;

#define RENDER(TestClass) tests.emplace_back(#TestClass, new TestClass());

class Test1 : public Test {
public:
    static constexpr unsigned mul = 10;

    void setUp() override {
        m_obj1 = new DisplayObject();
        m_obj1->setScaleX(1 * mul);
        m_obj1->setScaleY(10 * mul);
        m_obj1->setX(0 * mul);
        m_obj1->setY(0 * mul);
        stage.addChild(m_obj1);

        m_obj2 = new DisplayObject();
        m_obj2->setScaleX(1 * mul);
        m_obj2->setScaleY(10 * mul);
        m_obj2->setX(9 * mul);
        m_obj2->setY(0 * mul);
        stage.addChild(m_obj2);

        m_obj3 = new DisplayObject();
        m_obj3->setScaleX(10 * mul);
        m_obj3->setScaleY(1 * mul);
        m_obj3->setX(0 * mul);
        m_obj3->setY(0 * mul);
        stage.addChild(m_obj3);

        m_obj4 = new DisplayObject();
        m_obj4->setScaleX(10 * mul);
        m_obj4->setScaleY(1 * mul);
        m_obj4->setX(0 * mul);
        m_obj4->setY(9 * mul);
        stage.addChild(m_obj4);

        m_obj5 = new DisplayObject();
        m_obj5->setScaleX(6 * mul);
        m_obj5->setScaleY(6 * mul);
        m_obj5->setX(2 * mul);
        m_obj5->setY(2 * mul);
        stage.addChild(m_obj5);
    }

    void tearDown() override {
        delete m_obj1;
        delete m_obj2;
        delete m_obj3;
        delete m_obj4;
        delete m_obj5;
    }

private:
    DisplayObject* m_obj1;
    DisplayObject* m_obj2;
    DisplayObject* m_obj3;
    DisplayObject* m_obj4;
    DisplayObject* m_obj5;
};

class Test2 : public Test {
public:
    static constexpr unsigned mul = 10;

    void setUp() override {
        m_obj = new DisplayObject();
        m_obj->setScaleX(8 * mul);
        m_obj->setScaleY(8 * mul);
        m_obj->setX(1 * mul);
        m_obj->setY(1 * mul);

        stage.addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

private:
    DisplayObject* m_obj;
};

void tets3() {
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
}

const char* nextOffscreen() {
    if (currentTest) {
        currentTest->tearDown();
        delete currentTest;
        stage.removeChildren();
    }

    const char* name;
    if (testIndex < tests.size()) {
        currentTest = tests[testIndex].second;
        name = tests[testIndex].first;
    } else {
        std::terminate();
    }
    currentTest->setUp();

    ++testIndex;
    return name;
}

int main(int argc, const char** argv) {
    RENDER(Test1);
    RENDER(Test2);

    stage.start();

    return 0;
}

/*int main(int argc, const char** argv) {
    Stage stage(800, 600);

    DisplayObject obj1;
    obj1.setScaleX(80);
    obj1.setScaleY(20);
    obj1.setX(20);
    obj1.setY(20);

    DisplayObjectContainer parent;
    parent.setY(20);
    parent.addChild(&obj1);

    stage.addChild(&parent);


    DisplayObject obj2;
    obj2.setScaleX(40);
    obj2.setScaleY(100);
    obj2.setX(740);
    obj2.setY(480);
    stage.addChild(&obj2);


    flash::filesystem::FileLoader loader;
    loader.load("texture_big.jpg");

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
}*/
