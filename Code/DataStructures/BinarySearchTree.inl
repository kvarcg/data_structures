#ifndef DSBINARYSEARCHTREE_INL
#define DSBINARYSEARCHTREE_INL

namespace DS {

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree() {
        destroy();
    }

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other) {
        clone(*this, other);
    }

    template <typename T>
    BinarySearchTree<T>& BinarySearchTree<T>::operator =(const BinarySearchTree<T>& other) {
        if (this != &other) {
            BinarySearchTree<T> tmp_container;
            clone(tmp_container, other);

            std::swap(m_root, tmp_container.m_root);
            // destructor of tmp_container is called implicitly here
        }
        return *this;
    }

    template <typename T>
    void BinarySearchTree<T>::clone(BinarySearchTree<T>& newcontainer, const BinarySearchTree<T>& oldcontainer) {
        BinarySearchTree<T> tmp_tree;
        tmp_tree.m_root = my_new node_type(oldcontainer.m_root->m_data);
        copyNodesPreorder(&tmp_tree.m_root, oldcontainer.m_root);

        std::swap(newcontainer.m_root, tmp_tree.m_root);
    }

    template <typename T>
    void BinarySearchTree<T>::copyNodesPreorder(node_type** node_ptr, const node_type* old_node) {

        node_type* node = *node_ptr;
        if (old_node->m_left != nullptr) {
            node->m_left = my_new node_type(old_node->m_left->m_data);
            copyNodesPreorder(&node->m_left, old_node->m_left);
        }

        if (old_node->m_right != nullptr) {
            node->m_right = my_new node_type(old_node->m_right->m_data);
            copyNodesPreorder(&node->m_right, old_node->m_right);
        }
    }

    template <typename T>
    typename BinarySearchTree<T>::size_type BinarySearchTree<T>::height(node_type* node) const {

        if (node == nullptr) {
            return 0;
        }

        size_type left_height = height(node->m_left) + 1;
        size_type right_height = height(node->m_right) + 1;

        return left_height > right_height ? left_height : right_height;
    }

    template <typename T>
    void BinarySearchTree<T>::destroy() {
        destroyPostorder(m_root);
    }

    template <typename T>
    typename BinarySearchTree<T>::node_type* BinarySearchTree<T>::insertPreOrder(node_type* node, const T& data) {

        if (node == nullptr) {
            node = my_new Node(data);
            if (m_root == nullptr) {
                m_root = node;
            }
            return node;
        }


        if (data <= node->m_data) {
            node->m_left = insertPreOrder(node->m_left, data);
        }
        else {
            node->m_right = insertPreOrder(node->m_right, data);
        }

        return node;
    }

    template <typename T>
    typename BinarySearchTree<T>::node_type* BinarySearchTree<T>::searchPreorder(node_type* node, const T& data) const {

        if (node == nullptr || node->m_data == data) {
            return node;
        }

        node_type* return_node = nullptr;

        if (data <= node->m_data) {
            return searchPreorder(node->m_left, data);
        }
        else {
            return searchPreorder(node->m_right, data);
        }
    }

    template <typename T>
    typename BinarySearchTree<T>::node_type* BinarySearchTree<T>::searchInorderSuccessor(node_type* node) const {

        node_type* return_node = node;

        if (node->m_left != nullptr) {
            return_node = searchInorderSuccessor(node->m_left);
        }

        return return_node;
    }

    template <typename T>
    typename BinarySearchTree<T>::node_type* BinarySearchTree<T>::deletePreorder(node_type* node, const T& data)
    {
        if (node == nullptr) {
            return nullptr;
        }

        if (data < node->m_data) {
            node->m_left = deletePreorder(node->m_left, data);
        }
        else if (data > node->m_data) {
            node->m_right = deletePreorder(node->m_right, data);
        } else {

            // no children just delete
            if (node->m_right == nullptr && node->m_left == nullptr) {
                // reset the root if only child
                if (node == m_root) {
                    m_root = nullptr;
                }
                XE_SAFE_DELETE(node)
            }
            // if has one left child
            else if (node->m_right == nullptr) {
                std::swap(node->m_data, node->m_left->m_data);
                XE_SAFE_DELETE(node->m_left);
            } // if has one right child
            else if (node->m_left == nullptr) {
                std::swap(node->m_data, node->m_right->m_data);
                XE_SAFE_DELETE(node->m_right);
            }
            else {
                // if node does has both children
                // find the leaf with the next value and swap
                /* e.g. to delete 100:
                // A: find the node
                // B: find the inorder successor (leaf with the next value) and copy its data (125) to 100
                // C: delete preorder the duplicate node with 125 from the right subtree (this is needed to re-adjust the parent pointers)
                         (A)                      (B)                (C)
                         100                     (125)                150
                       /     \                    /    \               /   \
                      50     150              50     150        (125)  175
                     /  \    /  \            /  \    /   \
                   25   75  125 175         25  75 (125) 175
                */
                node_type* inorder_successor = searchInorderSuccessor(node->m_right);
                node->m_data = inorder_successor->m_data;
                node->m_right = deletePreorder(node->m_right, inorder_successor->m_data);
            }
        }

        return node;
    }

    template <typename T>
    void BinarySearchTree<T>::destroyPostorder(node_type* node) {

        if (node == nullptr) {
            return;
        }

        if (node->m_left != nullptr) {
            destroyPostorder(node->m_left);
        }

        if (node->m_right != nullptr) {
            destroyPostorder(node->m_right);
        }

        XE_SAFE_DELETE(node);
    }

#ifdef DS_DEBUG_LOG
    template <typename T>
    void BinarySearchTree<T>::printNodePreorder(node_type* node, std::string& str) const {

        if (node == nullptr) {
            return;
        }

        str += std::to_string(node->m_data.val) + std::string(" ");

        if (node->m_left != nullptr) {
            printNodePreorder(node->m_left, str);
        }

        if (node->m_right != nullptr) {
            printNodePreorder(node->m_right, str);
        }
    }

    template <typename T>
    void BinarySearchTree<T>::printNodePostorder(node_type* node, std::string& str) const {

        if (node == nullptr) {
            return;
        }

        if (node->m_left != nullptr) {
            printNodePostorder(node->m_left, str);
        }

        if (node->m_right != nullptr) {
            printNodePostorder(node->m_right, str);
        }
        str += std::to_string(node->m_data.val) + std::string(" ");
    }

    template <typename T>
    void BinarySearchTree<T>::printNodeInorder(node_type* node, std::string& str) const {

        if (node == nullptr) {
            return;
        }

        if (node->m_left != nullptr) {
            printNodeInorder(node->m_left, str);
        }

        str += std::to_string(node->m_data.val) + std::string(" ");

        if (node->m_right != nullptr) {
            printNodeInorder(node->m_right, str);
        }
    }

    template <typename T>
    void BinarySearchTree<T>::printNodeLevelorder(node_type* node, int requested_level, std::string& str, int start_level) const {

        if (node == nullptr) {
            return;
        }

        if (start_level == requested_level) {
            str += std::to_string(node->m_data.val) + std::string(" ");
            return;
        }

        if (node->m_left != nullptr) {
            printNodeLevelorder(node->m_left, requested_level, str, start_level + 1);
        }

        if (node->m_right != nullptr) {
            printNodeLevelorder(node->m_right, requested_level, str, start_level + 1);
        }
    }

    template <typename T>
    void BinarySearchTree<T>::printNodePretty(node_type* node, std::string& str, const std::string& level_offset, int level) const {

        if (node == nullptr) {
            return;
        }

        if (node->m_right != nullptr) {
            printNodePretty(node->m_right, str, level_offset, level + 1);
        }

        for (int i = 0; i < level; ++i) {
            str = str.append(level_offset);
        }
        str = str.append(std::to_string(node->m_data.val)).append("\n");

        if (node->m_left != nullptr) {
            printNodePretty(node->m_left, str, level_offset, level + 1);
        }
    }

#endif // DS_DEBUG_LOG

    template <typename T>
    void BinarySearchTree<T>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Tree: Addr:0x%p", (void*)this);
        std::string str;
        printNodePretty(m_root, str);
        X_DEBUG_COMMENT("\n%s", str.c_str());
#endif // DS_DEBUG_LOG
    }
}

#endif //DSBINARYSEARCHTREE_INL
