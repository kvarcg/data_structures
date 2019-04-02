#ifndef DSARRAY_INL
#define DSARRAY_INL

namespace DS {

    template <typename T, std::size_t N>
    typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
#ifdef DS_EXCEPTION_HANDLING
        if (pos >= N) {
            throw std::out_of_range("Array::at: Out of range");
        }
#endif
        return m_data[pos];
    }

    template <typename T, std::size_t N>
    typename Array<T, N>::const_reference Array<T, N>::at(size_type pos) const {
#ifdef DS_EXCEPTION_HANDLING
        if (pos >= N) {
            throw std::out_of_range("Array::at: Out of range");
        }
#endif
        return m_data[pos];
    }

    template <typename T, std::size_t N>
    void Array<T, N>::fill(const_reference value) noexcept {
        for (size_type i = 0; i < size(); ++i) {
            m_data[i] = value;
        }
    }

    template <typename T, std::size_t N>
    void Array<T, N>::print() const {
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Addr:0x%p, Size: %d, Capacity: %d, First: 0x%p (%d)", (void*)this, size(),
            (void*)m_data, size() > 0 ? m_data[size() - 1].val : 0);
        std::string str;
        for (size_t i = 0; i < size(); ++i) {
            str = str.append(std::to_string(m_data[i].val));
            str = str.append("->");
        }
        str = str.append("[]");
        X_DEBUG_COMMENT("Array: %s", str.c_str());
#endif // DS_DEBUG_LOG
    }

}  // namespace DS

#endif //DSARRAY_H
