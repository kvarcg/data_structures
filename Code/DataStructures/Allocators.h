#ifndef DSALLOCATOR_H
#define DSALLOCATOR_H

// includes ////////////////////////////////////////
#include <cstddef>
#include <utility>
#include <memory>

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {

    /// @brief Implements a simple allocator
    /// @tparam T the data type of the elements
    template <typename T>
    struct AllocatorSimple
    {
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        /// @brief Allocates num * sizeof(T) bytes of uninitialized storage
        /// @param num the number of objects to allocate storage for
        /// @return A void pointer to the first byte of the allocated memory block
        void* allocate(size_type num)               { return malloc(num * sizeof(value_type)); }

        /// @brief Deallocates a previously allocated storage
        /// @param ptr a pointer returned by allocate
        void deallocate(T* ptr, size_type)          { ::operator delete(ptr); }

        /// @brief Constructs an object of type T
        /// @param ptr a pointer to allocated storage
        /// @param args the constructor arguments to use
        template<class El, class... Args >
        void construct(El* ptr, Args&&... args)     { :: new (ptr) El(std::forward<Args>(args)...); }

        /// @brief Calls the destructor of an object of type T
        /// @param ptr the pointer to the object
        void destroy(T* ptr)                        { ptr->~T(); }
    };

    /// @brief Wraps a default STL allocator
    /// @param T the data type of the elements
    template <typename T>
    struct AllocatorDefault
    {
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        std::allocator<T> m_allocator;

        /// @brief Allocates num * sizeof(value_type) bytes of uninitialized storage
        /// @param num the number of objects to allocate storage for
        /// @return A void pointer to the first byte of the allocated memory block
        void* allocate(size_type num)               { return m_allocator.allocate(num); }

        /// @brief Deallocates a previously allocated storage
        /// @param ptr a pointer returned by allocate
        /// @param num the number of bytes passed to allocate earlier
        void deallocate(T* ptr, size_type num)      { m_allocator.deallocate(ptr, num); }

        /// @brief Constructs an object of type T
        /// @param ptr a pointer to allocated storage
        /// @param args the constructor arguments to use
        template< class El, class... Args >
        void construct(El* ptr, Args&&... args)     { m_allocator.construct(ptr, std::forward<Args>(args)...); }

        /// @brief Calls the destructor of an object of type T
        /// @param ptr the pointer to the object
        void destroy(T* ptr)                        { m_allocator.destroy(ptr); }
    };

}  // namespace DS

#endif //DSALLOCATOR_H
