#ifndef DSLINKEDLIST_INL
#define DSLINKEDLIST_INL

namespace DS {

    template <typename T>
    LinkedList<T>::~LinkedList() {
        destroy();
    }

    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& other) {
        clone(*this, other);
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T>& other) {
        if (this != &other) {
            LinkedList<T> tmp_container;
            clone(tmp_container, other);
            std::swap(m_head, tmp_container.m_head);

            // destructor of tmp_container is called implicitly here
        }
        return *this;
    }

    template <typename T>
    LinkedList<T> LinkedList<T>::reverse()
    {
        LinkedList<T> reversedlist(*this);

        node_type* current = reversedlist.m_head;
        node_type* prev = nullptr;
        node_type* next = nullptr;
        while (current != nullptr) {
            // store the correct next in temp
            next = current->m_next;
            // set the next to point to prev
            current->m_next = prev;
            // set prev (for the next iteration) to the current node
            prev = current;
            // advance using the stored next (next to the old list)
            current = next;
        }

        reversedlist.m_head = prev;
        return reversedlist;
    }

    template <typename T>
    void LinkedList<T>::clone(LinkedList<T>& newcontainer, const LinkedList<T>& oldcontainer) {

        if (oldcontainer.m_head == nullptr) {
            return;
        }

        // create a temp list to clone
        node_type* copy_node = my_new node_type(*oldcontainer.m_head);
        node_type* copy_head_node = copy_node;

        // traverse the old list
        node_type* node = oldcontainer.m_head;
        while (node != nullptr) {
            node = node->m_next;

            // if there is a next pointer, clone it to the copy list and advance
            if (node != nullptr) {
                copy_node->m_next = my_new node_type(*node);
                copy_node = copy_node->m_next;
            }
        }

        // once everything is done, set the temp list as the new one
        newcontainer.m_head = copy_head_node;
    }

    template <typename T>
    void LinkedList<T>::destroy() {
        node_type* node = m_head;
        while (node != nullptr) {
            // store current node as temp (to delete)
            node_type* tmp_node = node;
            // advance
            node = node->m_next;
            // delete the stored node
            XE_SAFE_DELETE(tmp_node);
        }
        m_head = nullptr;
    }

    template <typename T>
    typename LinkedList<T>::node_type* LinkedList<T>::find(const T & val)
    {
        node_type* node = m_head;
        while (node != nullptr && node->m_data != val) {
            node = node->m_next;
        }

        return node;
    }

    template <typename T>
    typename LinkedList<T>::node_type* LinkedList<T>::push_front(const T& val)
    {
        // create new node
        node_type* node = my_new node_type(val);

        // new node points to old head
        node->m_next = m_head;

        // set new node as head
        m_head = node;

        return node;
    }

    template <typename T>
    void LinkedList<T>::pop_front()
    {
        // if the list is empty, return
        if (m_head == nullptr) {
            return;
        }

        // store node
        node_type* node = m_head;

        // advance to the next
        m_head = m_head->m_next;

        XE_SAFE_DELETE(node);
    }

    template <typename T>
    typename LinkedList<T>::node_type* LinkedList<T>::push_back(const T& val)
    {
        // if the list is empty, just add one element
        if (m_head == nullptr) {
            return push_front(val);
        }

        // traverse the list to the last element
        node_type* tail = m_head;
        while (tail->m_next != nullptr) {
            tail = tail->m_next;
        }

        // create new node
        node_type* node = my_new node_type(val);

        // set new element as last
        node->m_next = nullptr;

        // set the next of the (up to now) last element as the new node
        tail->m_next = node;

        return node;
    }

    template <typename T>
    void LinkedList<T>::pop_back()
    {
        // if the list is empty, return
        // if single element call pop_front (O(1))
        if (m_head == nullptr || m_head->m_next == nullptr) {
            pop_front();
            return;
        }

        // traverse the list to the last element
        node_type* tail = m_head;
        node_type* tail_prev = nullptr;
        while (tail->m_next != nullptr) {
            tail_prev = tail;
            tail = tail->m_next;
        }

        // store node
        node_type* node = tail;

        // set prev element to point to empty
        tail_prev->m_next = nullptr;

        // delete the node
        XE_SAFE_DELETE(node);
    }

    template <typename T>
    typename LinkedList<T>::node_type* LinkedList<T>::insert_after(node_type* prev_node, const T& val)
    {
        // if the prev_node is null, return
        if (prev_node == nullptr) {
            return nullptr;
        }

        // if the list is empty, just add one element
        if (m_head == nullptr) {
            return push_front(val);
        }

        // create new node
        node_type* node = my_new node_type(val);

        // set the next of the new node to what the previous node was pointing to
        node->m_next = prev_node->m_next;

        // set next of the previous node to the new node (append)
        prev_node->m_next = node;

        return node;
    }

    template <typename T>
    void LinkedList<T>::erase(node_type* node) {
        // if the list is empty, just add one element
        // if removing head pop_front (O(1))
        if (m_head == nullptr || m_head->m_next == nullptr) {
            pop_front();
            return;
        }

        // traverse the list to the requested node
        node_type* node_to_remove = m_head;
        node_type* node_to_remove_prev = nullptr;
        while (node_to_remove != node) {
            node_to_remove_prev = node_to_remove;
            node_to_remove = node_to_remove->m_next;
        }

        // if not found, return
        if (node_to_remove == nullptr) {
            return;
        }

        // set next of previous element to point to the node after the deleted one
        node_to_remove_prev->m_next = node->m_next;

        // delete the node
        XE_SAFE_DELETE(node);
    }

    template <typename T>
    void LinkedList<T>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Addr:0x%p, Head addr 0x%p (%d)", (void*)this, (void*)m_head, m_head != nullptr ? m_head->m_data.val : 0);
        std::string str;
        node_type* node = m_head;
        while (node != nullptr) {
            str = str.append(std::to_string(node->m_data.val));
            str = str.append("->");
            node = node->m_next;
        }
        str = str.append("[]");
        X_DEBUG_COMMENT("Head: %s", str.c_str());
#endif // DS_DEBUG_LOG
    }
}

#endif //DSLINKEDLIST_INL
