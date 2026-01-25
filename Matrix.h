//
// Created by oelshora on 21/01/2026.
//

#ifndef MATRIX_LIBRARY_MATRIX_H
#define MATRIX_LIBRARY_MATRIX_H

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <algorithm>

template<typename T>
class Matrix {
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;

    // Default constructor
    Matrix() noexcept = default;

    // Constructor with size
    explicit Matrix(size_type rows, size_type cols);

    // Matrix with value
    Matrix(size_type rows, size_type cols, const T& value);

    // Matrix with an Initializer list
    Matrix(std::initializer_list<std::initializer_list<T>> init);

    // Destructor
    ~Matrix();

    // Copy constructor
    Matrix(const Matrix& other);

    // Copy assignment
    Matrix& operator=(const Matrix& other);

    // Move constructor
    Matrix(Matrix&& other) noexcept;

    // Move assignment
    Matrix& operator=(Matrix&& other) noexcept;

    // Swap utility
    void swap(Matrix& other) noexcept;

    friend void swap(Matrix& m1, Matrix& m2) noexcept { m1.swap(m2); }

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
    const const_pointer row_data(size_type r) const noexcept;

    // Element access
    reference operator()(size_type r, size_type c);
    const_reference operator()(size_type r, size_type c) const;

    // Checked access
    reference at(size_type r, size_type c);
    const_reference at(size_type r, size_type c) const;

    // Modifiers
    void fill(const_reference value);

    // Reset to 0x0 and release storage
    void clear() noexcept;

    // Resize
    void resize(size_type rows, size_type cols);

    // Swap row/column
    void swap_rows(size_type r1, size_type r2);
    void swap_cols(size_type c1, size_type c2);

    // Transpose
    // - transpose_in_place(): only valid for square matrices (otherwise throws).
    // - transposed(): returns a new transposed matrix (always valid).
    void transpose_in_place();
    [[nodiscard]] Matrix transposed() const;

    // Arthimetic operators
    // Dimensions must match; on mismatch throw error
    [[nodiscard]] Matrix operator+(const Matrix& other) const;
    [[nodiscard]] Matrix operator-(const Matrix& other) const;
    [[nodiscard]] Matrix operator*(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const_reference scalar);

    // Scalar operations (non-members)
    friend Matrix operator*(const Matrix& m, const_reference scalar);
    friend Matrix operator*(const_reference scalar, const Matrix& m);

    // Comparisons
    [[nodiscard]] bool operator==(const Matrix& other) const noexcept;
    [[nodiscard]] bool operator!=(const Matrix& other) const;

    // Iteration
    pointer begin() noexcept;
    pointer end() noexcept;
    const_pointer begin() const noexcept;
    const_pointer end() const noexcept;
    const_pointer cbegin() const noexcept;
    const_pointer cend() const noexcept;

    // I/O
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& m);

private:
    [[nodiscard]] size_type index(size_type r, size_type c) const noexcept;

    size_type m_rows{0};
    size_type m_cols{0};
    T* m_data{nullptr};
};

#endif //MATRIX_LIBRARY_MATRIX_H