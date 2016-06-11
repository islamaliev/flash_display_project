#include "gmock/gmock-matchers.h"
#include "ComponentContainer.h"

using namespace testing;
using namespace flash;

using Container = ComponentContainer;

size_t getAddress(const SpatialComponent& c) {
    return reinterpret_cast<size_t>(&c);
}

size_t getAddress(const int& c) {
    return reinterpret_cast<size_t>(&c);
}

class Component_SortingTest : public Test {
public:
    static const unsigned SIZE = 4;
    static const unsigned SPACIAL_SIZE = sizeof(SpatialComponent);
    static const unsigned DEPTH_SIZE = sizeof(int);

    Container* container{nullptr};

    void assertSort(const std::vector<int>& expectedOrder) {
        if (expectedOrder.size() > m_entities.size()) {
            FAIL();
        }
        auto spatialBaseAddr = std::numeric_limits<size_t>::max();
        auto depthBaseAddr = spatialBaseAddr;
        for (const auto& e : m_entities) {
            auto addr = getAddress(container->getSpatialComponent(*e));
            if (addr < spatialBaseAddr)
                spatialBaseAddr = addr;
            addr = getAddress(container->getDepthComponent(*e));
            if (addr < depthBaseAddr)
                depthBaseAddr = addr;
        }

        std::vector<int> actualSpatialOrder = {};
        std::vector<int> actualDepthOrder = {};
        for (int i = 0; i < expectedOrder.size(); ++i) {
            const auto& e = *m_entities[i];
            auto addr = getAddress(container->getSpatialComponent(e));
            actualSpatialOrder.push_back((int) (addr - spatialBaseAddr) / SPACIAL_SIZE);

            addr = getAddress(container->getDepthComponent(e));
            actualDepthOrder.push_back((int) (addr - depthBaseAddr) / DEPTH_SIZE);
        }

        ASSERT_THAT(actualSpatialOrder, Eq(expectedOrder));
        ASSERT_THAT(actualDepthOrder, Eq(expectedOrder));
    }

    const Entity& createEntity() {
        const auto& entity = container->createEntity();
        m_entities.push_back(&entity);
        return entity;
    }

protected:
    void SetUp() override {
        container = new Container(SIZE);

    }

    void TearDown() override {
        if (container) {
            delete container;
        }
        m_entities.clear();
    }

private:
    std::vector<const Entity*> m_entities;
};

TEST_F(Component_SortingTest, EmptyContainer) {
    container->sort();
}

TEST_F(Component_SortingTest, OneEntityNotAltered) {
    const auto& entity = createEntity();
    auto oldAddr = getAddress(container->getSpatialComponent(entity));
    container->sort();
    auto newAddr = getAddress(container->getSpatialComponent(entity));

    ASSERT_THAT(newAddr, Eq(oldAddr));
}

TEST_F(Component_SortingTest, DISABLED_SwappingTwoElements) {
    auto& e1 = createEntity();
    auto& e2 = createEntity();

    container->getOrderComponent(e1) = 0;
    container->getOrderComponent(e2) = 1;
    container->sort();

    assertSort({0, 1});

    container->getOrderComponent(e1) = 1;
    container->getOrderComponent(e2) = 0;
    container->sort();

    assertSort({1, 0});
}
