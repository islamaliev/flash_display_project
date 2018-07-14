#include "Shape.h"
#include "StageBasedTest.h"

using Shape = flash::display::Shape;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;

namespace {
    class SpyDisplayObjectContainer : public DisplayObjectContainer {
    public:
        static int s_numDestructorCalls;
        
        ~SpyDisplayObjectContainer() {
            m_isDestructed = true;
            ++s_numDestructorCalls;
        }
        
        bool isDestructed() const {
            return m_isDestructed;
        }
        
    private:
        bool m_isDestructed{false};
    };
    
    int SpyDisplayObjectContainer::s_numDestructorCalls = 0;
}

class Stage_Test : public StageBasedTest {
public:
};

TEST_F(Stage_Test, Constructor) {
    ASSERT_EQ(stage().width(), STAGE_WIDTH);
    ASSERT_EQ(stage().height(), STAGE_HEIGHT);
}

TEST_F(Stage_Test, ClearRemoveChildren) {
    Shape* obj1 = new Shape();
    Shape* obj2 = new Shape();
    stage().addChild(  obj1);
    stage().addChild(obj2);
    ASSERT_THAT(stage().treeSize(), Eq(3));
    ASSERT_THAT(stage().numChildren(), Eq(2));
    stage().removeChildren();
    ASSERT_THAT(stage().treeSize(), Eq(1));
    ASSERT_THAT(stage().numChildren(), Eq(0));
}

TEST_F(Stage_Test, ClearDescructsTree) {
    SpyDisplayObjectContainer* grandParent = new SpyDisplayObjectContainer();
    SpyDisplayObjectContainer* parent = new SpyDisplayObjectContainer();
    SpyDisplayObjectContainer* child1 = new SpyDisplayObjectContainer();
    SpyDisplayObjectContainer* child2 = new SpyDisplayObjectContainer();
    SpyDisplayObjectContainer* notChild = new SpyDisplayObjectContainer();
    grandParent->addChild(parent);
    parent->addChild(child1);
    parent->addChild(child2);
    stage().addChild(grandParent);
    ASSERT_THAT(SpyDisplayObjectContainer::s_numDestructorCalls, Eq(0));
    stage().removeChildren();
    ASSERT_THAT(SpyDisplayObjectContainer::s_numDestructorCalls, Eq(4));
    ASSERT_FALSE(notChild->isDestructed());
    delete notChild;
}

TEST_F(Stage_Test, ClearDoesNotTouchNotInTreeEntities) {
    DisplayObjectContainer* grandParent = new DisplayObjectContainer();
    DisplayObjectContainer* parent = new DisplayObjectContainer();
    Shape* notChild1 = new Shape();
    Shape* child1 = new Shape();
    Shape* notChild2 = new Shape();
    Shape* child2 = new Shape();
    grandParent->addChild(parent);
    parent->addChild(child1);
    parent->addChild(child2);
    stage().addChild(grandParent);
    
    notChild1->setWidth(7);
    notChild2->setWidth(13);
    stage().removeChildren();
    
    grandParent = new DisplayObjectContainer();
    parent = new DisplayObjectContainer();
    child1 = new Shape();
    child2 = new Shape();
    grandParent->addChild(parent);
    parent->addChild(child1);
    parent->addChild(child2);
    stage().addChild(grandParent);
    
    ASSERT_THAT(notChild1->width(), Eq(7));
    ASSERT_THAT(notChild2->width(), Eq(13));
    delete notChild1;
    delete notChild2;
}


