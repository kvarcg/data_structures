#ifndef DSSTACK_INL
#define DSSTACK_INL

namespace DS {

    template <typename T>
    StackArray<T>::StackArray(size_type count) {
        m_impl.m_capacity = count;
        if (m_impl.m_capacity > 0) {
            m_impl.m_data = static_cast<T*>(m_allocator.allocate(m_impl.m_capacity));
        }
    }

    template <typename T>
    StackArray<T>::~StackArray() {
        if (m_impl.m_capacity > 0) {
            destroy(m_impl.m_data, m_impl.m_size);
            m_allocator.deallocate(m_impl.m_data, m_impl.m_capacity);
        }
    }

    template <typename T>
    void StackArray<T>::clone(StackArrayImpl& newdata, const StackArrayImpl& olddata) {
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

    template <typename T>
    StackArray<T>::StackArray(const StackArray<T>& other) {
        StackArrayImpl tmp_impl;
        clone(tmp_impl, other.m_impl);
        std::swap(m_impl, tmp_impl);
    }

    template <typename T>
    StackArray<T>& StackArray<T>::operator =(const StackArray<T>& other) {
        if (this != &other) {
            StackArrayImpl tmp_impl;
            clone(tmp_impl, other.m_impl);
            std::swap(m_impl, tmp_impl);

            // delete the old data
            destroy(tmp_impl.m_data, tmp_impl.m_size);
            // deallocate the old data
            m_allocator.deallocate(tmp_impl.m_data, tmp_impl.m_capacity);
        }
        return *this;
    }

    template <typename T>
    void StackArray<T>::reallocate(size_type capacity) {
        StackArrayImpl old_impl;
        old_impl.m_data = m_impl.m_data;
        old_impl.m_size = m_impl.m_size;
        old_impl.m_capacity = capacity;
        StackArrayImpl tmp_impl;
        clone(tmp_impl, old_impl);
        std::swap(m_impl, tmp_impl);

        // delete the old data
        destroy(tmp_impl.m_data, tmp_impl.m_size);
        // deallocate the old data
        m_allocator.deallocate(tmp_impl.m_data, tmp_impl.m_capacity);
    }

    template <typename T>
    void StackArray<T>::destroy(value_type* data, size_type size) {
        for (size_type i = 0; i < size; ++i) {
            m_allocator.destroy(&data[i]);
        }
    }

    template <typename T>
    void StackArray<T>::push(const T& val)
    {
        // realloc
        if (m_impl.m_size == m_impl.m_capacity) {
            reallocate(m_impl.m_capacity + 1);
        }

        m_allocator.construct(&m_impl.m_data[m_impl.m_size++], val);
    }

    template <typename T>
    void StackArray<T>::pop(void) {
        if (m_impl.m_size == 0) {
            return;
        }
        m_allocator.destroy(&m_impl.m_data[m_impl.m_size - 1]);
        m_impl.m_size--;
    }

    template <typename T>
    void StackArray<T>::reserve(size_type new_cap) {
        if (new_cap > m_impl.m_capacity) {
            reallocate(new_cap);
        }
    }

    template <typename T>
    void StackArray<T>::shrink_to_fit() {
        if (m_impl.m_size < m_impl.m_capacity) {
            reallocate(m_impl.m_size);
        }
    }

    template <typename T>
    void StackArray<T>::clear() noexcept {
        destroy(m_impl.m_data, m_impl.m_size);
        m_impl.m_size = 0;
    }

    template <typename T>
    void StackArray<T>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Addr:0x%p, Size: %d, Capacity: %d, Front: 0x%p (%d)", (void*)this, m_impl.m_size, m_impl.m_capacity,
            (void*)m_impl.m_data, m_impl.m_size > 0 ? m_impl.m_data[m_impl.m_size - 1].val : 0);
        std::string str;
        for (size_t i = 0; i < m_impl.m_size; ++i) {
            str = str.append(std::to_string(m_impl.m_data[i].val));
            str = str.append("->");
        }
        str = str.append("[]");
        X_DEBUG_COMMENT("Stack (Back To Front): %s", str.c_str());
#endif // DS_DEBUG_LOG
    }
}

#endif //DSSTACK_H
