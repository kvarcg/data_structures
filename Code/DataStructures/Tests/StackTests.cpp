// global includes    //////////////////////////////
#include "Global.h"

#include "Stack.h"
#include "DataStructureTests.h"
#include <stack>

namespace DS {

    void compareElements(std::stack<GenericTestObject> stdstack, StackArray<GenericTestObject> dsstack) {
        X_ASSERT_IF_FALSE(stdstack.size() == dsstack.size());
        while (!stdstack.empty()) {
            dsstack.print();
            X_ASSERT_IF_FALSE(stdstack.top().val == dsstack.top()->val);
            stdstack.pop();
            dsstack.pop();
        }
        dsstack.print();
    }

    template <typename T>
    void constructTestStack(T& stack) {
        // test element access
        for (size_t i = 0; i < stack.size(); ++i) {
            stack.push(GenericTestObject(static_cast<int64_t>(i)));
        }
    }

    template <typename T>
    void testStackBase() {
        X_ASSERT_IF_FALSE(std::is_default_constructible<StackArray<GenericTestObject>>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_constructible<StackArray<GenericTestObject>>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_assignable<StackArray<GenericTestObject>>() == true);
        //X_ASSERT_IF_FALSE(std::is_move_constructible<StackArray<GenericTestObject>>() == false);
        //X_ASSERT_IF_FALSE(std::is_move_assignable<StackArray<GenericTestObject>>() == false);
    }

    void testEmptyStack(size_t num_elements) {
        {
            std::stack<GenericTestObject> stdstack;
            StackArray<GenericTestObject> dsstack;
            X_ASSERT_IF_FALSE(stdstack.empty() == true);
            X_ASSERT_IF_FALSE(dsstack.empty() == true);
        }
        {
            StackArray<GenericTestObject> dsstack(num_elements);
            X_ASSERT_IF_FALSE(dsstack.empty() == true);
            X_ASSERT_IF_FALSE(dsstack.capacity() == num_elements);
        }
        {
            StackArray<GenericTestObject> dsstack;
            dsstack.reserve(num_elements);
            X_ASSERT_IF_FALSE(dsstack.empty() == true);
            X_ASSERT_IF_FALSE(dsstack.capacity() == num_elements);
        }

        {
            std::stack<GenericTestObject> stdstack;
            StackArray<GenericTestObject> dsstack;
            constructTestStack<std::stack<GenericTestObject>>(stdstack);
            constructTestStack<StackArray<GenericTestObject>>(dsstack);

            // test copy
            StackArray<GenericTestObject> dsstack_copy(dsstack);
            compareElements(stdstack, dsstack_copy);

            // test assignment
            StackArray<GenericTestObject> dsstack_ass(2);
            dsstack_ass = dsstack;
            compareElements(stdstack, dsstack_copy);
        }
    }

    void testStackOperations(size_t num_elements) {
        std::stack<GenericTestObject> stdstack;
        StackArray<GenericTestObject> dsstack;
        dsstack.reserve(num_elements / 2);
        compareElements(stdstack, dsstack);
        for (size_t i = 0; i < num_elements; ++i) {
            stdstack.push(GenericTestObject(i));
            dsstack.push(GenericTestObject(i));
        }
        compareElements(stdstack, dsstack);
    }

    namespace TESTS {
        void testStacks() {
            X_DEBUG_COMMENT("Started %s", __func__);
            constexpr size_t num_elements = 10;
            testStackBase<StackArray<GenericTestObject>>();
            testEmptyStack(num_elements);
            testStackOperations(num_elements);
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}

int main() {
    DS::TESTS::testStacks();
    return 0;
}
