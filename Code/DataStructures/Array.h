#ifndef DSARRAY_H
#define DSARRAY_H

// includes ////////////////////////////////////////
#include <cstddef>
#include "Allocators.h"
#include "Iterators.h"

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {
    /// @brief Implements an array data structure
    /// Characteristics:
    /// Contiguous
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Indexing: O(1)
    /// - Search: O(n)
    ///
    /// @tparam T the data type of the elements
    /// @tparam N the size of the array
    template <typename T, std::size_t N>
    class Array {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type & ;
        using const_reference = const value_type&;
        using pointer = value_type * ;
        using const_pointer = const value_type*;
        using iterator = RandomAccessMutableIterator<value_type>;
        using const_iterator = RandomAccessConstIterator<value_type>;
        using allocator = AllocatorSimple<value_type>;

    protected:
        // protected variable declarations

        // protected function declarations
        value_type m_data[N == 0 ? 1 : N];

    private:
        // private variable declarations

        // private function declarations

    public:
        /// @brief Default Constructor
        Array(void) = default;

        /// @brief Destructor
        ~Array(void) = default;

        /// @brief Copy Constructor
        /// @param other the container to copy
        Array(const Array& other) = default;

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        Array& operator=(const Array& other) = default;

        // public function declarations

        /// @brief Return a reference to the underlying data with bounds checking
        /// @param pos the position in the array
        /// @return A reference to data
        reference at(size_type pos);
        /// @brief Return a reference to the underlying data with bounds checking
        /// @param pos the position in the array
        /// @return A reference to data
        const_reference at(size_type pos) const;

        /// @brief Return a reference to the first element
        /// @return A reference to data
        reference front(void) noexcept                  { return m_data[0]; }
        /// @brief Return a reference to the first element
        /// @return A reference to data
        const_reference front(void) const noexcept      { return m_data[0]; }

        /// @brief Return a reference to the last element
        /// @return A reference to data
        reference back(void) noexcept                   { return m_data[size() - 1]; }
        /// @brief Return a reference to the last element
        /// @return A reference to data
        const_reference back(void) const noexcept       { return m_data[size() - 1]; }

        /// @brief Return a reference to the underlying data
        /// @param pos the position in the array
        /// @return A reference to data
        reference operator[](size_type pos) noexcept    { return m_data[pos]; }
        /// @brief Return a reference to the underlying data
        /// @param pos the position in the array
        /// @return A reference to data
        const_reference operator[](size_type pos) const noexcept { return m_data[pos]; }

        /// @brief Return a pointer to the underlying data
        /// @return A pointer to data
        pointer data(void) noexcept                     { return m_data; }
        /// @brief Return a pointer to the underlying data
        /// @return A pointer to data
        const_pointer data(void) const noexcept         { return m_data; }

        /// @brief Return an iterator to the beginning of the underlying data
        /// @return An iterator to the beginning of data
        iterator begin(void) noexcept                   { return iterator(&m_data[0]); }
        /// @brief Return an iterator to the beginning of the underlying data
        /// @return An iterator to the beginning of data
        const_iterator begin(void) const noexcept       { return const_iterator(&m_data[0]); }
        /// @brief Return an iterator to the beginning of the underlying data
        /// @return An iterator to the beginning of data
        const_iterator cbegin(void) const noexcept      { return const_iterator(&m_data[0]); }

        /// @brief Return an iterator to the end of the underlying data
        /// @return An iterator to the end of data
        iterator end(void) noexcept                     { return iterator(&m_data[size()]); }
        /// @brief Return an iterator to the end of the underlying data
        /// @return An iterator to the end of data
        const_iterator end(void) const noexcept         { return const_iterator(&m_data[size()]); }
        /// @brief Return an iterator to the end of the underlying data
        /// @return An iterator to the end of data
        const_iterator cend(void) const noexcept        { return const_iterator(&m_data[size()]); }

        /// @brief Checks if the container is empty
        /// @return A flag indicating whether the container is empty
        constexpr bool empty(void) const noexcept       { return size() == 0; }

        /// @brief Size of the container
        /// @return Size of the container
        constexpr std::size_t size(void) const noexcept { return N; }

        /// @brief Fill the array with value
        /// @param value the value to fill the array
        void fill(const_reference value) noexcept;

        /// @brief Logs the container
        void print(void) const;
    };
    /// @brief Returns a reference to the underlying data
    /// @tparam I the element's position
    /// @tparam T the data type of the elements
    /// @tparam N the size of the array
    /// @param a the array to retrieve the data from
    /// @return A reference to data
    template<std::size_t I, class T, std::size_t N>
    constexpr typename Array<T, N>::reference get(Array<T, N>& a) noexcept { return a[I]; }

    /// @brief Returns a reference to the underlying data
    /// @tparam I the element's position
    /// @tparam T the data type of the elements
    /// @tparam N the size of the array
    /// @param a the array to retrieve the data from
    /// @return A reference to data
    template<std::size_t I, class T, std::size_t N>
    constexpr typename Array<T, N>::const_reference get(const Array<T, N>& a) noexcept { return a[I]; }

}  // namespace DS

#include "Array.inl"

#endif //DSARRAY_H
