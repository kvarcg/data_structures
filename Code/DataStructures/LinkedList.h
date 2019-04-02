#ifndef DSLINKEDLIST_H
#define DSLINKEDLIST_H

// includes ////////////////////////////////////////


// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {
    /// @brief Implements a mple linked-list
    /// Characteristics:
    /// Non-contiguous
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Indexing: O(n)
    /// - Search: O(n)
    /// - Insert: O(1)
    /// - Delete: O(1)
    /// - Push/Pop: O(1) front O(n) back
    ///
    /// @tparam T the data type of the elements
    template <typename T>
    class LinkedList {
    public:
        /// @brief Internal implementation of a node
        struct NodeSingle {
        protected:
            /// @brief Data type
            T m_data = { nullptr };
            /// @brief Next pointer
            NodeSingle *m_next = { nullptr };
            /// @brief Explicit Constructor
            explicit NodeSingle(const T& data) :m_data(data) { }
            friend class LinkedList<T>;
        public:
            /// @brief Retrieves the next node
            /// @return the next node
            NodeSingle* next(void)              { return m_next; }
            /// @brief Retrieves the next node
            /// @return the next node
            const NodeSingle* next(void) const  { return m_next; }
            /// @brief Retrieves the data of the node
            /// @return the data of the list
            T* data(void)                       { return &m_data; }
            /// @brief Retrieves the data of the node
            /// @return the data of the list
            const T* data(void) const           { return &m_data; }
        };

        using node_type = struct NodeSingle;

    protected:

        // protected variable declarations
        node_type* m_head = { nullptr };

        // protected function declarations
        /// @brief Clone the container
        /// @param newcontainer the new container
        /// @param oldcontainer the old container
        void clone(LinkedList& newcontainer, const LinkedList& oldcontainer);

    private:

        // private variable declarations

        // private function declarations

    public:

        /// @brief Default Constructor
        LinkedList() = default;

        /// @brief Destructor
        ~LinkedList();

        /// @brief Copy Constructor
        /// @param other the container to copy
        LinkedList(const LinkedList& other);

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        LinkedList& operator=(const LinkedList& other);

        /// @brief Reverses the list
        /// @return the reversed list
        LinkedList reverse(void);

        /// @brief Destroy all elements
        void destroy(void);

        /// @brief Retrieves the head of the list
        /// @return the head of the list
        node_type* head(void)               { return m_head; }
        /// @brief Retrieves the head of the list
        /// @return the head of the list
        const node_type* head(void) const   { return m_head; }

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

        /// @brief Add a new element to the back (new "tail") O(N)
        /// @param val the data of the new node
        /// @return the new node
        node_type* push_back(const T& val);

        /// @brief Erase an element from the back (new tail) O(N)
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
#include "LinkedList.inl"

#endif //DSLINKEDLIST_H
