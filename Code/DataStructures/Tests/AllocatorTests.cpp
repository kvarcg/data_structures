// global includes    //////////////////////////////
#include "Global.h"

#include "DataStructureTests.h"
#include "Allocators.h"

namespace DS {

    template <typename Alloc1, typename Alloc2, typename T, std::size_t N>
    void compareAllocators() {
        Alloc1 al1;
        Alloc1 al2;

        T* v1 = static_cast<T*>(al1.allocate(N));
        T* v2 = static_cast<T*>(al2.allocate(N));
        for (std::size_t i = 0; i < N; ++i) {
            al1.construct(&v1[i], i);
            al2.construct(&v2[i], i);
        }

        for (std::size_t i = 0; i < N; ++i) {
            T* v1_element = static_cast<T*>(&v1[i]);
            T* v2_element = static_cast<T*>(&v2[i]);
            // same data
            X_ASSERT_IF_FALSE(*v1_element == *v2_element);
            // different pointers
            X_ASSERT_IF_FALSE(v1_element != v2_element);
        }

        for (std::size_t i = 0; i < N; ++i) {
            al1.destroy(&v1[i]);
            al2.destroy(&v2[i]);
        }
        al1.deallocate(v1, N);
        al2.deallocate(v2, N);
    }

    template <typename Alloc, typename T, std::size_t N>
    void testAllocator() {
        Alloc al;

        T* v = static_cast<T*>(al.allocate(N));
        for (std::size_t i = 0; i < N; ++i) {
            al.construct(&v[i], i);
        }
        for (std::size_t i = 0; i < N; ++i) {
            al.destroy(&v[i]);
        }
        al.deallocate(v, N);
    }

    namespace TESTS {
        void testAllocators() {
            X_DEBUG_COMMENT("Started %s", __func__);
            constexpr int element_size = 100;
            testAllocator<std::allocator<GenericTestObject>, GenericTestObject, element_size>();
            testAllocator<DS::AllocatorSimple<GenericTestObject>, GenericTestObject, element_size>();
            testAllocator<DS::AllocatorDefault<GenericTestObject>, GenericTestObject, element_size>();
            compareAllocators<std::allocator<GenericTestObject>, DS::AllocatorSimple<GenericTestObject>, GenericTestObject, element_size>();
            compareAllocators<std::allocator<GenericTestObject>, DS::AllocatorDefault<GenericTestObject>, GenericTestObject, element_size>();
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }  // namespace TESTS
}  // namespace DS

int main() {
    DS::TESTS::testAllocators();
    return 0;
}
