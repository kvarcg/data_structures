// global includes    //////////////////////////////
#include "Global.h"

#include "Queue.h"
#include "DataStructureTests.h"
#include <queue>

namespace DS {

    void compareElements(std::queue<GenericTestObject> stdqueue, Queue<GenericTestObject> dsqueue) {
        while (!stdqueue.empty()) {
            dsqueue.print();
            X_ASSERT_IF_FALSE(stdqueue.front().val == dsqueue.front()->data()->val);
            X_ASSERT_IF_FALSE(stdqueue.back().val == dsqueue.back()->data()->val);
            stdqueue.pop();
            dsqueue.pop();
        }
        dsqueue.print();
    }

    template <typename T>
    void constructTestQueue(T& queue, size_t num_elements) {
        // test element access
        for (size_t i = 0; i < num_elements; ++i) {
            queue.push(GenericTestObject(static_cast<int64_t>(i)));
        }
    }

    template <typename T>
    void testQueueBase() {
        X_ASSERT_IF_FALSE(std::is_default_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_assignable<T>() == true);
        //X_ASSERT_IF_FALSE(std::is_move_constructible<T>() == false);
        //X_ASSERT_IF_FALSE(std::is_move_assignable<T>() == false);
    }

    void testEmptyQueue(size_t num_elements) {
        {
            std::queue<GenericTestObject> stdqueue;
            Queue<GenericTestObject> dsqueue;
            X_ASSERT_IF_FALSE(stdqueue.empty() == true);
            X_ASSERT_IF_FALSE(dsqueue.empty() == true);
        }
        {
            std::queue<GenericTestObject> stdqueue;
            Queue<GenericTestObject> dsqueue;
            constructTestQueue(stdqueue, num_elements);
            constructTestQueue(dsqueue, num_elements);

            // test copy
            Queue<GenericTestObject> dsqueue_copy(dsqueue);
            compareElements(stdqueue, dsqueue_copy);

            // test assignment
            Queue<GenericTestObject> dsqueue_ass;
            dsqueue_ass = dsqueue;
            compareElements(stdqueue, dsqueue_copy);
        }
    }

    void testQueueOperations(size_t num_elements) {
        std::queue<GenericTestObject> stdqueue;
        Queue<GenericTestObject> dsqueue;
        for (size_t i = 0; i < num_elements; ++i) {
            stdqueue.push(GenericTestObject(i));
            dsqueue.push(GenericTestObject(i));
        }
        compareElements(stdqueue, dsqueue);
        stdqueue.pop();
        dsqueue.pop();
        stdqueue.pop();
        dsqueue.pop();
        for (size_t i = 0; i < num_elements; ++i) {
            stdqueue.push(GenericTestObject(i));
            dsqueue.push(GenericTestObject(i));
        }
        compareElements(stdqueue, dsqueue);
    }

    namespace TESTS {
        void testQueues() {
            X_DEBUG_COMMENT("Started %s", __func__);
            constexpr size_t num_elements = 10;
            testQueueBase<Queue<GenericTestObject>>();
            testEmptyQueue(num_elements);
            testQueueOperations(num_elements);
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}


#include <vector>
int main() {
    DS::TESTS::testQueues();
    return 0;
}
