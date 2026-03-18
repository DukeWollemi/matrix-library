//
// Created by oelshora on 21/01/2026.
//

#ifndef MATRIX_LIBRARY_MATRIX_H
#define MATRIX_LIBRARY_MATRIX_H

#include <iosfwd>
#include <initializer_list>
#include <cstddef>
#include <algorithm>
#include <ostream>
#include <istream>
#include <stdexcept>

template<typename T>
class Matrix {
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = T *;
    using reference = T &;
    using const_pointer = const T *;
    using const_reference = const T &;

    // Default constructor
    Matrix() noexcept = default;

    // Constructor with size
    Matrix(size_type rows, size_type cols);

    // Matrix with value
    Matrix(size_type rows, size_type cols, const T &value);

    // Matrix with an Initializer list
    Matrix(std::initializer_list<std::initializer_list<T> > init);

    // Destructor
    ~Matrix();

    // Copy constructor
    Matrix(const Matrix &other);

    // Copy assignment
    Matrix &operator=(const Matrix &other);

    // Move constructor
    Matrix(Matrix &&other) noexcept;

    // Move assignment
    Matrix &operator=(Matrix &&other) noexcept;

    // Swap utility
    void swap(Matrix &other) noexcept;

    friend void swap(Matrix &m1, Matrix &m2) noexcept { m1.swap(m2); }

    // Observers
    [[nodiscard]] size_type rows() const noexcept;

    [[nodiscard]] size_type cols() const noexcept;

    [[nodiscard]] size_type size() const noexcept;

    [[nodiscard]] bool empty() const noexcept;

    // Raw access to contiguous storage
    pointer data() noexcept;

    const_pointer data() const noexcept;

    // Pointer to first element of row r
    pointer row_data(size_type r) noexcept;

    const_pointer row_data(size_type r) const noexcept;

    // Element access
    reference operator()(size_type r, size_type c);

    const_reference operator()(size_type r, size_type c) const;

    // Checked access
    reference at(size_type r, size_type c);

    const_reference at(size_type r, size_type c) const;

    // Modifiers
    Matrix &fill(const_reference value);

    // Reset to 0x0 and release storage
    void clear() noexcept;

    // Swap row/column
    void swap_rows(size_type r1, size_type r2);

    void swap_cols(size_type c1, size_type c2);

    // Transpose
    // - transpose_in_place(): only valid for square matrices (otherwise throws).
    // - transposed(): returns a new transposed matrix (always valid).
    void transpose_in_place();

    [[nodiscard]] Matrix transposed() const;

    // Arithmetic operators
    // Dimensions must match; on mismatch throw error
    [[nodiscard]] Matrix operator+(const Matrix &other) const;

    [[nodiscard]] Matrix operator-(const Matrix &other) const;

    [[nodiscard]] Matrix operator*(const Matrix &other) const;

    Matrix &operator+=(const Matrix &other);

    Matrix &operator-=(const Matrix &other);

    Matrix &operator*=(Matrix &scalar);

    // Scalar operations (non-members)
    friend Matrix operator*(const Matrix &m, const Matrix &scalar);

    friend Matrix operator*(const Matrix &scalar, const Matrix &m);

    // Comparisons
    [[nodiscard]] bool operator==(const Matrix &other) const noexcept;

    [[nodiscard]] bool operator!=(const Matrix &other) const noexcept;

    // Iteration
    pointer begin() noexcept;

    pointer end() noexcept;

    const_pointer begin() const noexcept;

    const_pointer end() const noexcept;

    const_pointer cbegin() const noexcept;

    const_pointer cend() const noexcept;

    // I/O — only declared here; defined below as free templates
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &m);

    template<typename U>
    friend std::istream &operator>>(std::istream &is, Matrix<U> &m);

private:
    [[nodiscard]] size_type index(size_type r, size_type c) const noexcept;

    size_type m_rows{ 0 };
    size_type m_cols{ 0 };
    pointer m_data{ nullptr };
};

#endif //MATRIX_LIBRARY_MATRIX_H

// Constructor / destructor implementations

template<typename T>
Matrix<T>::Matrix(size_type rows, size_type cols)
	: m_rows{rows},
    m_cols{cols},
    m_data{(rows == 0 || cols == 0) ? nullptr : new T[rows * cols]} {
}

template<typename T>
Matrix<T>::Matrix(size_type rows, size_type cols, const T &value)
    : m_rows{rows},
    m_cols{cols},
    m_data{(rows == 0 || cols == 0) ? nullptr : new T[rows * cols]} {
    const size_type count {m_rows * m_cols};
    for (size_type i {0}; i < count; ++i) {
        m_data[i] = value;
    }
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init)
    : m_rows{init.size()},
    m_cols{(m_rows > 0) ? init.begin()->size() : 0},
    m_data{ nullptr } {
    const size_type count{m_rows * m_cols};

    for (const auto& row : init) {
        if (row.size() != m_cols) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
    }

    if (count == 0) {
        return;
    }

    m_data = new T[count];

    size_type destination{0};
    for (const auto& row : init) {
        for (const auto& value : row) {
            m_data[destination++] = value;
        }
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] m_data;
}

template<typename T>
Matrix<T>::Matrix(const Matrix &other)
    : m_rows{ other.m_rows }, m_cols{ other.m_cols }, m_data{ nullptr } {

    const size_type count{m_rows * m_cols};

    if (count > 0) {
        m_data = new T[count];

        for (size_type i{0}; i < count; ++i) {
            m_data[i] = other.m_data[i];
        }
    }
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) {
        Matrix temp{other};
        swap(temp);
    }

    return *this;
}

template<typename T>
Matrix<T>::Matrix(Matrix &&other) noexcept
    : m_rows{other.m_rows}, m_cols{other.m_cols}, m_data{other.m_data} {
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_data = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix &&other) noexcept {
    if (this != &other) {
        delete[] m_data;

        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = other.m_data;

        other.m_rows = 0;
        other.m_cols = 0;
        other.m_data = nullptr;
    }
    return *this;
}

template<typename T>
void Matrix<T>::swap(Matrix &other) noexcept {
    std::swap(m_rows, other.m_rows);
    std::swap(m_cols, other.m_cols);
    std::swap(m_data, other.m_data);
}

