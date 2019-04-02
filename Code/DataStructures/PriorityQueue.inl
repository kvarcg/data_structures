#ifndef DSPRIORITYQUEUE_INL
#define DSPRIORITYQUEUE_INL

namespace DS {
    template <typename T, bool isMin>
    PriorityQueue<T, isMin>::PriorityQueue(size_type capacity) {
        m_impl.m_capacity = capacity;
        if (m_impl.m_capacity > 0) {
            m_impl.m_data = static_cast<T*>(m_allocator.allocate(m_impl.m_capacity));
        }
    }

    template <typename T, bool isMin>
    PriorityQueue<T, isMin>::~PriorityQueue(void) {
        if (m_impl.m_capacity > 0) {
            destroy(m_impl.m_data, m_impl.m_size);
            m_allocator.deallocate(m_impl.m_data, m_impl.m_capacity);
        }
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::clone(PriorityQueueImpl& newdata, const PriorityQueueImpl& olddata) {
        // create all data to temp
        size_t tmp_size = olddata.m_size;
        size_t tmp_capacity = olddata.m_capacity;
        T* tmp_data = nullptr;
        if (tmp_capacity > 0) {
            tmp_data = static_cast<T*>(m_allocator.allocate(tmp_capacity));
            for (size_t i = 0; i < tmp_size; ++i) {
                m_allocator.construct(&tmp_data[i], olddata.m_data[i]);
            }
        }

        // once this has finished successfully, assign the data
        newdata.m_capacity = tmp_capacity;
        newdata.m_size = tmp_size;
        newdata.m_data = tmp_data;
    }


    template <typename T, bool isMin>
    PriorityQueue<T, isMin>::PriorityQueue(const PriorityQueue& other) {
        PriorityQueueImpl tmp_impl;
        clone(tmp_impl, other.m_impl);
        std::swap(m_impl, tmp_impl);
    }

    template <typename T, bool isMin>
    PriorityQueue<T, isMin>& PriorityQueue<T, isMin>::operator=(const PriorityQueue& other) {
        if (this != &other) {
            PriorityQueueImpl tmp_impl;
            clone(tmp_impl, other.m_impl);
            std::swap(m_impl, tmp_impl);

            // delete the old data
            destroy(tmp_impl.m_data, tmp_impl.m_size);
            // deallocate the old data
            m_allocator.deallocate(tmp_impl.m_data, tmp_impl.m_capacity);
        }

        return *this;
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::reallocate(size_type capacity) {
        PriorityQueueImpl old_impl;
        old_impl.m_data = m_impl.m_data;
        old_impl.m_size = m_impl.m_size;
        old_impl.m_capacity = capacity;
        PriorityQueueImpl tmp_impl;
        clone(tmp_impl, old_impl);
        std::swap(m_impl, tmp_impl);

        // delete the old data
        destroy(tmp_impl.m_data, tmp_impl.m_size);
        // deallocate the old data
        m_allocator.deallocate(tmp_impl.m_data, tmp_impl.m_capacity);
    }

    template <typename T, bool isMin>
    typename PriorityQueue<T, isMin>::size_type PriorityQueue<T, isMin>::height(size_type index) {

        if (index >= m_impl.m_size) {
            return 0;
        }

        size_type left_height = height(left(index)) + 1;
        size_type right_height = height(right(index)) + 1;

        return left_height > right_height ? left_height : right_height;
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::destroy(value_type* data, size_type size) {
        for (size_type i = 0; i < size; ++i) {
            m_allocator.destroy(&data[i]);
        }
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::reserve(size_type new_cap) {
        if (new_cap > m_impl.m_capacity) {
            reallocate(new_cap);
        }
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::shrink_to_fit() {
        if (m_impl.m_size < m_impl.m_capacity) {
            reallocate(m_impl.m_size);
        }
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::clear() noexcept {
        destroy(m_impl.m_data, m_impl.m_size);
        m_impl.m_size = 0;
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::heapify_down(size_type index)
    {
        T* parent = &m_impl.m_data[index];
        T* candidate_child = parent;
        size_type candidate_index = index;

        // initialize children data (for code clarity)
        size_type left_index = left(index);
        size_type right_index = right(index);
        T* left_child = nullptr;
        T* right_child = nullptr;
        if (has_left(index)) {
            left_child = &m_impl.m_data[left_index];
        }
        if (has_right(index)) {
            right_child = &m_impl.m_data[right_index];
        }

        // find smaller "ordered" child
        if (has_left(index) && !isBefore(candidate_child, left_child)) {
            candidate_child = left_child;
            candidate_index = left_index;
        }
        if (has_right(index) && !isBefore(candidate_child, right_child)) {
            candidate_child = right_child;
            candidate_index = right_index;
        }

        // recursively move downwards by swapping parent and current element
        if (candidate_index != index) {
            std::swap(*parent, *candidate_child);
            heapify_down(candidate_index);
        }
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::heapify_up(size_type index)
    {
        if (index == 0) {
            return;
        }

        // initialize data
        size_type parent_index = parent(index);
        T* parent = &m_impl.m_data[parent_index];
        T* current_child = &m_impl.m_data[index];

        // recursively move upwards by swapping parent and current element
        if (!isBefore(parent, current_child)) {
            std::swap(*parent, *current_child);
            heapify_up(parent_index);
        }
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::push(const value_type& value) {
        // realloc
        if (m_impl.m_size == m_impl.m_capacity) {
            m_impl.m_capacity = increaseCapacity(m_impl.m_capacity, 1);
            reallocate(m_impl.m_capacity);
        }

        // insert a new element at the end of the array
        m_allocator.construct(&m_impl.m_data[m_impl.m_size], value);
        ++m_impl.m_size;

        // call heapify up to recursively place the new element at its ordered place
        heapify_up(m_impl.m_size - 1);
    }

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::pop(void) {

        if (m_impl.m_size == 0) {
            return;
        }

        // replace the root with the last element to invalidate the heap
        T* current_root = &m_impl.m_data[0];
        T* last_element = &m_impl.m_data[m_impl.m_size - 1];
        std::swap(*current_root, *last_element);

        // fix the array size (old element is now ghost)
        m_impl.m_size--;

        // call heapify down to recursively place the new root at its ordered place
        heapify_down(0);

        // destroy the popped element
        m_allocator.destroy(&m_impl.m_data[m_impl.m_size]);
    }

#ifdef DS_DEBUG_LOG
    template <typename T, bool isMin>
    bool PriorityQueue<T, isMin>::validateHeap(size_type index) const
    {
        bool validated = true;

        if (m_impl.m_size <= 1 || index >= m_impl.m_size) {
            return validated;
        }

        const value_type* parent = &m_impl.m_data[index];

        // check children first (to early exit)
        if (has_left(index)) {
            validated = isBefore(parent, &m_impl.m_data[left(index)]);
        }
        if (validated && has_right(index)) {
            validated = isBefore(parent, &m_impl.m_data[right(index)]);
        }

        // recurse
        if (validated && has_left(index)) {
            validated = validateHeap(left(index));
        }

        if (validated && has_right(index)) {
            validated = validateHeap(right(index));
        }

        return validated;
    }

    template <typename T, bool isMin>
        void PriorityQueue<T, isMin>::printPretty(size_type index, std::string& str, int level) const {

            if (m_impl.m_size == 0) {
                return;
            }

            if (has_right(index)) {
                printPretty(right(index), str, level + 1);
            }

            for (int i = 0; i < level; ++i) {
                str = str.append("\t");
            }
            str = str.append(std::to_string(m_impl.m_data[index].val)).append("\n");

            if (has_left(index)) {
                printPretty(left(index), str, level + 1);
            }
        }
#endif // DS_DEBUG_LOG

    template <typename T, bool isMin>
    void PriorityQueue<T, isMin>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Addr:0x%p, Size: %d, Capacity: %d", (void*)this, m_impl.m_size, m_impl.m_capacity);
        std::string str;
        printPretty(0, str, 0);
        X_DEBUG_COMMENT("PriorityQueue:\n%s", str.c_str());
#endif // DS_DEBUG_LOG
    }
}

#endif //DSPRIORITYQUEUE_INL
