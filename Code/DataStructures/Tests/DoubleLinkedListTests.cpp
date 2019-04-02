// global includes    //////////////////////////////
#include "Global.h"

#include "DataStructureTests.h"
#include "DoubleLinkedList.h"
#include <vector>
#include <string>
#include <algorithm>

namespace DS {

    void compareElements(const std::vector<GenericTestObject>& vector, const LinkedListDouble<GenericTestObject>& list) {
        const auto* node = list.head();
        for (size_t index = 0; index < vector.size(); ++index) {
            X_ASSERT_IF_FALSE(vector[index].val == node->data()->val);
            node = node->next();
        }

        list.print();
    }

    void testBase(int32_t num_elements) {
        // test empty list
        LinkedListDouble<GenericTestObject> list;
        std::vector<GenericTestObject> vector;
        compareElements(vector, list);


        //test list
        for (int32_t i = 0; i < num_elements; ++i) {
            list.push_front(GenericTestObject(num_elements - i - 1));
            vector.push_back(GenericTestObject(i));
        }
        compareElements(vector, list);

        // test copy
        LinkedListDouble<GenericTestObject> list_clone(list);
        list.destroy();
        compareElements(vector, list_clone);

        // test assignment
        LinkedListDouble<GenericTestObject> list_clone2;
        list_clone2.push_front(GenericTestObject(2));
        list_clone2.push_front(GenericTestObject(1));
        list_clone2 = list_clone;
        list_clone.destroy();
        compareElements(vector, list_clone2);
    }

    void testPushFront(int32_t num_elements) {
        LinkedListDouble<GenericTestObject> list;
        std::vector<GenericTestObject> vector(num_elements);
        for (int32_t i = 0; i < num_elements; ++i) {
            list.push_front(GenericTestObject(num_elements - i - 1));
            vector[i] = (GenericTestObject(i));
        }
        compareElements(vector, list);
    }

    void testPushBack(int32_t num_elements) {
        LinkedListDouble<GenericTestObject> list;
        std::vector<GenericTestObject> vector(num_elements);
        for (int32_t i = 0; i < num_elements; ++i) {
            list.push_back(GenericTestObject(i));
            vector[i] = (GenericTestObject(i));
        }
        compareElements(vector, list);
    }

    void testInsertAfter(int32_t num_elements) {
        LinkedListDouble<GenericTestObject> list;
        auto* node = list.head();
        for (int32_t i = 0; i < num_elements; ++i) {
            node = list.insert_after(node, GenericTestObject(i));
        }
        std::vector<GenericTestObject> vector(num_elements);
        for (int32_t i = 0; i < num_elements; ++i) {
            vector[i] = (GenericTestObject(i));
        }
        compareElements(vector, list);
    }

    void testOperations(int32_t num_elements) {

        // test random operations
        {
            LinkedListDouble<GenericTestObject> list;
            list.push_front(GenericTestObject(2));
            list.push_front(GenericTestObject(1));
            compareElements({ 1, 2 }, list);
            auto* node3 = list.push_back(GenericTestObject(3));
            list.push_back(GenericTestObject(5));
            auto* node6 = list.push_back(GenericTestObject(6));
            list.push_back(GenericTestObject(8));
            list.push_back(GenericTestObject(9));
            compareElements({ 1, 2, 3, 5, 6, 8, 9 }, list);
            list.insert_after(node3, GenericTestObject(4));
            compareElements({ 1, 2, 3, 4, 5, 6, 8, 9 }, list);
            list.insert_after(node6, GenericTestObject(7));
            compareElements({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, list);
        }

        // test reverse
        {
            LinkedListDouble<GenericTestObject> list;
             LinkedListDouble<GenericTestObject> list_reversed = list.reverse();
            std::vector<GenericTestObject> vector;
            compareElements(vector, list_reversed);

            for (int32_t i = 0; i < num_elements; ++i) {
                list.push_front(GenericTestObject(i));
                vector.push_back(i);
            }
            list_reversed = list.reverse();
            compareElements(vector, list_reversed);
        }

        {
            LinkedListDouble<GenericTestObject> list;
            std::vector<GenericTestObject> vector;

            // pop front
            int32_t test_size = num_elements;
            for (int32_t i = 0; i < test_size; ++i) {
                list.push_front(GenericTestObject(test_size - i - 1));
                vector.push_back(GenericTestObject(i));
            }
            for (int32_t i = 0; i < test_size; ++i) {
                list.pop_front();
                vector.erase(vector.begin());
                compareElements(vector, list);
            }

            // pop back
            for (int32_t i = 0; i < test_size; ++i) {
                list.push_front(GenericTestObject(test_size - i - 1));
                vector.push_back(GenericTestObject(i));
            }
            for (int32_t i = 0; i < test_size; ++i) {
                list.pop_back();
                vector.pop_back();
                compareElements(vector, list);
            }

            // erase
            for (int32_t i = 0; i < test_size; ++i) {
                list.push_front(GenericTestObject(test_size - i - 1));
                vector.push_back(GenericTestObject(i));
            }

            auto* node = list.find(test_size / 2);
            list.print();
            list.erase(node);
            list.print();
            auto veciter = std::find(vector.begin(), vector.end(), test_size / 2);
            veciter = vector.erase(veciter);
            compareElements(vector, list);
            list.insert_after(list.find((test_size / 2) - 1), GenericTestObject(test_size / 2));
            vector.insert(veciter--, GenericTestObject(test_size / 2));
            for (int32_t i = test_size - 1; i >= 0; --i) {
                node = list.find(i);
                list.erase(node);
                veciter = std::find(vector.begin(), vector.end(), i);
                vector.erase(veciter);
                compareElements(vector, list);
            }
        }
    }

    namespace TESTS {
        void testLinkedLists() {
            X_DEBUG_COMMENT("Started %s", __func__);
            constexpr int32_t num_elements = 100;
            testBase(num_elements);
            testPushFront(num_elements);
            testPushBack(num_elements);
            testOperations(num_elements);
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}

int main() {
    DS::TESTS::testLinkedLists();
    return 0;
}


