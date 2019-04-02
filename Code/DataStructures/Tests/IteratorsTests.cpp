// global includes    //////////////////////////////
#include "Global.h"

#include "DataStructureTests.h"
#include "Iterators.h"
#include <array>

/*
#include<list>

template <typename T>
class MyAlloc {

};

namespace T1 {
    // create Widget
    class Wine {};

    // create a synonym for linked list using MyAlloc
    template <typename T>
    struct MyAllocList {
        typedef std::list<T, MyAlloc<T>> customListAlloc;
    };
    MyAllocList<Wine>::customListAlloc lw2;

    // use customListAlloc inside a class T
    template <typename T>
    class Widget {
        typename MyAllocList<T>::customListAlloc m_list;
        // alternatively
        std::list<T, MyAlloc<T>> m_list2;
    };
    Widget<Wine> ow;
}

namespace T3 {
    // create Widget
    class Object {};
    class Wine {};

    // create a synonym for linked list using MyAlloc
    template <typename T>
    struct MyAllocList {
        typedef std::list<T, MyAlloc<T>> type;
    };

    template<> // MyAllocList specialization
    class MyAllocList<Wine> { // for when T is Wine
    public:
        typedef std::list<Wine, MyAlloc<Wine>> type;
        enum class WineType { White, Red, Rose }; // "enum class"
        WineType type2; // in this class, type is a data member!
    };

    // use customListAlloc inside a class T
    template <typename T>
    class Widget {
        typename MyAllocList<T>::type m_list;
        // alternatively
        std::list<T, MyAlloc<T>> m_list2;
    };

    MyAllocList<Object>::type lw2; // or
    std::list<Object, MyAlloc<Object>> mlw2;

    Widget<Wine> ow;
    //MyAllocList<Wine>::customListAlloc lw2;

}


namespace T2 {
    class Object {};
    class Wine {};

    // create a synonym for linked list using MyAlloc
    template <typename T>
    using MyAllocList = std::list<T, MyAlloc<T>>;

    // use MyALlocList inside a class T
    template <typename T>
    class Widget {
        MyAllocList<T> m_list;
        // alternatively
        std::list<T, MyAlloc<T>> m_list2;
    };

    MyAllocList<Wine> lw;
    Widget<Wine> ow;
}
*/

template<class It, class T>
void testBaseIterator(T* test_data, const int array_size) {
    X_ASSERT_IF_FALSE(std::is_copy_constructible<It>::value == true);
    X_ASSERT_IF_FALSE(std::is_copy_assignable<It>::value == true);
    It iterator(&test_data[0]);
    // increment prefix and dereference
    It iterator2 = iterator;
    for (int i = 0; i < array_size; ++i) {
        X_ASSERT_IF_FALSE((*iterator2).val == (*iterator).val);
        iterator2 = ++iterator;
    }
}

template<class It, class T>
void testInputIterator(T* test_data, const int array_size) {
    testBaseIterator<It, T>(test_data, array_size);
    It iterator(&test_data[0]);
    // increment postfix
    iterator = It(&test_data[0]);
    for (int i = 0; i < array_size - 1; ++i) {
        It iterator2 = iterator++;
        X_ASSERT_IF_FALSE((*iterator2).val + 1 == (*iterator).val);
    }
    // ->
    for (int i = 0; i < array_size; ++i) {
        iterator = It(&test_data[i]);
        It iterator2 = It(&test_data[i]);
        X_ASSERT_IF_FALSE((*iterator2).val == iterator->val);
    }
    // equality
    for (int i = 0; i < array_size; ++i) {
        iterator = It(&test_data[i]);
        It iterator2 = It(&test_data[i]);
        X_ASSERT_IF_FALSE((*iterator2).val == (*iterator).val);
    }
    // inequality
    for (int i = 0; i < array_size; ++i) {
        iterator = It(&test_data[i]);
        int iterator2_index = array_size - i - 1;
        It iterator2 = It(&test_data[iterator2_index]);
        if (iterator2_index != i) {
            X_ASSERT_IF_FALSE((*iterator2).val != (*iterator).val);
        }
        else {
            X_ASSERT_IF_FALSE((*iterator2).val == (*iterator).val);
        }
    }
}

template<class It, class T>
void testOutputIterator(T* test_data, const int array_size) {
    testBaseIterator<It, T>(test_data, array_size);
    It iterator(&test_data[0]);
    // increment postfix
    for (int i = 0; i < array_size - 1; ++i) {
        It iterator2 = iterator++;
        X_ASSERT_IF_FALSE((*iterator2).val + 1 == (*iterator).val);
    }
}

template<class It, class T>
void testForwardIterator(T* test_data, const int array_size) {
    testInputIterator<It, T>(test_data, array_size);
    It iterator;
}

template<class It, class T>
void testBidirectionalIterator(T* test_data, const int array_size) {
    testForwardIterator<It, T>(test_data, array_size);
    It iterator(&test_data[0]);
    // decrement prefix and dereference
    for (int i = 0; i < array_size - 1; ++i) {
        ++iterator;
    }
    It iterator2 = iterator;
    for (int i = array_size - 1; i >= 0; --i) {
        X_ASSERT_IF_FALSE((*iterator2).val == (*iterator).val);
        if (i > 0) {
            iterator2 = --iterator;
        }
    }
    // decrement postfix
    iterator = It(&test_data[0]);
    for (int i = 0; i < array_size - 1; ++i) {
        ++iterator;
    }
    iterator2 = iterator;
    for (int i = array_size - 1; i >= 1; --i) {
        It iterator2 = iterator--;
        X_ASSERT_IF_FALSE((*iterator2).val - 1 == (*iterator).val);
    }
}

template<class It, class T>
void testRandomAccessIterator(T* test_data, const int array_size) {
    testBidirectionalIterator<It, T>(test_data, array_size);

    // test difference operators
    It iterator = It(&test_data[0]);
    It iterator2 = iterator + 8;
    ptrdiff_t diff = iterator2 - iterator;
    ptrdiff_t diff1 = sizeof(T);
    ptrdiff_t diff2 = reinterpret_cast<uintptr_t>(&test_data[0]);
    ptrdiff_t diff3 = reinterpret_cast<uintptr_t>(&test_data[0] + 8);
    ptrdiff_t diff4 = (diff3 - diff2) / diff1;
    X_ASSERT_IF_FALSE(diff == 8);
    X_ASSERT_IF_FALSE(diff == diff4);

    // relational operators
    for (int i = 0; i < array_size; ++i) {
        It iterator = It(&test_data[i]);
        for (int j = 0; j < array_size; ++j) {
            It iterator2 = It(&test_data[j]);
            if (i == j) {
                X_ASSERT_IF_FALSE((*iterator).val == (*iterator2).val);
                X_ASSERT_IF_FALSE((*iterator).val >= (*iterator2).val);
                X_ASSERT_IF_FALSE((*iterator).val <= (*iterator2).val);
            }
            if (i != j) {
                X_ASSERT_IF_FALSE((*iterator).val != (*iterator2).val);
            }
            if (i >= j) {
                X_ASSERT_IF_FALSE((*iterator).val >= (*iterator2).val);
            }
            if (i > j) {
                X_ASSERT_IF_FALSE((*iterator).val > (*iterator2).val);
            }
            if (i < j) {
                X_ASSERT_IF_FALSE((*iterator).val < (*iterator2).val);
            }
            if (i <= j) {
                X_ASSERT_IF_FALSE((*iterator).val <= (*iterator2).val);
            }
            // compares pointers values!
            if (i == j) {
                X_ASSERT_IF_FALSE(iterator == iterator2);
                X_ASSERT_IF_FALSE(iterator >= iterator2);
                X_ASSERT_IF_FALSE(iterator <= iterator2);
            }
            if (i != j) {
                X_ASSERT_IF_FALSE(iterator != iterator2);
            }
            if (i >= j) {
                X_ASSERT_IF_FALSE(iterator >= iterator2);
            }
            if (i > j) {
                X_ASSERT_IF_FALSE(iterator > iterator2);
            }
            if (i < j) {
                X_ASSERT_IF_FALSE(iterator < iterator2);
            }
            if (i <= j) {
                X_ASSERT_IF_FALSE(iterator <= iterator2);
            }
        }
    }
}

// check if iterators are:
// default constructible
// a const can be constructed and assigned from a mutable and vice versa
void checkisIteratorConstructible() {
    using namespace DS;

    X_ASSERT_IF_FALSE(std::is_default_constructible<BaseMutableIterator<GenericTestObject>>::value == false);
    X_ASSERT_IF_FALSE(std::is_default_constructible<InputMutableIterator<GenericTestObject>>::value == false);
    X_ASSERT_IF_FALSE(std::is_default_constructible<OutputMutableIterator<GenericTestObject>>::value == false);
    X_ASSERT_IF_FALSE(std::is_default_constructible<ForwardMutableIterator<GenericTestObject>>::value == true);
    X_ASSERT_IF_FALSE(std::is_default_constructible<BidirectionalMutableIterator<GenericTestObject>>::value == true);
    X_ASSERT_IF_FALSE(std::is_default_constructible<RandomAccessMutableIterator<GenericTestObject>>::value == true);

    X_ASSERT_IF_FALSE(std::is_default_constructible<BaseConstIterator<GenericTestObject>>::value == false);
    X_ASSERT_IF_FALSE(std::is_default_constructible<InputConstIterator<GenericTestObject>>::value == false);
    X_ASSERT_IF_FALSE(std::is_default_constructible<OutputConstIterator<GenericTestObject>>::value == false);
    X_ASSERT_IF_FALSE(std::is_default_constructible<ForwardConstIterator<GenericTestObject>>::value == true);
    X_ASSERT_IF_FALSE(std::is_default_constructible<BidirectionalConstIterator<GenericTestObject>>::value == true);
    X_ASSERT_IF_FALSE(std::is_default_constructible<RandomAccessConstIterator<GenericTestObject>>::value == true);

    X_ASSERT_IF_FALSE((std::is_constructible<BaseMutableIterator<GenericTestObject>, BaseConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_constructible<InputMutableIterator<GenericTestObject>, InputConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_constructible<OutputMutableIterator<GenericTestObject>, OutputConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_constructible<ForwardMutableIterator<GenericTestObject>, ForwardConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_constructible<BidirectionalMutableIterator<GenericTestObject>, BidirectionalConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_constructible<RandomAccessMutableIterator<GenericTestObject>, RandomAccessConstIterator<GenericTestObject>>::value == false));

    X_ASSERT_IF_FALSE((std::is_assignable<BaseMutableIterator<GenericTestObject>, BaseConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_assignable<InputMutableIterator<GenericTestObject>, InputConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_assignable<OutputMutableIterator<GenericTestObject>, OutputConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_assignable<ForwardMutableIterator<GenericTestObject>, ForwardConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_assignable<BidirectionalMutableIterator<GenericTestObject>, BidirectionalConstIterator<GenericTestObject>>::value == false));
    X_ASSERT_IF_FALSE((std::is_assignable<RandomAccessMutableIterator<GenericTestObject>, RandomAccessConstIterator<GenericTestObject>>::value == false));

    X_ASSERT_IF_FALSE((std::is_constructible<BaseConstIterator<GenericTestObject>, BaseMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_constructible<InputConstIterator<GenericTestObject>, InputMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_constructible<OutputConstIterator<GenericTestObject>, OutputMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_constructible<ForwardConstIterator<GenericTestObject>, ForwardMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_constructible<BidirectionalConstIterator<GenericTestObject>, BidirectionalMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_constructible<RandomAccessConstIterator<GenericTestObject>, RandomAccessMutableIterator<GenericTestObject>>::value == true));

    X_ASSERT_IF_FALSE((std::is_assignable<BaseConstIterator<GenericTestObject>, BaseMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_assignable<InputConstIterator<GenericTestObject>, InputMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_assignable<OutputConstIterator<GenericTestObject>, OutputMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_assignable<ForwardConstIterator<GenericTestObject>, ForwardMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_assignable<BidirectionalConstIterator<GenericTestObject>, BidirectionalMutableIterator<GenericTestObject>>::value == true));
    X_ASSERT_IF_FALSE((std::is_assignable<RandomAccessConstIterator<GenericTestObject>, RandomAccessMutableIterator<GenericTestObject>>::value == true));
}

namespace DS {
    namespace TESTS {
        void testIterators() {
            X_DEBUG_COMMENT("Started %s", __func__);
            using namespace DS;
            constexpr int array_size = 10;
            checkisIteratorConstructible();

            GenericTestObject mutable_test_data[array_size] = { 1,2,3,4,5,6,7,8,9,10 };
            const GenericTestObject const_test_data[array_size] = { 1,2,3,4,5,6,7,8,9,10 };

            testBaseIterator<BaseMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testInputIterator<InputMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testOutputIterator<OutputMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testForwardIterator<ForwardMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testBidirectionalIterator<BidirectionalMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testRandomAccessIterator<RandomAccessMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);

            testBaseIterator<BaseConstIterator<GenericTestObject>, const GenericTestObject>(const_test_data, array_size);
            testInputIterator<InputConstIterator<GenericTestObject>, const GenericTestObject>(const_test_data, array_size);
            testOutputIterator<OutputConstIterator<GenericTestObject>, const GenericTestObject>(const_test_data, array_size);
            testForwardIterator<ForwardConstIterator<GenericTestObject>, const GenericTestObject>(const_test_data, array_size);
            testBidirectionalIterator<BidirectionalConstIterator<GenericTestObject>, const GenericTestObject>(const_test_data, array_size);
            testRandomAccessIterator<RandomAccessConstIterator<GenericTestObject>, const GenericTestObject>(const_test_data, array_size);

            std::array<GenericTestObject, array_size> ar = { 1,2,3,4,5,6,7,8,9,10 };
            std::array<const GenericTestObject, array_size> const_ar = { 1,2,3,4,5,6,7,8,9,10 };
            testBaseIterator<BaseMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testInputIterator<InputMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testOutputIterator<OutputMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testForwardIterator<ForwardMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testBidirectionalIterator<BidirectionalMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);
            testRandomAccessIterator<RandomAccessMutableIterator<GenericTestObject>, GenericTestObject>(mutable_test_data, array_size);

            testBidirectionalIterator<std::array<GenericTestObject, array_size>::iterator, GenericTestObject>(mutable_test_data, array_size);
            testBidirectionalIterator<std::array<GenericTestObject, array_size>::const_iterator, const GenericTestObject>(const_test_data, array_size);
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}

int main() {
    DS::TESTS::testIterators();
    return 0;
}
