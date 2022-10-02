/**
 * @file vec.h
 * @author PANFACTORY (github/PANFACTORY)
 * @brief Definition and implementation of linear algebraic vector class
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <cassert>
#include <cmath>
#include <iostream>

#include "mat.h"

namespace PANSFE {
template <class T>
class Mat;

/**
 * @brief Linear algebraic vector class
 *
 * @tparam T Type of element
 */
template <class T>
class Vec {
    template <class U>
    friend std::ostream &operator<<(std::ostream &_out, const Vec<U> &_vec);
    template <class U>
    friend Vec<U> operator*(U _a, const Vec<U> &_vec);

    template <class U>
    friend class Mat;

   public:
    /**
     * @brief Construct a new Vec object whose size is zero.
     *
     */
    Vec() {
        this->size = 0;
        this->values = nullptr;
    }

    /**
     * @brief Construct a new Vec object whose size is _size and each element is
     * _value
     *
     * @param _size     Size of the Vec object
     * @param _value    Each element value of the Vec object
     */
    explicit Vec(int _size, T _value = T()) {
        this->size = _size;
        if (this->size > 0) {
            this->values = new T[this->size];
            for (int i = 0; i < this->size; i++) {
                this->values[i] = _value;
            }
        } else {
            this->values = nullptr;
        }
    }

    /**
     * @brief Construct a new Vec object
     *
     * @param _values   Format like {1, 2, 3}
     */
    Vec(const std::initializer_list<T> &_values) {
        this->size = _values.size();
        if (this->size > 0) {
            this->values = new T[this->size];
            for (int i = 0; i < this->size; i++) {
                this->values[i] = *(_values.begin() + i);
            }
        } else {
            this->values = nullptr;
        }
    }

    /**
     * @brief Copy constructor (deep copy)
     *
     * @param _vec      Copy source
     */
    Vec(const Vec<T> &_vec) {
        this->size = _vec.size;
        if (this->size > 0) {
            this->values = new T[this->size];
            for (int i = 0; i < this->size; i++) {
                this->values[i] = _vec.values[i];
            }
        } else {
            this->values = nullptr;
        }
    }

    /**
     * @brief Destroy the Vec object
     *
     */
    ~Vec() {
        if (this->values) {
            delete[] this->values;
        }
    }

    /**
     * @brief Get number of element
     *
     * @return int  number of element
     */
    int Size() const { return this->size; }

    /**
     * @brief Get _i th element value without validation
     *
     * @param _i    Index of element
     * @return T&   Reference of _i th element
     */
    T &operator[](int _i) { return this->values[_i]; }

    /**
     * @brief Get _i th element value with validation
     *
     * @param _i    Index of element
     * @return T&   Reference of _i th element
     */
    T &operator()(int _i) {
        assert(0 <= _i && _i < this->size);
        return this->values[_i];
    }

    /**
     * @brief Get pointer indicating value
     *
     * @return T*   Pointer indicating value
     */
    T *Values() { return this->values; }

    /**
     * @brief Check the same
     *
     * @param _vec      Comparison
     * @return true     Same with _vec
     * @return false    Not the same
     */
    bool operator==(const Vec<T> &_vec) const {
        if (this->size != _vec.size) {
            return false;
        }
        for (int i = 0; i < this->size; ++i) {
            if (this->values[i] != _vec.values[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Check not the same
     *
     * @param _vec      Comparison
     * @return true     Not the same
     * @return false    Same with _vec
     */
    bool operator!=(const Vec<T> &_vec) const { return !(*this == _vec); }

    /**
     * @brief Assign _vec to this object
     *
     * @param _vec      Assignor object
     * @return Vec<T>&  Reference of this object
     */
    Vec<T> &operator=(const Vec<T> &_vec) {
        if (this != &_vec) {
            if (this->values) {
                delete[] this->values;
            }
            this->size = _vec.size;
            this->values = new T[this->size];
            for (int i = 0; i < this->size; i++) {
                this->values[i] = _vec.values[i];
            }
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for addition
     *
     * @param _vec      Assignor object
     * @return Vec<T>&  Reference of this object
     */
    Vec<T> &operator+=(const Vec<T> &_vec) {
        assert(this->size == _vec.size);
        for (int i = 0; i < this->size; i++) {
            this->values[i] += _vec.values[i];
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for subtraction
     *
     * @param _vec      Assignor object
     * @return Vec<T>&  Reference of this object
     */
    Vec<T> &operator-=(const Vec<T> &_vec) {
        assert(this->size == _vec.size);
        for (int i = 0; i < this->size; i++) {
            this->values[i] -= _vec.values[i];
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for multiplication
     *
     * @param _a        Coefficient of multiplication
     * @return Vec<T>&  Reference of this object
     */
    Vec<T> &operator*=(T _a) {
        for (int i = 0; i < this->size; i++) {
            this->values[i] *= _a;
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for division
     *
     * @param _a        Coefficient of division
     * @return Vec<T>&  Reference of this object
     */
    Vec<T> &operator/=(T _a) {
        for (int i = 0; i < this->size; i++) {
            this->values[i] /= _a;
        }
        return *this;
    }

    /**
     * @brief Addition operator
     *
     * @param _vec          Adding vector
     * @return const Vec<T> Added vector
     */
    const Vec<T> operator+(const Vec<T> &_vec) const {
        Vec<T> retvec = *this;
        retvec += _vec;
        return retvec;
    }

    /**
     * @brief Subtraction operator
     *
     * @param _vec          Subtracting vector
     * @return const Vec<T> Subtracted vector
     */
    const Vec<T> operator-(const Vec<T> &_vec) const {
        Vec<T> retvec = *this;
        retvec -= _vec;
        return retvec;
    }

    /**
     * @brief Get reverse vector
     *
     * @return const Vec<T> Reverse vector
     */
    const Vec<T> operator-() const { return Vec<T>(this->size) - *this; }

    /**
     * @brief Get multipled vector
     *
     * @param _a            Multiple coefficient
     * @return const Vec<T> Multipled vector
     */
    const Vec<T> operator*(T _a) const {
        Vec<T> retvec = *this;
        retvec *= _a;
        return retvec;
    }

    /**
     * @brief Get matrix from vector matrix product
     *
     * @param _mat      Matrix used vector matrix product
     * @return Mat<T>   Matrix from vector matrix product
     */
    Mat<T> operator*(const Mat<T> &_mat) {
        assert(_mat.row == 1);
        Mat<T> retmat(this->size, _mat.col);
        for (int i = 0; i < retmat.row; ++i) {
            for (int j = 0; j < retmat.col; ++j) {
                retmat.values[retmat.col * i + j] =
                    this->values[i] * _mat.values[j];
            }
        }
        return retmat;
    }

    /**
     * @brief Get dividev vector
     *
     * @param _a            Divide coefficient
     * @return const Vec<T> Devided vector
     */
    const Vec<T> operator/(T _a) {
        Vec<T> retvec = *this;
        retvec /= _a;
        return retvec;
    }

    /**
     * @brief Convert to Mat
     *
     * @return Mat<T>   Mat object converted from this object
     */
    operator Mat<T>() const {
        Mat<T> retmat(this->size, 1);
        for (int i = 0; i < retmat.row * retmat.col; i++) {
            retmat.values[i] = this->values[i];
        }
        return retmat;
    }

    /**
     * @brief Convert to T
     *
     * @return T    T converted from this object
     */
    operator T() const {
        assert(this->size == 1);
        return this->values[0];
    }

    /**
     * @brief Get norm of this vector
     *
     * @return T    Norm of this vector
     */
    T Norm() const { return sqrt((*this).Dot(*this)); }

    /**
     * @brief Normalize vector
     *
     * @return const Vec<T> Normalized vector
     */
    const Vec<T> Normal() const {
        Vec<T> retvec = *this;
        return retvec / retvec.Norm();
    }

    /**
     * @brief Get scalar product
     *
     * @param _vec  Vector used scalar product
     * @return T    Scalar product
     */
    T Dot(const Vec<T> &_vec) const {
        assert(this->size == _vec.size);
        T retvalue = T();
        for (int i = 0; i < this->size; i++) {
            retvalue += this->values[i] * _vec.values[i];
        }
        return retvalue;
    }

    /**
     * @brief Get vector product
     *
     * @param _vec          Vector used vector product
     * @return const Vec<T> Vector product
     */
    const Vec<T> Cross(const Vec<T> &_vec) const {
        assert(this->size == 3 && _vec.size == 3);
        Vec<T> retvec(3);
        retvec[0] =
            this->values[1] * _vec.values[2] - this->values[2] * _vec.values[1];
        retvec[1] =
            this->values[2] * _vec.values[0] - this->values[0] * _vec.values[2];
        retvec[2] =
            this->values[0] * _vec.values[1] - this->values[1] * _vec.values[0];
        return retvec;
    }

    /**
     * @brief Stack vectors along vertical
     *
     * @param _vec  Vector to stack
     * @return const Vec<T> Stacked vector
     */
    const Vec<T> Vstack(const Vec<T> &_vec) const {
        Vec<T> retvec(this->size + _vec.size);
        for (int i = 0; i < this->size; i++) {
            retvec.values[i] = this->values[i];
        }
        for (int i = 0; i < _vec.size; i++) {
            retvec.values[i + this->size] = _vec.values[i];
        }
        return retvec;
    }

    /**
     * @brief Stack vectors along horizontal
     *
     * @param _vec  Vector to stack
     * @return const Mat<T> Stacked matrix
     */
    const Mat<T> Hstack(const Mat<T> &_mat) const {
        assert(this->size == _mat.row);
        Mat<T> retmat(this->size, _mat.col + 1);
        for (int i = 0; i < retmat.row; i++) {
            retmat.values[retmat.col * i] = this->values[i];
            for (int j = 1; j < retmat.col; j++) {
                retmat.values[retmat.col * i + j] =
                    _mat.values[_mat.col * i + j - 1];
            }
        }
        return retmat;
    }

    /**
     * @brief Get subvector
     *
     * @param _head         Start index
     * @param _length       Length of subvector
     * @return const Vec<T> Subvector
     */
    const Vec<T> Block(int _head, int _length) const {
        assert(0 <= _head && 0 <= _length && _head + _length < this->size);
        Vec<T> retvec(_length);
        for (int i = 0; i < retvec.size; i++) {
            retvec.values[i] = this->values[_head + i];
        }
        return retvec;
    }

    /**
     * @brief Transpose this vector
     *
     * @return const Mat<T> Transposed matrix
     */
    const Mat<T> Transpose() const {
        Mat<T> retmat(1, this->size);
        for (int i = 0; i < retmat.row * retmat.col; i++) {
            retmat.values[i] = this->values[i];
        }
        return retmat;
    }

    /**
     * @brief Get matrix whose diagonal is this vector
     *
     * @return const Mat<T> Diagonal matrix
     */
    const Mat<T> Diagonal() const {
        Mat<T> retmat(this->size, this->size);
        for (int i = 0; i < this->size; i++) {
            retmat.values[retmat.col * i + i] = this->values[i];
        }
        return retmat;
    }

   private:
    int size;
    T *values;
};

/**
 * @brief Add vector to stream
 *
 * @tparam U                Type of coefficient and vector
 * @param _out              Stream
 * @param _vec              Source vector
 * @return std::ostream&    Stream updated
 */
template <class U>
inline std::ostream &operator<<(std::ostream &_out, const Vec<U> &_vec) {
    for (int i = 0; i < _vec.size; i++) {
        _out << _vec.values[i] << std::endl;
    }
    return _out;
}

/**
 * @brief Get multipled vector
 *
 * @tparam U        Type of coefficient and vector
 * @param _a        Multiple coefficient
 * @param _vec      Applied vector
 * @return Vec<U>   Multipled vector
 */
template <class U>
inline Vec<U> operator*(U _a, const Vec<U> &_vec) {
    return _vec * _a;
}
}  // namespace PANSFE
