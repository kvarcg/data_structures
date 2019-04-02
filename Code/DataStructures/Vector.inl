#ifndef DSVECTOR_INL
#define DSVECTOR_INL

namespace DS {

    template <typename T>
    Vector<T>::Vector(size_type count) {
        m_impl.m_capacity = count;
        if (m_impl.m_capacity > 0) {
            m_impl.m_data = static_cast<T*>(m_allocator.allocate(m_impl.m_capacity));
            insert(begin(), count, T());
        }
    }

    template <typename T>
    Vector<T>::~Vector(void) {
        if (m_impl.m_capacity > 0) {
            destroy(m_impl.m_data, m_impl.m_size);
            m_allocator.deallocate(m_impl.m_data, m_impl.m_capacity);
        }
    }

    template <typename T>
    void Vector<T>::clone(VectorImpl& newdata, const VectorImpl& olddata) {
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
    Vector<T>::Vector(const Vector& other) {
        VectorImpl tmp_impl;
        clone(tmp_impl, other.m_impl);
        std::swap(m_impl, tmp_impl);
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector& other) {
        if (this != &other) {
            VectorImpl tmp_impl;
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
    void Vector<T>::reallocate(size_type capacity) {
        VectorImpl old_impl;
        old_impl.m_data = m_impl.m_data;
        old_impl.m_size = m_impl.m_size;
        old_impl.m_capacity = capacity;
        VectorImpl tmp_impl;
        clone(tmp_impl, old_impl);
        std::swap(m_impl, tmp_impl);

        // delete the old data
        destroy(tmp_impl.m_data, tmp_impl.m_size);
        // deallocate the old data
        m_allocator.deallocate(tmp_impl.m_data, tmp_impl.m_capacity);
    }

    template <typename T>
    void Vector<T>::destroy(value_type* data, size_type size) {
        for (size_type i = 0; i < size; ++i) {
            m_allocator.destroy(&data[i]);
        }
    }

    template <typename T>
    typename Vector<T>::reference Vector<T>::at(size_type pos) {
#ifdef DS_EXCEPTION_HANDLING
        if (pos >= m_impl.m_size) {
            throw std::out_of_range("Vector::at: Out of range");
        }
#endif
        return m_impl.m_data[pos];
    }

    template <typename T>
    typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
#ifdef DS_EXCEPTION_HANDLING
        if (pos >= m_impl.m_size) {
            throw std::out_of_range("Vector::at: Out of range");
        }
#endif
        return m_impl.m_data[pos];
    }

    template <typename T>
    void Vector<T>::reserve(size_type new_cap) {
        if (new_cap > m_impl.m_capacity) {
            reallocate(new_cap);
        }
    }

    template <typename T>
    void Vector<T>::shrink_to_fit() {
        if (m_impl.m_size < m_impl.m_capacity) {
            reallocate(m_impl.m_size);
        }
    }

    template <typename T>
    void Vector<T>::clear() noexcept {
        destroy(m_impl.m_data, m_impl.m_size);
        m_impl.m_size = 0;
    }

    template <typename T>
    void Vector<T>::assign(size_type count, const T& value) {
        clear();

        // realloc if needed
        if (count > m_impl.m_capacity) {
            reallocate(count);
        }

        // now place the new elements at the requested positions
        for (size_type index = 0; index < count; ++index) {
            m_allocator.construct(&m_impl.m_data[index], value);
        }

        m_impl.m_size = count;
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_type count, const value_type& value) {
        ptrdiff_t new_elem_index = pos - begin();

        // realloc if needed
        if (m_impl.m_size + count > m_impl.m_capacity) {
            size_type new_cap = increaseCapacity(m_impl.m_capacity, count);
            reallocate(new_cap);
        }

        // shift the rest of the elements by N
        for (size_type index = m_impl.m_size - 1 + count; index >= new_elem_index + count; --index) {
            std::swap(m_impl.m_data[index], m_impl.m_data[index - count]);
        }

        // now place the new elements at the requested positions
        for (size_type index = new_elem_index; index < new_elem_index + count; ++index) {
            m_allocator.construct(&m_impl.m_data[index], value);
        }

        m_impl.m_size = m_impl.m_size + count;
        return iterator(&m_impl.m_data[new_elem_index]);
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last) {
        ptrdiff_t removed_elem_index = first - begin();
        ptrdiff_t count = last - first;

        if (removed_elem_index < 0) {
            return iterator(&m_impl.m_data[0]);
        }

        size_type removed_elem_index_uint = static_cast<size_type>(removed_elem_index);
        // erase the element at the requested position
        for (size_type index = removed_elem_index; index < removed_elem_index_uint + count; ++index) {
            m_impl.m_data[index].val = -111;
            m_allocator.destroy(&m_impl.m_data[index]);
        }

        // shift the rest of the elements by N
        for (size_type index = removed_elem_index_uint; index < m_impl.m_size - count; ++index) {
            std::swap(m_impl.m_data[index], m_impl.m_data[index + count]);
        }

        m_impl.m_size = m_impl.m_size - count;
        return iterator(&m_impl.m_data[removed_elem_index_uint + count]);
    }

    template <typename T>
    void Vector<T>::push_back(const value_type& value) {
        // realloc
        if (m_impl.m_size == m_impl.m_capacity) {
            reallocate(m_impl.m_capacity + 1);
        }
        insert(end(), 1, value);
    }

    template <typename T>
    void Vector<T>::pop_back(void) {
        if (m_impl.m_size == 0) {
            return;
        }
        erase(end() - 1, end());
    }

    template <typename T>
    void Vector<T>::resize(size_type count, const value_type& value) {
        // shrink
        if (count < m_impl.m_size) {
            erase(cbegin() + count, cend());
        }
        // grow
        else if (count > m_impl.m_size) {
            // reallocate if needed
            if (count > m_impl.m_capacity) {
                reallocate(count);
            }
            size_type new_data = count - m_impl.m_size;
            insert(cend(), new_data, value);
        }
    }

    template <typename T>
    void Vector<T>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Addr:0x%p, Size: %d, Capacity: %d, First: 0x%p (%d)", (void*)this, m_impl.m_size, m_impl.m_capacity,
            (void*)m_impl.m_data, m_impl.m_capacity, m_impl.m_size > 0 ? m_impl.m_data[m_impl.m_size - 1].val : 0);
        std::string str;
        for (size_t i = 0; i < m_impl.m_size; ++i) {
            str = str.append(std::to_string(m_impl.m_data[i].val));
            str = str.append("->");
        }
        str = str.append("[]");
        X_DEBUG_COMMENT("Vector: %s", str.c_str());
#endif // DS_DEBUG_LOG
    }
}

#endif //DSVECTOR_H
