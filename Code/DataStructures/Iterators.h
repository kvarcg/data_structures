#ifndef DSITERATORS_H
#define DSITERATORS_H

// includes ////////////////////////////////////////


// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

#include <cstddef>
#include <type_traits>

/*
BaseIterator
    //base properties
    BaseIterator(const BaseIterator& other);
    BaseIterator& operator=(const BaseIterator& other);
    BaseIterator& operator++();
    reference operator*() const;

InputIterator
    //base properties
    BaseIterator(const BaseIterator& other);
    BaseIterator& operator=(const BaseIterator& other);
    BaseIterator& operator++();
    reference operator*() const;

    //input properties
    bool operator==(const InputIterator& rhs) const;
    bool operator!=(const InputIterator& rhs) const;
    InputIterator operator++(int);

    pointer operator->() const;

OutputIterator
    //base properties
    BaseIterator(const BaseIterator& other);
    BaseIterator& operator=(const BaseIterator& other);
    BaseIterator& operator++();
    reference operator*() const;

    //output properties
    OutputIterator operator++(int);

ForwardIterator
    //base properties
    BaseIterator(const BaseIterator& other);
    BaseIterator& operator=(const BaseIterator& other);
    BaseIterator& operator++();
    reference operator*() const;

    //input properties
    bool operator==(const InputIterator& rhs) const;
    bool operator!=(const InputIterator& rhs) const;
    InputIterator operator++(int);

    pointer operator->() const;

    //forward properties
    ForwardIterator();

BidirectionalIterator
    //base properties
    BaseIterator(const BaseIterator& other);
    BaseIterator& operator=(const BaseIterator& other);
    BaseIterator& operator++();
    reference operator*() const;

    //input properties
    bool operator==(const InputIterator& rhs) const;
    bool operator!=(const InputIterator& rhs) const;
    InputIterator operator++(int);

    pointer operator->() const;

    //forward properties
    ForwardIterator();

    //bidirectionalIterator
    BidirectionalIterator & operator--();
    BidirectionalIterator & operator--(int);

RandomAccessIterator
    //base properties
    BaseIterator(const BaseIterator& other);
    BaseIterator& operator=(const BaseIterator& other);
    BaseIterator& operator++();
    reference operator*() const;

    //input properties
    bool operator==(const InputIterator& rhs) const;
    bool operator!=(const InputIterator& rhs) const;
    InputIterator operator++(int);

    pointer operator->() const;

    //forward properties
    ForwardIterator();

    //bidirectional properties
    BidirectionalIterator & operator--();
    BidirectionalIterator & operator--(int);

    //random access properties
    RandomAccessIterator& operator+=(difference_type offset);
    RandomAccessIterator& operator-=(difference_type offset);
    friend RandomAccessIterator operator+(const RandomAccessIterator& lhs, difference_type offset);
    friend RandomAccessIterator operator-(const RandomAccessIterator& lhs, difference_type offset);
    friend difference_type operator-(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs);
    reference operator[](difference_type index) const;
    friend bool operator< (const RandomAccessIterator& lhs, const RandomAccessIterator& rhs);
    friend bool operator> (const RandomAccessIterator& lhs, const RandomAccessIterator& rhs);
    friend bool operator<=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs);
    friend bool operator>=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs);
*/

namespace DS {

    /// @brief Implements a base iterator
    /// @tparam isConst a flag if this is a const iterator
    /// @tparam the data type
    template<bool isConst, class T>
    class IteratorBase
    {
    public:
        using difference_type = ptrdiff_t;
        using value_type = typename std::conditional<isConst, const T, T>::type;
        using pointer = typename std::conditional<isConst, const T*, T*>::type;
        using reference = typename std::conditional<isConst, const T&, T&>::type;
        using isConst_t = typename std::conditional<isConst, const T, T>::type;
        friend class IteratorBase<true, T>;

    private:
        // private variable declarations

        // private function declarations

    protected:
        // protected variable declarations
        pointer m_ptr;

        /// @brief Protected Constructor
        IteratorBase() : m_ptr(nullptr) {
        }

    public:
        /// @brief Copy Constructor to allow copy construction of a const iterator from a mutable one
        /// @tparam isConst a flag if this is a const iterator
        /// @tparam the data type
        /// @param mutableIter the mutable iterator to copy construct from
        template <bool _isConst = isConst,
            typename std::enable_if<(_isConst), bool>::type = 0>
            IteratorBase(const IteratorBase<false, T>& mutableIter) {
            *this = mutableIter;
        }

        /// @brief Copy Assignment to allow copy construction of a const iterator from a mutable one
        /// @tparam isConst a flag if this is a const iterator
        /// @tparam the data type
        /// @param mutableIter the mutable iterator to copy assign from
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        IteratorBase& operator=(const IteratorBase<false, T>& mutableIter) {
            this->m_ptr = mutableIter.m_ptr;
            return *this;
        }

        /// @brief Explicit Constructor
        /// @param ptr a pointer to the data
        explicit IteratorBase(pointer ptr) :
            m_ptr(ptr) { }

        /// @brief Copy Constructor
        /// @param other the iterator to copy
        IteratorBase(const IteratorBase& other) {
            *this = other;
        }

        /// @brief Copy assignment operator
        /// @param other the iterator to copy assign
        IteratorBase& operator=(const IteratorBase& other) {
            if (this != &other)
            {
                m_ptr = other.m_ptr;
            }
            return *this;
        }

        /// @brief Pre-increment operator
        /// @return The incremented operator
        IteratorBase& operator++() { ++m_ptr; return *this; }

        /// @brief Dereference operator
        /// @return The internal member
        reference operator*() const { return *m_ptr; }
    };

    /// @brief Implements the input iterator
    /// @tparam isConst a flag if this is a const iterator
    /// @tparam the data type
    template<bool isConst, class T>
    class IteratorInput : public IteratorBase<isConst, T>
    {
    private:
        // private variable declarations

        // private function declarations

    protected:
        // protected variable declarations
        /// @brief Protected Default Constructor
        IteratorInput() = default;

        // protected function declarations

    public:
        using iterator_category = std::input_iterator_tag;
        using pointer = typename IteratorBase<isConst, T>::pointer;
        using IteratorBase<isConst, T>::IteratorBase;
        friend class IteratorInput<true, T>;

        // allow copy construction of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        IteratorInput(const IteratorInput<false, T>& mutableIter) {
            *this = mutableIter;
        }

        // allow copy assignment of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        IteratorInput& operator=(const IteratorInput<false, T>& mutableIter) {
            this->m_ptr = mutableIter.m_ptr;
            return *this;
        }

        /// @brief Equality operator
        /// @param rhs the member to compare
        /// @return The result of the comparison
        bool operator==(const IteratorInput& rhs) const { return this->m_ptr == rhs.m_ptr; }

        /// @brief Inequality operator
        /// @param rhs the member to compare
        /// @return The result of the comparison
        bool operator!=(const IteratorInput& rhs) const { return !(*this == rhs); }

        /// @brief Pre-increment operator
        /// @return The incremented operator
        IteratorInput& operator++() { ++this->m_ptr; return *this; }

        /// @brief Post-increment operator
        /// @return The incremented operator
        IteratorInput operator++(int) {
            IteratorInput temp = *this;
            ++this->m_ptr;
            return temp;
        }

        /// @brief Member access operator
        /// @return The internal pointer member
        pointer operator->() const { return this->m_ptr; }
    };

    /// @brief Implements the output iterator
    /// @tparam isConst a flag if this is a const iterator
    /// @tparam the data type
    template<bool isConst, class T>
    class IteratorOutput : public IteratorBase<isConst, T>
    {
    private:
        // private variable declarations

        // private function declarations

    protected:
        /// @brief Protected Default Constructor
        IteratorOutput() = default;

        // protected function declarations

    public:
        using iterator_category = std::output_iterator_tag;
        using IteratorBase<isConst, T>::IteratorBase;
        friend class IteratorOutput<true, T>;

        // allow copy construction of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        IteratorOutput(const IteratorOutput<false, T>& mutableIter) {
            *this = mutableIter;
        }

        // allow copy assignment of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        IteratorOutput& operator=(const IteratorOutput<false, T>& mutableIter) {
            this->m_ptr = mutableIter.m_ptr;
            return *this;
        }

        /// @brief Pre-increment operator
        /// @return The incremented operator
        IteratorOutput& operator++() { ++this->m_ptr; return *this; }

        /// @brief Post-increment operator
        /// @return The incremented operator
        IteratorOutput operator++(int) {
            IteratorOutput temp = *this;
            ++this->m_ptr;
            return temp;
        }
    };

    template<bool isConst, class T>
    class ForwardIterator : public IteratorInput<isConst, T>
    {
    private:
        // private variable declarations

        // private function declarations

    protected:
        // protected variable declarations

        // protected function declarations

    public:
        using iterator_category = std::forward_iterator_tag;
        using IteratorInput<isConst, T>::IteratorInput;
        friend class ForwardIterator<true, T>;

        // allow copy construction of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        ForwardIterator(const ForwardIterator<false, T>& mutableIter) {
            *this = mutableIter;
        }

        // allow copy assignment of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        ForwardIterator& operator=(const ForwardIterator<false, T>& mutableIter) {
            this->m_ptr = mutableIter.m_ptr;
            return *this;
        }

        /// @brief Default Constructor
        ForwardIterator() = default;

        /// @brief Pre-increment operator
        /// @return The incremented operator
        ForwardIterator& operator++() { ++this->m_ptr; return *this; }

        /// @brief Post-increment operator
        /// @return The incremented operator
        ForwardIterator operator++(int) {
            ForwardIterator temp = *this;
            ++this->m_ptr;
            return temp;
        }
    };

    /// @brief Implements the bidirectional iterator
    /// @tparam isConst a flag if this is a const iterator
    /// @tparam the data type
    template<bool isConst, class T>
    class IteratorBidirectional : public ForwardIterator<isConst, T>
    {
    private:
        // private variable declarations

        // private function declarations

    protected:
        // protected variable declarations

        // protected function declarations

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using ForwardIterator<isConst, T>::ForwardIterator;
        friend class IteratorBidirectional<true, T>;

        // allow copy construction of a const iterator from a mutable one
        template <bool _isConst = isConst,
            typename std::enable_if<(_isConst), bool>::type = 0>
            IteratorBidirectional(const IteratorBidirectional<false, T>& mutableIter) {
            *this = mutableIter;
        }

        // allow copy assignment of a const iterator from a mutable one
        template <bool _isConst = isConst,
            typename std::enable_if<(_isConst), bool>::type = 0>
            IteratorBidirectional& operator=(const IteratorBidirectional<false, T>& mutableIter) {
            this->m_ptr = mutableIter.m_ptr;
            return *this;
        }

        /// @brief Default Constructor
        IteratorBidirectional() = default;

        /// @brief Pre-decrement operator
        /// @return The decremented operator
        IteratorBidirectional & operator--() { --this->m_ptr; return *this; }

        /// @brief Post-decrement operator
        /// @return The decremented operator
        IteratorBidirectional operator--(int) {
            IteratorBidirectional temp = *this;
            --this->m_ptr;
            return temp;
        }

        /// @brief Pre-increment operator
        /// @return The incremented operator
        IteratorBidirectional& operator++() { ++this->m_ptr; return *this; }

        /// @brief Post-increment operator
        /// @return The incremented operator
        IteratorBidirectional operator++(int) {
            IteratorBidirectional temp = *this;
            ++this->m_ptr;
            return temp;
        }
    };

    /// @brief Implements the random access iterator
    /// @tparam isConst a flag if this is a const iterator
    /// @tparam the data type
    template<bool isConst, class T>
    class IteratorRandomAccess : public IteratorBidirectional<isConst, T>
    {
    private:
        // private variable declarations

        // private function declarations

    protected:
        // protected variable declarations

        // protected function declarations

    public:
        using iterator_category = std::random_access_iterator_tag;
        using IteratorBidirectional<isConst, T>::IteratorBidirectional;
        using difference_type = ptrdiff_t;
        using reference = typename IteratorBase<isConst, T>::reference;
        friend class IteratorRandomAccess<true, T>;

        // allow copy construction of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        IteratorRandomAccess(const IteratorRandomAccess<false, T>& mutableIter) { *this = mutableIter; }

        // allow copy assignment of a const iterator from a mutable one
        template <bool _isConst = isConst, typename std::enable_if<(_isConst), bool>::type = 0>
        IteratorRandomAccess& operator=(const IteratorRandomAccess<false, T>& mutableIter) {
            this->m_ptr = mutableIter.m_ptr;
            return *this;
        }

        /// @brief Default Constructor
        IteratorRandomAccess() = default;

        /// @brief Compound addition assignment operator
        /// @param offset the offset to add to the iterator
        /// @return The iterator
        IteratorRandomAccess& operator+=(difference_type offset) { this->m_ptr += offset; return *this; }

        /// @brief Compound subtraction assignment operator
        /// @param offset the offset to add to the iterator
        /// @return The iterator
        IteratorRandomAccess& operator-=(difference_type offset) { this->m_ptr += -offset; return *this; }

        /// @brief Addition assignment operator with offset
        /// @param lhs the member to perform the operation
        /// @param offset the offset to add to the iterator
        /// @return The new iterator
        friend IteratorRandomAccess operator+(const IteratorRandomAccess& lhs, difference_type offset) {
            IteratorRandomAccess tmp = lhs;
            return tmp += offset;
        }

        /// @brief Subtraction assignment operator with offset
        /// @param lhs the member to perform the operation
        /// @param offset the offset to subtract from the iterator
        /// @return The new iterator
        friend IteratorRandomAccess operator-(const IteratorRandomAccess& lhs, difference_type offset) {
            return lhs + (-offset);
        }

        /// @brief Difference between iterators
        /// @param lhs the member to subtract to
        /// @param rhs the member to subtract from
        /// @return The result of the subtraction operation
        friend difference_type operator-(const IteratorRandomAccess& lhs, const IteratorRandomAccess& rhs) {
            return (lhs.m_ptr - rhs.m_ptr);
        }

        /// @brief Iterator-based indexing
        /// @param index the offset to apply to the iterator
        /// @return A reference to the resulting member
        reference operator[](difference_type index) const {
            return *(this->m_ptr + index);
        }

        /// @brief Less equality operator
        /// @param lhs the member to compare
        /// @param rhs the member to compare
        /// @return The result of the comparison
        friend bool operator< (const IteratorRandomAccess& lhs, const IteratorRandomAccess& rhs) { return lhs.m_ptr < rhs.m_ptr; }

        /// @brief Larger equality operator
        /// @param lhs the member to compare
        /// @param rhs the member to compare
        /// @return The result of the comparison
        friend bool operator> (const IteratorRandomAccess& lhs, const IteratorRandomAccess& rhs) { return lhs.m_ptr > rhs.m_ptr; }

        /// @brief Less-equal equality operator
        /// @param lhs the member to compare
        /// @param rhs the member to compare
        /// @return The result of the comparison
        friend bool operator<=(const IteratorRandomAccess& lhs, const IteratorRandomAccess& rhs) { return !(lhs > rhs); }

        /// @brief Larger-equal equality operator
        /// @param lhs the member to compare
        /// @param rhs the member to compare
        /// @return The result of the comparison
        friend bool operator>=(const IteratorRandomAccess& lhs, const IteratorRandomAccess& rhs) { return !(lhs < rhs); }

        /// @brief Pre-decrement operator
        /// @return The decremented operator
        IteratorRandomAccess& operator--() { --this->m_ptr; return *this; }

        /// @brief Post-decrement operator
        /// @return The decremented operator
        IteratorRandomAccess operator--(int) {
            IteratorRandomAccess temp = *this;
            --this->m_ptr;
            return temp;
        }

        /// @brief Pre-increment operator
        /// @return The incremented operator
        IteratorRandomAccess& operator++() { ++this->m_ptr; return *this; }

        /// @brief Post-increment operator
        /// @return The incremented operator
        IteratorRandomAccess operator++(int) {
            IteratorRandomAccess temp = *this;
            ++this->m_ptr;
            return temp;
        }
    };

    template <class T> using BaseMutableIterator = IteratorBase<false, T>;
    template <class T> using BaseConstIterator = IteratorBase<true, T>;
    template <class T> using InputMutableIterator = IteratorInput<false, T>;
    template <class T> using InputConstIterator = IteratorInput<true, T>;
    template <class T> using OutputMutableIterator = IteratorOutput<false, T>;
    template <class T> using OutputConstIterator = IteratorOutput<true, T>;
    template <class T> using ForwardMutableIterator = ForwardIterator<false, T>;
    template <class T> using ForwardConstIterator = ForwardIterator<true, T>;
    template <class T> using BidirectionalMutableIterator = IteratorBidirectional<false, T>;
    template <class T> using BidirectionalConstIterator = IteratorBidirectional<true, T>;
    template <class T> using RandomAccessMutableIterator = IteratorRandomAccess<false, T>;
    template <class T> using RandomAccessConstIterator = IteratorRandomAccess<true, T>;
}  // namespace DS

#endif //DSITERATORS_H
