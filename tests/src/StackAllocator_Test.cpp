#include "gmock/gmock-matchers.h"
#include "StackAllocator.h"

using namespace testing;
using namespace flash;

using StackAllocator = allocator::StackAllocator;
using Marker = StackAllocator::Marker;

size_t getAddress(void* p) {
    return reinterpret_cast<size_t>(p);
}

class StackAllocator_Test : public Test {
public:
    static const size_t INT_SIZE = sizeof(int);
    static const size_t STACK_SIZE = INT_SIZE * 4;

    StackAllocator_Test()
            : m_allocator(STACK_SIZE) {}

    StackAllocator m_allocator;
};

TEST_F(StackAllocator_Test, MarkerChanges_ifAllocationTookPlace) {
    Marker m1 = m_allocator.getMarker();
    m_allocator.alloc(INT_SIZE);
    Marker m2 = m_allocator.getMarker();
    ASSERT_THAT(m2, Not(m1));
}

TEST_F(StackAllocator_Test, NextAllocationAddressIsHigher) {
    void* p1 = m_allocator.alloc(INT_SIZE);
    void* p2 = m_allocator.alloc(INT_SIZE);
    ASSERT_THAT(getAddress(p2), Eq(getAddress(p1) + INT_SIZE));
}

TEST_F(StackAllocator_Test, Fails_ifRequestedMoreThanCapacity) {
    m_allocator.alloc(STACK_SIZE);
    ASSERT_DEATH(m_allocator.alloc(1), "");
}

TEST_F(StackAllocator_Test, Clear) {
    m_allocator.alloc(STACK_SIZE);
    m_allocator.clear();
    m_allocator.alloc(STACK_SIZE);
}

TEST_F(StackAllocator_Test, FreeToMarkerShrinksAllocator) {
    m_allocator.alloc(STACK_SIZE / 2);
    Marker m = m_allocator.getMarker();
    m_allocator.alloc(STACK_SIZE / 2);
    m_allocator.freeToMarker(m);
    m_allocator.alloc(STACK_SIZE / 2);
}

TEST_F(StackAllocator_Test, FreeToMarkerClearTillGivenMarker) {
    int* p1 = (int*) m_allocator.alloc(INT_SIZE);
    *p1 = 1;
    int* p2 = (int*) m_allocator.alloc(INT_SIZE);
    *p2 = 2;
    Marker m = m_allocator.getMarker();
    int* p3 = (int*) m_allocator.alloc(INT_SIZE);
    *p3 = 3;
    int* p4 = (int*) m_allocator.alloc(INT_SIZE);
    *p4 = 4;
    ASSERT_THAT(*p1, Eq(1));
    ASSERT_THAT(*p2, Eq(2));
    ASSERT_THAT(*p3, Eq(3));
    ASSERT_THAT(*p4, Eq(4));

    m_allocator.freeToMarker(m);

    int* p5 = (int*) m_allocator.alloc(INT_SIZE);
    *p5 = 5;
    int* p6 = (int*) m_allocator.alloc(INT_SIZE);
    *p6 = 6;

    ASSERT_THAT(*p1, Eq(1));
    ASSERT_THAT(*p2, Eq(2));
    ASSERT_THAT(*p3, Eq(5));
    ASSERT_THAT(*p4, Eq(6));
    ASSERT_THAT(*p5, Eq(5));
    ASSERT_THAT(*p6, Eq(6));
}

TEST_F(StackAllocator_Test, FreeToMarkerFails_ifOldHigherMarkerGiven) {
    m_allocator.alloc(INT_SIZE);
    m_allocator.alloc(INT_SIZE);
    Marker m = m_allocator.getMarker();
    m_allocator.clear();

    ASSERT_DEATH(m_allocator.freeToMarker(m), "");
}
