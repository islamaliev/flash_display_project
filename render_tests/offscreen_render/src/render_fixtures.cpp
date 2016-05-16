#define DEFINE_OFFSCREEN

#include "render_fixtures.h"
#include <FileLoader.h>
#include <Texture.h>
#include <Bitmap.h>

using namespace offscreen;
using namespace flash::display;

class Test1 : public Test {
public:
    static constexpr unsigned mul = 10;

    void setUp() override {
        m_obj1 = new DisplayObject();
        m_obj1->setScaleX(1 * mul);
        m_obj1->setScaleY(10 * mul);
        m_obj1->setX(0 * mul);
        m_obj1->setY(0 * mul);
        stage->addChild(m_obj1);

        m_obj2 = new DisplayObject();
        m_obj2->setScaleX(1 * mul);
        m_obj2->setScaleY(10 * mul);
        m_obj2->setX(9 * mul);
        m_obj2->setY(0 * mul);
        stage->addChild(m_obj2);

        m_obj3 = new DisplayObject();
        m_obj3->setScaleX(10 * mul);
        m_obj3->setScaleY(1 * mul);
        m_obj3->setX(0 * mul);
        m_obj3->setY(0 * mul);
        stage->addChild(m_obj3);

        m_obj4 = new DisplayObject();
        m_obj4->setScaleX(10 * mul);
        m_obj4->setScaleY(1 * mul);
        m_obj4->setX(0 * mul);
        m_obj4->setY(9 * mul);
        stage->addChild(m_obj4);

        m_obj5 = new DisplayObject();
        m_obj5->setScaleX(6 * mul);
        m_obj5->setScaleY(6 * mul);
        m_obj5->setX(2 * mul);
        m_obj5->setY(2 * mul);
        stage->addChild(m_obj5);
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

        stage->addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

private:
    DisplayObject* m_obj;
};

class Test3 : public Test {
public:
    void setUp() override {
        m_obj = new DisplayObject();
        m_obj->setScaleX(80);
        m_obj->setScaleY(80);
        m_obj->setX(25);
//        m_obj->setY(10);

        stage->addChild(m_obj);
    }

    void tearDown() override {
        delete m_obj;
    }

private:
    DisplayObject* m_obj;
};

void offscreen::initFixtures() {
    stage = new flash::display::Stage(W, H);
    RENDER(Test1);
    RENDER(Test2);
    RENDER(Test3);
}
