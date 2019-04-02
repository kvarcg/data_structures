#ifndef DSDOUBLELINKEDLIST_H
#define DSDOUBLELINKEDLIST_H

// includes ////////////////////////////////////////


// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////


namespace DS {
    /// @brief Implements a double linked-list
    /// Characteristics:
    /// Non-contiguous
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Indexing: O(n)
    /// - Search: O(n)
    /// - Insert: O(1)
    /// - Delete: O(1)
    /// - Push/Pop: O(1) front/back
    ///
    /// @tparam T the data type of the elements
    template <typename T>
    class LinkedListDouble {
    public:
        /// @brief Internal implementation of a node
        struct NodeDouble {
        protected:
            /// @brief Data type
            T m_data = { nullptr };
            /// @brief Prev pointer
            NodeDouble *m_prev = { nullptr };
            /// @brief Next pointer
            NodeDouble *m_next = { nullptr };
            /// @brief Explicit Constructor
            explicit NodeDouble(const T& _data) :m_data(_data) { }
            friend class LinkedListDouble<T>;
        public:
            /// @brief Retrieves the next node
            /// @return the next node
            NodeDouble* next(void)              { return m_next; }
            /// @brief Retrieves the next node
            /// @return the next node
            const NodeDouble* next(void) const  { return m_next; }
            /// @brief Retrieves the prev node
            /// @return the prev node
            NodeDouble* prev(void)              { return m_prev; }
            /// @brief Retrieves the prev node
            /// @return the prev node
            const NodeDouble* prev(void) const  { return m_prev; }
            /// @brief Retrieves the data of the node
            /// @return the data of the list
            T* data(void)                       { return &m_data; }
            /// @brief Retrieves the data of the node
            /// @return the data of the list
            const T* data(void) const           { return &m_data; }
        };

        using node_type = struct NodeDouble;

    protected:

        // protected variable declarations
        node_type* m_head = { nullptr };
        node_type* m_tail = { nullptr };

        // protected function declarations
        /// @brief Clone the container
        /// @param newcontainer the new container
        /// @param oldcontainer the old container
        void clone(LinkedListDouble& newcontainer, const LinkedListDouble& oldcontainer);

    private:
        // private variable declarations

        // private function declarations

    public:

        /// @brief Default Constructor
        LinkedListDouble() = default;

        /// @brief Destructor
        ~LinkedListDouble();

        /// @brief Copy Constructor
        /// @param other the container to copy
        LinkedListDouble(const LinkedListDouble& other);

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        LinkedListDouble& operator=(const LinkedListDouble& other);

        /// @brief Reverses the list
        /// @return the reversed list
        LinkedListDouble reverse(void);

        /// @brief Destroy all elements
        void destroy(void);

        /// @brief Retrieves the head of the list
        /// @return the head of the list
        node_type* head(void)               { return m_head; }
        /// @brief Retrieves the head of the list
        /// @return the head of the list
        const node_type* head(void) const   { return m_head; }

        /// @brief Retrieves the tail of the list
        /// @return the tail of the list
        node_type* tail(void)               { return m_tail; }
        /// @brief Retrieves the tail of the list
        /// @return the tail of the list
        const node_type* tail(void) const   { return m_tail; }

        /// @brief Searches for an element O(N)
        /// @param val the data of the node
        /// @return the found node, nullptr otherwise
        node_type* find(const T& val);

        /// @brief Add a new element to the front (new head) O(1)
        /// @param val the data of the new node
        /// @return the new node
        node_type* push_front(const T& val);

        /// @brief Erase an element from the front (new head) O(1)
        void pop_front();

        /// @brief Add a new element to the back (new tail) O(1)
        /// @param val the data of the new node
        /// @return the new node
        node_type* push_back(const T& val);

        /// @brief Erase an element from the back (new tail) O(1)
        void pop_back();

        /// @brief Insert an element at a node position O(N)
        /// e.g., [2] -> [5] becomes [2] -> [4] -> [5]
        /// @param prev_node the previous node
        /// @param val the data of the new node
        /// @return the new node
        node_type* insert_after(node_type* prev_node, const T& val);

        /// @brief Deletes an existing node O(N)
        /// @param node the node to delete
        void erase(node_type* node);

        /// @brief Logs the container
        void print(void) const;
    };
}
#include "DoubleLinkedList.inl"

#endif //DSDOUBLELINKEDLIST_H
