// global includes    //////////////////////////////
#include "Global.h"

#include "DataStructureTests.h"
#include "Vector.h"
#include <vector>

namespace DS {

    void testEqualVectors(const std::vector<GenericTestObject>& stdvector, const Vector<GenericTestObject>& dsvector) {

        X_ASSERT_IF_FALSE(stdvector.size() == dsvector.size());
        for (size_t i = 0; i < stdvector.size(); ++i) {
            X_ASSERT_IF_FALSE(stdvector[i] == dsvector[i]);
        }
        dsvector.print();
    }

    template <typename T>
    void constructTestVector(T& vec, size_t num_elements) {
        vec = T(num_elements);
        // test element access
        for (size_t i = 0; i < num_elements; ++i) {
            vec[i] = GenericTestObject(i);
        }
    }

    void testVectorModifiers(std::vector<GenericTestObject> stdvector, Vector<GenericTestObject> dsvector, size_t num_elements) {

        // test push_back
        for (size_t i = 0; i < num_elements; ++i) {
            dsvector.push_back(GenericTestObject(i));
            stdvector.push_back(GenericTestObject(i));
            testEqualVectors(stdvector, dsvector);
        }

        // test pop_back
        for (size_t i = 0; i < num_elements; ++i) {
            dsvector.pop_back();
            stdvector.pop_back();
            testEqualVectors(stdvector, dsvector);
        }

        // test insert
        dsvector.clear();
        stdvector.clear();
        constructTestVector<Vector<GenericTestObject>>(dsvector, num_elements);
        constructTestVector<std::vector<GenericTestObject>>(stdvector, num_elements);
        GenericTestObject vt(120);
        dsvector.insert(dsvector.cbegin() + 1, vt);
        stdvector.insert(stdvector.cbegin() + 1, vt);
        testEqualVectors(stdvector, dsvector);
        vt.val = 240;
        dsvector.insert(dsvector.cbegin() + 3, vt);
        stdvector.insert(stdvector.cbegin() + 3, vt);
        testEqualVectors(stdvector, dsvector);
        vt.val = 360;
        dsvector.insert(dsvector.cbegin() + 5, 6, vt);
        stdvector.insert(stdvector.cbegin() + 5, 6, vt);
        testEqualVectors(stdvector, dsvector);

        // test erase
        dsvector.erase(dsvector.cbegin() + 5, dsvector.cbegin() + 11);
        stdvector.erase(stdvector.cbegin() + 5, stdvector.cbegin() + 11);
        testEqualVectors(stdvector, dsvector);
        dsvector.erase(dsvector.cbegin() + 3);
        stdvector.erase(stdvector.cbegin() + 3);
        testEqualVectors(stdvector, dsvector);
        dsvector.erase(dsvector.cbegin() + 1);
        stdvector.erase(stdvector.cbegin() + 1);
        testEqualVectors(stdvector, dsvector);

        // test reserve
        dsvector.reserve(60);
        stdvector.reserve(60);
        testEqualVectors(stdvector, dsvector);
        X_ASSERT_IF_FALSE(stdvector.capacity() == dsvector.capacity());

        // test shrink to fit
        dsvector.shrink_to_fit();
        stdvector.shrink_to_fit();
        testEqualVectors(stdvector, dsvector);
        X_ASSERT_IF_FALSE(stdvector.capacity() == dsvector.capacity());

        // test resize
        dsvector.resize(20);
        stdvector.resize(20);
        testEqualVectors(stdvector, dsvector);
        X_ASSERT_IF_FALSE(stdvector.capacity() == dsvector.capacity());
        dsvector.resize(5);
        stdvector.resize(5);
        testEqualVectors(stdvector, dsvector);
        X_ASSERT_IF_FALSE(stdvector.capacity() == dsvector.capacity());
        dsvector.resize(8, GenericTestObject(2));
        stdvector.resize(8, GenericTestObject(2));
        testEqualVectors(stdvector, dsvector);
        X_ASSERT_IF_FALSE(stdvector.capacity() == dsvector.capacity());

        // test assign
        dsvector.clear();
        stdvector.clear();
        dsvector.assign(5, GenericTestObject(4));
        stdvector.assign(5, GenericTestObject(4));
        testEqualVectors(stdvector, dsvector);
        dsvector.assign(2, GenericTestObject(2));
        stdvector.assign(2, GenericTestObject(2));
        testEqualVectors(stdvector, dsvector);
        dsvector.assign(28, GenericTestObject(6));
        stdvector.assign(28, GenericTestObject(6));
        testEqualVectors(stdvector, dsvector);
        dsvector.assign(2, GenericTestObject(8));
        stdvector.assign(2, GenericTestObject(8));
        testEqualVectors(stdvector, dsvector);
    }

    template <typename T>
    void testVectorBase(size_t num_elements) {
        // test vector size
        X_ASSERT_IF_FALSE(std::is_default_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_assignable<T>() == true);
        //X_ASSERT_IF_FALSE(std::is_move_constructible<T>() == false);
        //X_ASSERT_IF_FALSE(std::is_move_assignable<T>() == false);

        T dsvector_empty;
        X_ASSERT_IF_FALSE(dsvector_empty.empty() == true);

        T dsvector;
        constructTestVector<T>(dsvector, num_elements);
        X_ASSERT_IF_FALSE(dsvector.empty() == false);
        X_ASSERT_IF_FALSE(dsvector.size() == num_elements);
        X_ASSERT_IF_FALSE(dsvector.capacity() >= num_elements);

        // test copy
        T dsvector_copy(dsvector);
        dsvector.clear();
        constructTestVector(dsvector, num_elements);
        X_ASSERT_IF_FALSE(dsvector.empty() == dsvector_copy.empty());
        X_ASSERT_IF_FALSE(dsvector.size() == dsvector_copy.size());
        X_ASSERT_IF_FALSE(dsvector.capacity() == dsvector_copy.capacity());
        for (size_t i = 0; i < num_elements; ++i) {
            X_ASSERT_IF_FALSE(dsvector[i].val == dsvector_copy[i].val);
        }

        // test assignment
        T dsvector_ass(2);
        dsvector_ass = dsvector;
        dsvector.clear();
        constructTestVector(dsvector, num_elements);
        X_ASSERT_IF_FALSE(dsvector.empty() == dsvector_ass.empty());
        X_ASSERT_IF_FALSE(dsvector.size() == dsvector_ass.size());
        X_ASSERT_IF_FALSE(dsvector.capacity() == dsvector_ass.capacity());
        for (size_t i = 0; i < num_elements; ++i) {
            X_ASSERT_IF_FALSE(dsvector[i].val == dsvector_ass[i].val);
        }
    }

    template <typename T>
    void testVectorElementAccess(size_t num_elements) {
        T dsvector;
        constructTestVector<T>(dsvector, num_elements);

        X_ASSERT_IF_FALSE(GenericTestObject(0).val == dsvector.front().val);
        X_ASSERT_IF_FALSE(GenericTestObject(num_elements - 1).val == dsvector.back().val);
        for (size_t i = 0; i < num_elements; ++i) {
            GenericTestObject t(i);
            X_ASSERT_IF_FALSE(t.val == dsvector[i].val);
            X_ASSERT_IF_FALSE(t.val == dsvector.at(i).val);
            X_ASSERT_IF_FALSE(t.val == (dsvector.data() + i)->val);
        }
    }

    template <typename T>
    void testVectorIterators(size_t num_elements) {
        T dsvector;
        constructTestVector<T>(dsvector, num_elements);

        // test iterators
        int index = 0;
        for (auto i = dsvector.begin(); i != dsvector.end(); ++i) {
            X_ASSERT_IF_FALSE((*i).val == index);
            X_ASSERT_IF_FALSE(i->val == index);
            ++index;
        }

        index = 0;
        for (auto i = dsvector.cbegin(); i != dsvector.cend(); ++i) {
            X_ASSERT_IF_FALSE((*i).val == index);
            X_ASSERT_IF_FALSE(i->val == index);
            ++index;
        }

        X_ASSERT_IF_FALSE(GenericTestObject(0).val == dsvector.cbegin()->val);
        X_ASSERT_IF_FALSE(GenericTestObject(0).val == dsvector.begin()->val);
        auto f = dsvector.cend();
        X_ASSERT_IF_FALSE(GenericTestObject(num_elements - 1).val == (--f)->val);
        X_ASSERT_IF_FALSE(GenericTestObject(num_elements - 1).val == (f)->val);
    }

    namespace TESTS {
        void testVectors() {
            X_DEBUG_COMMENT("Started %s", __func__);
            constexpr size_t num_elements = 10;
            testVectorBase<std::vector<GenericTestObject>>(num_elements);
            testVectorElementAccess<std::vector<GenericTestObject>>(num_elements);
            testVectorIterators<std::vector<GenericTestObject>>(num_elements);
            testVectorBase<Vector<GenericTestObject>>(num_elements);
            testVectorElementAccess<Vector<GenericTestObject>>(num_elements);
            testVectorIterators<Vector<GenericTestObject>>(num_elements);
            std::vector<GenericTestObject>stdvector;
            Vector<GenericTestObject> dsvector;
            testVectorModifiers(stdvector, dsvector, num_elements);
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}

int main() {
    DS::TESTS::testVectors();
    return 0;
}
