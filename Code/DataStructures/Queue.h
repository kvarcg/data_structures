#ifndef DSQUEUE_H
#define DSQUEUE_H

// includes ////////////////////////////////////////


// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {

    /// @brief Implements a linked-list based queue
    /// Characteristics:
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Insert: O(1)
    /// - Delete: O(1)
    /// - Push/Pop: O(1)
    ///
    /// @tparam T the data type of the elements
    template <typename T>
    class Queue {
    public:
        /// @brief Internal implementation of a node
        struct NodeSingle {
        protected:
            /// @brief Data type
            T m_data = { nullptr };
            /// @brief Prev pointer
            NodeSingle *m_prev = { nullptr };
            /// @brief Explicit Constructor
            explicit NodeSingle(const T& _data) :m_data(_data) { }
            friend class Queue<T>;
        public:
            /// @brief Retrieves the data of the node
            /// @return the data of the list
            T* data(void)                        { return &m_data; }
            /// @brief Retrieves the data of the node
            /// @return the data of the list
            const T* data(void) const            { return &m_data; }
        };
        using node_type = struct NodeSingle;

    protected:
        // protected variable declarations
        node_type* m_front = { nullptr };
        node_type* m_back  = { nullptr };

        // protected function declarations
        /// @brief Clone the container
        /// @param newcontainer the new container
        /// @param oldcontainer the old container
        void clone(Queue& newcontainer, const Queue& oldcontainer);

    private:
        // private variable declarations

        // private function declarations

    public:

        /// @brief Default Constructor
        Queue() = default;

        /// @brief Destructor
        ~Queue();

        /// @brief Copy Constructor
        /// @param other the container to copy
        Queue(const Queue& other);

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        Queue& operator=(const Queue& other);

        /// @brief Destroy all elements
        void destroy(void);

        /// @brief Retrieves the front
        /// @return the front
        node_type* front(void)                          { return m_front; }
        /// @brief Retrieves the front
        /// @return the front
        const node_type* front(void) const              { return m_front; }

        /// @brief Retrieves the back
        /// @return the back
        node_type* back(void)                           { return m_back; }
        /// @brief Retrieves the back
        /// @return the back
        const node_type* back(void) const               { return m_back; }

        /// @brief Add a new element to the back O(1)
        /// @param val the data of the new node
        /// @return the new node
        void push(const T& val);

        /// @brief Remove an element from the front O(1)
        /// @return the new node
        void pop(void);

        /// @brief Checks if the container is empty
        /// @return A flag indicating whether the container is empty
        constexpr bool empty() const noexcept           { return m_front == nullptr; }

        /// @brief Logs the container
        void print(void) const;
    };
}

#include "Queue.inl"

#endif //DSQUEUE_H
