#ifndef DSBINARYTREE_INL
#define DSBINARYTREE_INL

#ifdef DS_DEBUG_LOG
    #include <vector>
#endif
namespace DS {

    template <typename T>
    BinaryTree<T>::~BinaryTree() {
        destroy();
    }

    template <typename T>
    BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) {
        clone(*this, other);
    }

    template <typename T>
    BinaryTree<T>& BinaryTree<T>::operator =(const BinaryTree<T>& other) {
        if (this != &other) {
            BinaryTree<T> tmp_container;
            clone(tmp_container, other);

            std::swap(m_root, tmp_container.m_root);
            // destructor of tmp_container is called implicitly here
        }
        return *this;
    }

    template <typename T>
    void BinaryTree<T>::clone(BinaryTree<T>& newcontainer, const BinaryTree<T>& oldcontainer) {
        BinaryTree<T> tmp_tree;
        tmp_tree.addLeft(nullptr, oldcontainer.m_root->m_data);
        copyNodesPreorder(&tmp_tree.m_root, oldcontainer.m_root);

        std::swap(newcontainer.m_root, tmp_tree.m_root);
    }

    template <typename T>
    void BinaryTree<T>::copyNodesPreorder(node_type** node_ptr, const node_type* old_node) {

        node_type* node = *node_ptr;
        if (old_node->m_left != nullptr) {
            node->m_left = my_new node_type(old_node->m_left->m_data);
            node->m_left->m_parent = node;
            copyNodesPreorder(&node->m_left, old_node->m_left);
        }

        if (old_node->m_right != nullptr) {
            node->m_right = my_new node_type(old_node->m_right->m_data);
            node->m_right->m_parent = node;
            copyNodesPreorder(&node->m_right, old_node->m_right);
        }
    }

    template <typename T>
    typename BinaryTree<T>::size_type BinaryTree<T>::height(node_type* node) const {

        if (node == nullptr) {
            return 0;
        }

        size_type left_height = height(node->m_left) + 1;
        size_type right_height = height(node->m_right) + 1;

        return left_height > right_height ? left_height : right_height;
    }

    template <typename T>
    void BinaryTree<T>::destroy() {
        destroyPostorder(m_root);
    }

    template <typename T>
    typename BinaryTree<T>::node_type* BinaryTree<T>::addLeft(node_type* node, const T& data) {
        if (m_root == nullptr) {
            m_root = my_new Node(data);
            return m_root;
        }
        node->m_left = my_new Node(data);
        node->m_left->m_parent = node;
        return node->m_left;
    }

    template <typename T>
    typename BinaryTree<T>::node_type* BinaryTree<T>::addRight(node_type* node, const T& data) {
        if (m_root == nullptr) {
            m_root = my_new Node(data);
            return m_root;
        }
        node->m_right = my_new Node(data);
        node->m_right->m_parent = node;
        return node->m_right;
    }

    template <typename T>
    typename BinaryTree<T>::node_type* BinaryTree<T>::searchPreorder(node_type* node, const T& data) const {

        if(node == nullptr) {
            return nullptr;
        }

        node_type* return_node = nullptr;

        if(node->m_data == data) {
            return_node = node;
        }

        if (return_node == nullptr && node->m_left != nullptr) {
            return_node = searchPreorder(node->m_left, data);
        }

        if (return_node == nullptr && node->m_right != nullptr) {
            return_node = searchPreorder(node->m_right, data);
        }

        return return_node;
    }

    template <typename T>
    bool BinaryTree<T>::deletePreorder(node_type* node, const T& data)
    {
        if (node == nullptr) {
            return false;
        }

        bool deleted_node = false;

        if (node->m_data == data) {

            // if node does has both children
            if (node->m_left != nullptr && node->m_right != nullptr) {
                // unordered tree, just set one as the parent
                // set left as parent
                std::swap(node->m_data, node->m_left->m_data);
                // delete left
                XE_SAFE_DELETE(node->m_left);
            }
            // if it has only one child
            else if (node->m_right != nullptr) {
                node->m_data = node->m_right->m_data;
                XE_SAFE_DELETE(node->m_right);
            }
            else if (node->m_left != nullptr) {
                node->m_data = node->m_left->m_data;
                XE_SAFE_DELETE(node->m_left);
            }
            else {
                // if node has no children, swap with the parent and delete
                node_type* parent = node->m_parent;
                if (parent == nullptr && node == m_root) {
                    XE_SAFE_DELETE(node);
                    m_root = nullptr;
                }
                else if (parent->m_left && parent->m_left->m_data == data) {
                    std::swap(parent->m_left->m_data, node->m_data);
                    XE_SAFE_DELETE(parent->m_left);
                }
                else {
                    std::swap(parent->m_right->m_data, node->m_data);
                    XE_SAFE_DELETE(parent->m_right);
                }
            }

            deleted_node = true;
        }

        if (!deleted_node && node->m_left != nullptr) {
            deleted_node = deletePreorder(node->m_left, data);
        }

        if (!deleted_node && node->m_right != nullptr) {
            deleted_node = deletePreorder(node->m_right, data);
        }

        return deleted_node;
    }

    template <typename T>
    void BinaryTree<T>::destroyPostorder(node_type* node) {

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
    void BinaryTree<T>::printNodePreorder(node_type* node, std::string& str) const {

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
    void BinaryTree<T>::printNodePostorder(node_type* node, std::string& str) const {

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
    void BinaryTree<T>::printNodeInorder(node_type* node, std::string& str) const {

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
    void BinaryTree<T>::printNodeLevelorder(node_type* node, int requested_level, std::string& str, int start_level) const {

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
    void BinaryTree<T>::printNodePretty(node_type* node, std::string& str, const std::string& level_offset, int level) const {

        if (node == nullptr) {
            return;
        }

        if (node->m_right != nullptr) {
            printNodePretty(node->m_right, str, level_offset, level + 1);
        }

        for (int i = 0; i < level; ++i) {
            str = str.append("\t");
        }
        str = str.append(std::to_string(node->m_data.val)).append("\n");

        if (node->m_left != nullptr) {
            printNodePretty(node->m_left, str, level_offset, level + 1);
        }
    }

#endif // DS_DEBUG_LOG

    template <typename T>
    void BinaryTree<T>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Tree: Addr:0x%p", (void*)this);
        std::string str;
        printNodePretty(m_root, str);
        X_DEBUG_COMMENT("\n%s", str.c_str());
        str.clear();
#endif // DS_DEBUG_LOG
    }
}

#endif //DSBINARYTREE_INL
