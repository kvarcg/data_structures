#ifndef DSQUEUE_INL
#define DSQUEUE_INL

namespace DS {

    template <typename T>
    Queue<T>::~Queue() {
        destroy();
    }

    template <typename T>
    Queue<T>::Queue(const Queue<T>& other) {
        clone(*this, other);
    }

    template <typename T>
    Queue<T>& Queue<T>::operator =(const Queue<T>& other) {
        if (this != &other) {
            clone(*this, other);
        }
        return *this;
    }

    template <typename T>
    void Queue<T>::clone(Queue<T>& newcontainer, const Queue<T>& oldcontainer) {
        // create a temp list to clone
        node_type* copy_node = my_new node_type(*oldcontainer.m_front);
        node_type* copy_front_node = copy_node;
        node_type* copy_back_node = nullptr;

        // traverse the old list from the front
        node_type* node = oldcontainer.m_front;
        while (node != nullptr) {
            node = node->m_prev;

            // if there is a next pointer, clone it to the copy list and advance
            if (node != nullptr) {
                copy_node->m_prev = my_new node_type(*node);
                copy_node = copy_node->m_prev;
            }

            // store the back as well
            copy_back_node = copy_node;
        }

        // once everything is done, set the temp list as the new one
        newcontainer.m_front = copy_front_node;
        newcontainer.m_back = copy_back_node;
    }

    template <typename T>
    void Queue<T>::destroy() {
        node_type* node = m_front;
        while (node != nullptr) {
            // store current node as temp (to delete)
            node_type* tmp_node = node;
            // advance
            node = node->m_prev;
            // delete the stored node
            XE_SAFE_DELETE(tmp_node);
        }
        m_front = nullptr;
        m_back = nullptr;
    }

    template <typename T>
    void Queue<T>::push(const T& val)
    {

        // create new node
        node_type* node = my_new node_type(val);

        // if the list is empty, set front and back as the same
        if (m_back == nullptr) {
            m_back = m_front = node;
            return;
        }

        // set the old back to contain the new node
        m_back->m_prev = node;

        // set the new node as back
        m_back = node;
    }

    template <typename T>
    void Queue<T>::pop() {
        // empty queue
        if (m_front == nullptr) {
            return;
        }

        // store the node to pop from the front
        node_type* node = m_front;

        // update the new front with the prev
        m_front = m_front->m_prev;

        // if the list becomes empty, update the back pointer as well
        if (m_front == nullptr) {
            m_back = nullptr;
        }

        // remove the node
        XE_SAFE_DELETE(node);
    }

    template <typename T>
    void Queue<T>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Addr:0x%p, Back addr 0x%p (%d), Front addr 0x%p (%d)", (void*)this, (void*)m_back, m_back != nullptr ? m_back->m_data.val : 0, (void*)m_front, m_front != nullptr ? m_front->m_data.val : 0);
        std::string str;
        node_type* node = m_front;
        while (node != nullptr) {
            str = str.append(std::to_string(node->m_data.val));
            str = str.append("->");
            node = node->m_prev;
        }
        str = str.append("[]");
        X_DEBUG_COMMENT("Queue (Front to Back): %s", str.c_str());
#endif // DS_DEBUG_LOG
    }
}

#endif //DSQUEUE_INL
