#ifndef DSDOUBLELINKEDLIST_INL
#define DSDOUBLELINKEDLIST_INL

namespace DS {

    template <typename T>
    LinkedListDouble<T>::~LinkedListDouble() {
        destroy();
    }

    template <typename T>
    LinkedListDouble<T>::LinkedListDouble(const LinkedListDouble<T>& other) {
        clone(*this, other);
    }

    template <typename T>
    LinkedListDouble<T>& LinkedListDouble<T>::operator =(const LinkedListDouble<T>& other) {
        if (this != &other) {
            LinkedListDouble<T> tmp_container;
            clone(tmp_container, other);
            std::swap(m_head, tmp_container.m_head);
            std::swap(m_tail, tmp_container.m_tail);

            // destructor of tmp_container is called implicitly here
        }
        return *this;
    }

    template <typename T>
    LinkedListDouble<T> LinkedListDouble<T>::reverse()
    {
        LinkedListDouble<T> reversedlist(*this);

        node_type* current = reversedlist.m_head;
        node_type* next = nullptr;
        while (current != nullptr) {
            // store the correct next in temp
            next = current->m_next;
            // swap next and prev pointers
            std::swap(current->m_next, current->m_prev);
            // advance using the stored next (next to the old list)
            current = next;
        }

        // the tail of the reversed list is the head of the old one
        std::swap(reversedlist.m_tail, reversedlist.m_head);
        return reversedlist;
    }

    template <typename T>
    void LinkedListDouble<T>::clone(LinkedListDouble<T>& newcontainer, const LinkedListDouble<T>& oldcontainer) {

        if (oldcontainer.m_head == nullptr) {
            return;
        }

        // create a temp list to clone
        node_type* copy_node = my_new node_type(*oldcontainer.m_head);
        node_type* copy_head_node = copy_node;
        node_type* copy_tail_node = copy_node;

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

        // fix prev pointers (as they refer to the oldcontainer)
        node_type* current_prev = nullptr;
        copy_node = copy_head_node;
        while (copy_node != nullptr) {
            // advance and keep the prev pointer
            current_prev = copy_node;
            copy_node = copy_node->m_next;

            // set the prev to the stored temp
            if (copy_node != nullptr) {
                copy_node->m_prev = current_prev;
            }

            // keep the current tail
            copy_tail_node = current_prev;
        }

        // once everything is done, set the temp list as the new one
        newcontainer.m_head = copy_head_node;
        newcontainer.m_tail = copy_tail_node;
    }

    template <typename T>
    void LinkedListDouble<T>::destroy() {
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
        m_tail = nullptr;
    }

    template <typename T>
    typename LinkedListDouble<T>::node_type* LinkedListDouble<T>::find(const T & val)
    {
        node_type* node = m_head;
        while (node != nullptr && node->m_data != val) {
            node = node->m_next;
        }

        return node;
    }

    template <typename T>
    typename LinkedListDouble<T>::node_type* LinkedListDouble<T>::push_front(const T& val)
    {
        // create new node
        node_type* node = my_new node_type(val);

        // new node points to old head and old head points to new node
        node->m_next = m_head;
        if (m_head != nullptr) {
            m_head->m_prev = node;
        }

        // set new node as head
        m_head = node;

        // prev pointer remains null, as this is the new head
        node->m_prev = nullptr;

        // if single element, set tail
        if (m_head->m_next == nullptr) {
            m_tail = node;
        }

        return node;
    }

    template <typename T>
    void LinkedListDouble<T>::pop_front()
    {
        // if the list is empty, return
        if (m_head == nullptr) {
            return;
        }

        // store node
        node_type* node = m_head;

        // advance to the next
        m_head = m_head->m_next;

        // reset the prev pointer
        if (m_head != nullptr) {
            m_head->m_prev = nullptr;
        }

        // if empty, reset the tail as well
        if (m_head == nullptr) {
            m_tail = nullptr;
        }

        XE_SAFE_DELETE(node);
    }

    template <typename T>
    typename LinkedListDouble<T>::node_type* LinkedListDouble<T>::push_back(const T& val)
    {
        // if the list is empty, just add one element
        if (m_head == nullptr) {
            return push_front(val);
        }

        // create new node
        node_type* node = new node_type(val);

        // set new element as last
        node->m_next = nullptr;

        // set the prev of the new last element to point to the current tail
        node->m_prev = m_tail;

        // set the next of the (up to now) last element as the new node
        m_tail->m_next = node;

        // set the new node as tail
        m_tail = node;

        return node;
    }

    template <typename T>
    void LinkedListDouble<T>::pop_back()
    {
        // if the list is empty, return
        // if single element call pop_front (O(1))
        if (m_head == nullptr || m_head->m_next == nullptr) {
            pop_front();
            return;
        }

        // store node
        node_type* node = m_tail;

        // set prev element to point to empty
        m_tail->m_prev->m_next = nullptr;

        // set the new node as tail
        m_tail = m_tail->m_prev;

        // delete the node
        XE_SAFE_DELETE(node);
    }

    template <typename T>
    typename LinkedListDouble<T>::node_type* LinkedListDouble<T>::insert_after(node_type* prev_node, const T& val)
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

        // set the prev of the new node to the previous node
        node->m_prev = prev_node;

        // set next of the previous node to the new node (append)
        prev_node->m_next = node;

        // also set the prev of the next node to point to the new node
        if (node->m_next != nullptr) {
            node->m_next->m_prev = node;
        }

        // if the new element points to nothing, set it as tail
        if (node->m_next == nullptr) {
            m_tail = node;
        }

        return node;
    }

    template <typename T>
    void LinkedListDouble<T>::erase(node_type* node) {
        // if the list is empty, return
        // if single element call pop_front (O(1))
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
        // set prev of next element to point to the node before the deleted one
        if (node->m_next != nullptr) {
            node->m_next->m_prev = node_to_remove_prev;
        }

        // if we removed the tail, assign a new one
        if (m_tail == node) {
            m_tail = node->m_prev;
        }

        // delete the node
        XE_SAFE_DELETE(node);
    }

    template <typename T>
    void LinkedListDouble<T>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Addr:0x%p, Head addr: 0x%p (%d), Tail addr: 0x%p (%d)", (void*)this, (void*)m_head, m_head != nullptr ? m_head->m_data.val : 0, (void*)m_tail, m_tail != nullptr ? m_tail->m_data.val : 0);
        std::string str;
        node_type* node = m_head;
        while (node != nullptr) {
            str = str.append(std::to_string(node->m_data.val));
            str = str.append("->");
            node = node->m_next;
        }
        str = str.append("[]");
        X_DEBUG_COMMENT("Head: %s", str.c_str());

        str.clear();
        node = m_tail;
        while (node != nullptr) {
            str = str.append(std::to_string(node->m_data.val));
            str = str.append("->");
            node = node->m_prev;
        }
        str = str.append("[]");
        X_DEBUG_COMMENT("Tail: %s", str.c_str());
#endif // DS_DEBUG_LOG
    }
}

#endif //DSDOUBLELINKEDLIST_INL
