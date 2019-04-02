#ifndef DSBINARYSEARCHTREE_H
#define DSBINARYSEARCHTREE_H

// includes ////////////////////////////////////////
#include <cstddef>

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {

    /// @brief Implements an ordered binary tree
    /// Characteristics:
    /// Non-contiguous
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Search: O(h) or O(logn)
    /// - Insert: O(h) or O(logn)
    /// - Delete: O(h) or O(logn)
    ///
    /// @tparam T the data type of the elements
    template <typename T>
    class BinarySearchTree {
    public:
        /// @brief Internal implementation of a node
        struct Node {
        protected:
            /// @brief Data type
            T m_data = { nullptr };
            /// @brief Left pointer
            Node *m_left = { nullptr };
            /// @brief Right pointer
            Node *m_right = { nullptr };

            friend class BinarySearchTree<T>;
        public:
            /// @brief Explicit Constructor
            explicit Node(const T& _data) :m_data(_data) { }

            /// @brief Retrieves the left node
            /// @return the left node
            const Node* left(void) const    { return m_left; }

            /// @brief Retrieves the right node
            /// @return the right node
            const Node* right(void) const   { return m_right; }

            /// @brief Retrieves the data of the node
            /// @return the data of the list
            const T* data(void) const       { return &m_data; }
        };

        using node_type = struct Node;
        using size_type = std::size_t;

    protected:

        // protected variable declarations
        node_type* m_root = { nullptr };

        // protected function declarations
        /// @brief Clone the container
        /// @param newcontainer the new container
        /// @param oldcontainer the old container
        void clone(BinarySearchTree& newcontainer, const BinarySearchTree& oldcontainer);

        /// @brief copies a node by recursively traversing the container
        /// @param node_ptr the node to start traversing
        /// @param old_node the node to copy from a similar container
        void copyNodesPreorder(node_type** node_ptr, const node_type* old_node);

        /// @brief Recursively destroy all elements, starting from node
        /// @param node the node to start traversing
        void destroyPostorder(node_type* node);

        /// @brief Find the left-most leaf of the requested node, i.e., the leaf with the next ordered value
        /// @param node the node to start traversing
        node_type* searchInorderSuccessor(node_type* node) const;

    private:
        // private variable declarations

        // private function declarations

    public:

        /// @brief Default Constructor
        BinarySearchTree() = default;

        /// @brief Destructor
        ~BinarySearchTree();

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        BinarySearchTree(const BinarySearchTree& other);

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        BinarySearchTree& operator=(const BinarySearchTree& other);

        /// @brief Return the height of the sub-tree
        /// @return the height of the sub-tree
        size_type height(node_type* node) const;

        /// @brief Destroy all elements
        void destroy();

        /// @brief Retrieves the head of the list
        /// @return the head of the list
        node_type* root(void)               { return m_root; }
        /// @brief Retrieves the head of the list
        /// @return the head of the list
        const node_type* root(void) const   { return m_root; }

        /// @brief Retrieves the left node
        /// @param node the node to return the left
        /// @param data the data to insert
        /// @return the left node
        node_type* insertPreOrder(node_type* node, const T& data);

        /// @brief Searches for a node by recursively traversing the container
        /// @param node a node to start the traversal
        /// @param data the data in the node
        /// @return the node containing the data, otherwise nullptr
        node_type* searchPreorder(node_type* node, const T& data) const;

        /// @brief Searches for a node to delete by recursively traversing the container
        /// @param node a node to start the traversal
        /// @param data the data in the node
        /// @return a flag indicating whether the deletion was successful
        node_type* deletePreorder(node_type* node, const T& data);

#ifdef DS_DEBUG_LOG
        /// @brief Print traversal of the tree in a pretty way
        /// @param node the start node
        /// @param str a string to store the result
        /// @param level_offset the text to append to each level
        /// @param start_level the level of the node (should not change)
        void printNodePretty(node_type* node, std::string& str, const std::string& level_offset = "\t", int start_level = 0) const;

        /// @brief Print preorder traversal of the tree (root, left, right), e.g. for copy operations
        /// @param node the start node
        /// @param str a string to store the result
        void printNodePreorder(node_type* node, std::string& str) const;

        /// @brief Print postorder traversal of the tree (left, right, root), e.g. for deletion operations
        /// @param node the start node
        /// @param str a string to store the result
        void printNodePostorder(node_type* node, std::string& str) const;

        /// @brief Print inorder traversal of the tree (left, root, right), e.g. for ordered key traversal of BST
        /// @param node the start node
        /// @param str a string to store the result
        void printNodeInorder(node_type* node, std::string& str) const;

        /// @brief Print levelorder traversal of the tree (left, root, right), e.g. for DFS operations
        /// @param start_level the start level node
        /// @param requested_level the requested level to find
        /// @param str a string to store the result
        /// @param start_level the level of the node (should not change)
        void printNodeLevelorder(node_type* node, int requested_level, std::string& str, int start_level = 0) const;
#endif// DS_DEBUG_LOG

        /// @brief Logs the container
        void print(void) const;
    };
}
#include "BinarySearchTree.inl"

#endif //DSBINARYSEARCHTREE_H
