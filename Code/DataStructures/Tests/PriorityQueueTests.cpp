// global includes    //////////////////////////////
#include "Global.h"

#include "PriorityQueue.h"
#include "DataStructureTests.h"
#include <queue>

namespace DS {
    using stdTypeMin = std::priority_queue<GenericTestObject, std::vector<GenericTestObject>, std::greater<GenericTestObject>>;
    using stdTypeMax = std::priority_queue<GenericTestObject, std::vector<GenericTestObject>, std::less<GenericTestObject>>;
    using DSTypeMin = PriorityQueue<GenericTestObject, true>;
    using DSTypeMax = PriorityQueue<GenericTestObject, false>;

    template <typename stdType, typename dsType>
    void testEqualPriorityQueues(stdType stdpriority_queue, dsType dspriority_queue) {
        X_ASSERT_IF_FALSE(stdpriority_queue.size() == dspriority_queue.size());
        while (!stdpriority_queue.empty()) {
            dspriority_queue.print();
            X_ASSERT_IF_FALSE(stdpriority_queue.top().val == dspriority_queue.top()->val);
            stdpriority_queue.pop();
            dspriority_queue.pop();
        }
        dspriority_queue.print();
    }

    template <typename T>
    void constructTestPriorityQueue(T& priority_queue, size_t num_elements) {
        // test element access
        for (size_t i = 0; i < num_elements; ++i) {
            priority_queue.push(GenericTestObject(static_cast<int64_t>(i)));
        }
    }

    template <typename stdType, typename dsType, typename objT>
    void testPriorityQueueModifiers(stdType stdpriority_queue, dsType dspriority_queue, size_t num_elements) {

        // test push
        for (size_t i = 0; i < num_elements; ++i) {
            dspriority_queue.push(objT(static_cast<int64_t>(i)));
            stdpriority_queue.push(objT(static_cast<int64_t>(i)));
            testEqualPriorityQueues(stdpriority_queue, dspriority_queue);
        }

        // test pop
        for (size_t i = 0; i < num_elements; ++i) {
            dspriority_queue.pop();
            stdpriority_queue.pop();
            testEqualPriorityQueues(stdpriority_queue, dspriority_queue);
        }

        // test clear
        dspriority_queue.clear();
        X_ASSERT_IF_FALSE(dspriority_queue.size() == 0);
        X_ASSERT_IF_FALSE(dspriority_queue.empty() == true);

        // test reserve
        dspriority_queue.reserve(60);
        X_ASSERT_IF_FALSE(dspriority_queue.capacity() == 60);

        // test shrink to fit
        dspriority_queue.shrink_to_fit();
        X_ASSERT_IF_FALSE(dspriority_queue.capacity() == dspriority_queue.size());
    }

    template <typename T>
    void testPriorityQueueBase() {
        // test priority_queue size
        X_ASSERT_IF_FALSE(std::is_default_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_assignable<T>() == true);
        //X_ASSERT_IF_FALSE(std::is_move_constructible<T>() == false);
        //X_ASSERT_IF_FALSE(std::is_move_assignable<T>() == false);
    }

    template <typename stdType, typename dsType>
    void testBasicPriorityQueue(size_t num_elements) {
        {
            stdType stdpriority_queue;
            dsType dspriority_queue;
            X_ASSERT_IF_FALSE(stdpriority_queue.empty() == true);
            X_ASSERT_IF_FALSE(dspriority_queue.empty() == true);
        }
        {
            dsType dspriority_queue(num_elements);
            X_ASSERT_IF_FALSE(dspriority_queue.empty() == true);
            X_ASSERT_IF_FALSE(dspriority_queue.capacity() == num_elements);
        }
        {
            dsType dspriority_queue;
            dspriority_queue.reserve(num_elements);
            X_ASSERT_IF_FALSE(dspriority_queue.empty() == true);
            X_ASSERT_IF_FALSE(dspriority_queue.capacity() == num_elements);
        }
        {
            stdType stdpriority_queue;
            dsType dspriority_queue;
            constructTestPriorityQueue<stdType>(stdpriority_queue, num_elements);
            constructTestPriorityQueue<dsType>(dspriority_queue, num_elements);
            testEqualPriorityQueues(stdpriority_queue, dspriority_queue);
            dspriority_queue.validateHeap();

            // test copy
            dsType dspriority_queue_copy(dspriority_queue);
            testEqualPriorityQueues(stdpriority_queue, dspriority_queue_copy);
            dspriority_queue_copy.validateHeap();

            // test assignment
            dsType dspriority_queue_ass(2);
            dspriority_queue_ass = dspriority_queue;
            testEqualPriorityQueues(stdpriority_queue, dspriority_queue_copy);
            dspriority_queue_ass.validateHeap();
        }
    }

    namespace TESTS {
        void testPriorityQueues() {
            X_DEBUG_COMMENT("Started %s", __func__);
            constexpr size_t num_elements = 10;
            testPriorityQueueBase<DSTypeMin>();
            testPriorityQueueBase<DSTypeMax>();
            testBasicPriorityQueue<stdTypeMin, DSTypeMin>(num_elements);
            testBasicPriorityQueue<stdTypeMax, DSTypeMax>(num_elements);

            stdTypeMin stdpriority_queue_min;
            DSTypeMin dspriority_queue_min(num_elements);
            testPriorityQueueModifiers<stdTypeMin, DSTypeMin, GenericTestObject>(stdpriority_queue_min, dspriority_queue_min, num_elements);

            stdTypeMax stdpriority_queue_max;
            DSTypeMax dspriority_queue_max(num_elements);
            testPriorityQueueModifiers<stdTypeMax, DSTypeMax, GenericTestObject>(stdpriority_queue_max, dspriority_queue_max, num_elements);
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}

int main() {
    DS::TESTS::testPriorityQueues();
    return 0;
}
