// global includes    //////////////////////////////
#include "Global.h"

#include "DataStructureTests.h"
#include "Array.h"
#include <array>

namespace DS {

    template <std::size_t N>
    void testEqualArrays(const std::array<GenericTestObject, N>& stdarray, const Array<GenericTestObject, N>& dsarray) {

        X_ASSERT_IF_FALSE(stdarray.size() == dsarray.size());
        for (size_t i = 0; i < stdarray.size(); ++i) {
            X_ASSERT_IF_FALSE(stdarray[i] == dsarray[i]);
        }
        dsarray.print();
    }

    template <typename T>
    void constructTestArray(T& vec) {
        // test element access
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i] = GenericTestObject(static_cast<int64_t>(i));
        }
    }

    template <std::size_t N>
    void testArrayOperations(std::array<GenericTestObject, N> stdarray, Array<GenericTestObject, N> dsarray) {

        // test operations
        dsarray.fill(GenericTestObject(-5));
        stdarray.fill(GenericTestObject(-5));
        testEqualArrays<N>(stdarray, dsarray);

        // test element access
        for (size_t i = 0; i < dsarray.size(); ++i) {
            dsarray[i] = GenericTestObject(static_cast<int64_t>(i));
            stdarray[i] = GenericTestObject(static_cast<int64_t>(i));
        }

        testEqualArrays<N>(stdarray, dsarray);
        X_ASSERT_IF_FALSE(DS::get<0>(dsarray).val == 0);
        X_ASSERT_IF_FALSE(DS::get<2>(dsarray).val == 2);
    }

    template <typename T>
    void testArrayBase(std::size_t num_elements) {
        // test array size
        X_ASSERT_IF_FALSE(std::is_default_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_assignable<T>() == true);
        //X_ASSERT_IF_FALSE(std::is_move_constructible<T>() == false);
        //X_ASSERT_IF_FALSE(std::is_move_assignable<T>() == false);

        // test array size
        T dsarray;
        X_ASSERT_IF_FALSE(dsarray.size() == num_elements);
        X_ASSERT_IF_FALSE(dsarray.empty() == false);

        // test copy
        constructTestArray(dsarray);
        T dsarray_copy(dsarray);
        X_ASSERT_IF_FALSE(dsarray.empty() == dsarray_copy.empty());
        X_ASSERT_IF_FALSE(dsarray.size() == dsarray_copy.size());
        for (size_t i = 0; i < num_elements; ++i) {
            X_ASSERT_IF_FALSE(dsarray[i].val == dsarray_copy[i].val);
        }

        // test assignment
        T dsarray_ass;
        dsarray_ass = dsarray;
        X_ASSERT_IF_FALSE(dsarray.empty() == dsarray_ass.empty());
        X_ASSERT_IF_FALSE(dsarray.size() == dsarray_ass.size());
        for (size_t i = 0; i < num_elements; ++i) {
            X_ASSERT_IF_FALSE(dsarray[i].val == dsarray_ass[i].val);
        }
    }

    template <typename T>
    void testArrayElementAccess(size_t num_elements) {
        T dsarray;
        constructTestArray<T>(dsarray);

        X_ASSERT_IF_FALSE(GenericTestObject(0).val == dsarray.front().val);
        X_ASSERT_IF_FALSE(GenericTestObject(dsarray.size() - 1).val == dsarray.back().val);
        for (uint32_t i = 0; i < num_elements; ++i) {
            GenericTestObject t(i);
            X_ASSERT_IF_FALSE(t.val == dsarray[i].val);
            X_ASSERT_IF_FALSE(t.val == dsarray.at(i).val);
            X_ASSERT_IF_FALSE(t.val == (dsarray.data() + i)->val);
        }
    }

    template <typename T>
    void testArrayIterators(size_t num_elements) {
        T dsarray;
        constructTestArray<T>(dsarray);

        // test iterators
        int index = 0;
        for (auto i = dsarray.begin(); i < dsarray.end(); ++i) {
            X_ASSERT_IF_FALSE((*i).val == index);
            X_ASSERT_IF_FALSE(i->val == index);
            ++index;
        }

        index = 0;
        for (auto i = dsarray.cbegin(); i < dsarray.cend(); ++i) {
            X_ASSERT_IF_FALSE((*i).val == index);
            X_ASSERT_IF_FALSE(i->val == index);
            ++index;
        }

        X_ASSERT_IF_FALSE(GenericTestObject(0).val == dsarray.cbegin()->val);
        X_ASSERT_IF_FALSE(GenericTestObject(0).val == dsarray.begin()->val);
        auto f = dsarray.cend();
        int64_t forced_value = static_cast<int64_t>(num_elements - 1);
        X_ASSERT_IF_FALSE(GenericTestObject(forced_value).val == (--f)->val);
        X_ASSERT_IF_FALSE(GenericTestObject(forced_value).val == (f)->val);
    }

    namespace TESTS {
        void testArrays() {
            X_DEBUG_COMMENT("Started %s", __func__);
            constexpr size_t num_elements = 10;
            testArrayBase<std::array<GenericTestObject, num_elements>>(num_elements);
            testArrayElementAccess<std::array<GenericTestObject, num_elements>>(num_elements);
            testArrayIterators<std::array<GenericTestObject, num_elements>>(num_elements);
            testArrayBase<Array<GenericTestObject, num_elements>>(num_elements);
            testArrayElementAccess<Array<GenericTestObject, num_elements>>(num_elements);
            testArrayIterators<Array<GenericTestObject, num_elements>>(num_elements);
            std::array<GenericTestObject, num_elements>stdarray;
            Array<GenericTestObject, num_elements> dsarray;
            testArrayOperations<num_elements>(stdarray, dsarray);
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}  // namespace DS

int main() {
    DS::TESTS::testArrays();
    return 0;
}
