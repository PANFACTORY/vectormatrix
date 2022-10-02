/**
 * @file mat.h
 * @author PANFACTORY (github/PANFACTORY)
 * @brief Definition and implementation of linear algebraic matrix class
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <cassert>
#include <iostream>

#include "vec.h"

namespace PANSFE {
template <class T>
class Vec;

/**
 * @brief Linear algebraic matrix class
 *
 * @tparam T Type of element
 */
template <class T>
class Mat {
    template <class U>
    friend std::ostream &operator<<(std::ostream &_out, const Mat<U> &_mat);
    template <class U>
    friend Mat<U> operator*(U _a, const Mat<U> &_mat);

    template <class U>
    friend class Vec;

   public:
    /**
     * @brief Construct a new Mat object whose row and column are zero.
     *
     */
    Mat() {
        this->row = 0;
        this->col = 0;
        this->values = nullptr;
    }

    /**
     * @brief Construct a new Mat object whose row, col and each element value
     * are _row, _col, and _value, respectively.
     *
     * @param _row      Row of the Mat object
     * @param _col      Column of the Mat object
     * @param _value    Each element value of Mat object
     */
    Mat(int _row, int _col, T _value = T()) {
        this->row = _row;
        this->col = _col;
        if (this->row * this->col > 0) {
            this->values = new T[this->row * this->col];
            for (int i = 0; i < this->row * this->col; i++) {
                this->values[i] = _value;
            }
        } else {
            this->values = nullptr;
        }
    }

    /**
     * @brief Construct a new Mat object
     *
     * @param _values   Format like {{1, 2, 3}, {4, 5, 6}}
     */
    Mat(const std::initializer_list<std::initializer_list<T> > &_values) {
        this->row = _values.size();
        if (this->row > 0) {
            this->col = _values.begin()->size();
            if (this->row * this->col) {
                this->values = new T[this->row * this->col];
                int index = 0;
                for (auto valuei : _values) {
                    assert(this->col == valuei.size());
                    for (auto valueij : valuei) {
                        this->values[index] = valueij;
                        index++;
                    }
                }
            } else {
                this->values = nullptr;
            }
        } else {
            this->col = 0;
            this->values = nullptr;
        }
    }

    /**
     * @brief Copy constructor (deep copy)
     *
     * @param _mat  Copy source
     */
    Mat(const Mat<T> &_mat) {
        this->row = _mat.row;
        this->col = _mat.col;
        if (this->row * this->col > 0) {
            this->values = new T[this->row * this->col];
            for (int i = 0; i < this->row * this->col; i++) {
                this->values[i] = _mat.values[i];
            }
        } else {
            this->values = nullptr;
        }
    }

    /**
     * @brief Destroy the Mat object
     *
     */
    ~Mat() {
        if (this->values) {
            delete[] this->values;
        }
    }

    /**
     * @brief Get number of row
     *
     * @return int  Number of row
     */
    int Row() const { return this->row; }

    /**
     * @brief Get number of column
     *
     * @return int  Number of column
     */
    int Col() const { return this->col; }

    /**
     * @brief Get _i th element pointer without validation
     *
     * @param _i    Index of element
     * @return T*   Pointer of _i th element
     */
    T *operator[](int _i) { return &this->values[this->col * _i]; }

    /**
     * @brief Get (_i, _j) element value with validation
     *
     * @param _i    Index of row
     * @param _j    Index of column
     * @return T&   Reference of (_i, _j) element value
     */
    T &operator()(int _i, int _j) {
        assert(0 <= _i && _i < this->row && 0 <= _j && _j < this->col);
        return this->values[this->col * _i + _j];
    }

    /**
     * @brief Get pointer indicating value
     *
     * @return T*   Pointer indicating value
     */
    T *Values() { return values; }

    /**
     * @brief Check the same
     *
     * @param _mat      Comparison
     * @return true     Same with _mat
     * @return false    Not the same
     */
    bool operator==(const Mat<T> &_mat) const {
        if (this->row != _mat.row || this->col != _mat.col) {
            return false;
        }
        for (int i = 0; i < this->row * this->col; ++i) {
            if (this->values[i] != _mat.values[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Check not the same
     *
     * @param _mat      Comparison
     * @return true     Not the same
     * @return false    Same with _mat
     */
    bool operator!=(const Mat<int> &_mat) const { return !(*this == _mat); }

    /**
     * @brief Assign _mat to this object
     *
     * @param _mat      Assignor object
     * @return Mat<T>&  Reference of this object
     */
    Mat<T> &operator=(const Mat<T> &_mat) {
        if (this != &_mat) {
            if (this->values) {
                delete[] this->values;
            }
            this->row = _mat.row;
            this->col = _mat.col;
            this->values = new T[this->row * this->col];
            for (int i = 0; i < this->row * this->col; i++) {
                this->values[i] = _mat.values[i];
            }
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for addition
     *
     * @param _mat      Assignor object
     * @return Mat<T>&  Reference of this object
     */
    Mat<T> &operator+=(const Mat<T> &_mat) {
        assert(this->row == _mat.row && this->col == _mat.col);
        for (int i = 0; i < this->row * this->col; i++) {
            this->values[i] += _mat.values[i];
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for subtraction
     *
     * @param _mat      Assignor object
     * @return Mat<T>&  Reference of this object
     */
    Mat<T> &operator-=(const Mat<T> &_mat) {
        assert(this->row == _mat.row && this->col == _mat.col);
        for (int i = 0; i < this->row * this->col; i++) {
            this->values[i] -= _mat.values[i];
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for multiplication
     *
     * @param _a        Coefficient of multiplication
     * @return Mat<T>&  Reference of this object
     */
    Mat<T> &operator*=(T _a) {
        for (int i = 0; i < this->row * this->col; i++) {
            this->values[i] *= _a;
        }
        return *this;
    }

    /**
     * @brief Compound assignment operator for matrix matrix production
     *
     * @param _mat      Multiplying matrix
     * @return Mat<T>&  Reference of this object
     */
    Mat<T> &operator*=(const Mat<T> &_mat) {
        assert(this->col == _mat.row);
        Mat<T> retmat(this->row, _mat.col);
        for (int i = 0; i < retmat.row; i++) {
            for (int j = 0; j < retmat.col; j++) {
                for (int k = 0; k < this->col; k++) {
                    retmat.values[retmat.col * i + j] +=
                        this->values[this->col * i + k] *
                        _mat.values[_mat.col * k + j];
                }
            }
        }
        *this = retmat;
        return *this;
    }

    /**
     * @brief Compound assignment operator for division
     *
     * @param _a        Coefficient of division
     * @return Mat<T>&  Reference of this object
     */
    Mat<T> &operator/=(T _a) {
        for (int i = 0; i < this->row * this->col; i++) {
            this->values[i] /= _a;
        }
        return *this;
    }

    /**
     * @brief Addition operator
     *
     * @param _mat          Adding matrix
     * @return const Mat<T> Added matrix
     */
    const Mat<T> operator+(const Mat<T> &_mat) const {
        Mat<T> retmat = *this;
        retmat += _mat;
        return retmat;
    }

    /**
     * @brief Subtraction operator
     *
     * @param _mat          Subtracting matrix
     * @return const Mat<T> Subtracted matrix
     */
    const Mat<T> operator-(const Mat<T> &_mat) const {
        Mat<T> retmat = *this;
        retmat -= _mat;
        return retmat;
    }

    /**
     * @brief Get sign reversed matrix
     *
     * @return const Mat<T> Sign reversed matrix
     */
    const Mat<T> operator-() const {
        return Mat<T>(this->row, this->col) - *this;
    }

    /**
     * @brief Get multipled matrix
     *
     * @param _a            Multiple coefficient
     * @return const Mat<T> Multipled matrix
     */
    const Mat<T> operator*(T _a) const {
        Mat<T> retmat = *this;
        retmat *= _a;
        return retmat;
    }

    /**
     * @brief Get matrix matrix product
     *
     * @param _mat          Matrix used matrix matrix product
     * @return const Mat<T> Matrix from matrix matrix product
     */
    const Mat<T> operator*(const Mat<T> &_mat) const {
        Mat<T> retmat = *this;
        retmat *= _mat;
        return retmat;
    }

    /**
     * @brief Get matrix vector product
     *
     * @param _vec          Vector used matrix vector product
     * @return const Vec<T> Vector from matrix vector product
     */
    const Vec<T> operator*(const Vec<T> &_vec) const {
        assert(this->col == _vec.size);
        Vec<T> retvec(this->row);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                retvec.values[i] +=
                    this->values[this->col * i + j] * _vec.values[j];
            }
        }
        return retvec;
    }

    /**
     * @brief Get dividev matrix
     *
     * @param _a            Divide coefficient
     * @return const Mat<T> Devided matrix
     */
    const Mat<T> operator/(T _a) const {
        Mat<T> retmat = *this;
        retmat /= _a;
        return retmat;
    }

    /**
     * @brief Convert to Vec
     *
     * @return Vec<T>   Vec object converted from this object
     */
    operator Vec<T>() const {
        assert(this->col == 1);
        Vec<T> retvec(this->row);
        for (int i = 0; i < retvec.size; i++) {
            retvec.values[i] = this->values[i];
        }
        return retvec;
    }

    /**
     * @brief Convert to T
     *
     * @return T    T converted from this object
     */
    operator T() const {
        assert(this->row == 1 && this->col == 1);
        return this->values[0];
    }

    /**
     * @brief Transpose this matrix
     *
     * @return const Mat<T> Transposed matrix
     */
    const Mat<T> Transpose() const {
        Mat<T> retmat(this->col, this->row);
        for (int i = 0; i < retmat.row; i++) {
            for (int j = 0; j < retmat.col; j++) {
                retmat.values[retmat.col * i + j] =
                    this->values[this->col * j + i];
            }
        }
        return retmat;
    }

    /**
     * @brief Get determinant of this matrix
     *
     * @return T    Determinant of this matrix
     */
    T Determinant() const {
        assert(this->row == this->col && 0 < this->row);
        if (this->row == 1) {
            return this->values[0];
        } else if (this->row == 2) {
            return this->values[0] * this->values[3] -
                   this->values[1] * this->values[2];
        } else if (this->row == 3) {
            return -this->values[8] * this->values[1] * this->values[3] -
                   this->values[7] * this->values[5] * this->values[0] -
                   this->values[2] * this->values[4] * this->values[6] +
                   this->values[6] * this->values[1] * this->values[5] +
                   this->values[7] * this->values[3] * this->values[2] +
                   this->values[0] * this->values[4] * this->values[8];
        } else {
            T retvalue = T();
            for (int i = 0; i < this->row; i++) {
                retvalue += pow(-1.0, i) * this->values[this->col * i] *
                            this->Cofactor(i, 0).Determinant();
            }
            return retvalue;
        }
    }

    /**
     * @brief Get inverse matrix
     *
     * @return const Mat<T> Inverse matrix
     */
    const Mat<T> Inverse() const {
        assert(this->row == this->col);
        Mat<T> retmat(this->row, this->col);
        if (this->row == 1) {
            retmat.values[0] = 1 / this->values[0];
            return retmat;
        } else {
            for (int i = 0; i < this->row; i++) {
                for (int j = 0; j < this->col; j++) {
                    retmat.values[retmat.col * i + j] =
                        pow(-1.0, i + j) * this->Cofactor(j, i).Determinant();
                }
            }
            return retmat / this->Determinant();
        }
    }

    /**
     * @brief Get submatrix removed _i th row and _j th column
     *
     * @param _i            Index of row
     * @param _j            Index of column
     * @return const Mat<T> Submatrix
     */
    const Mat<T> Cofactor(int _i, int _j) const {
        assert(0 <= _i && _i < this->row && 0 <= _j && _j < this->col);
        Mat<T> retmat(this->row - 1, this->col - 1);
        for (int i = 0; i < retmat.row; i++) {
            for (int j = 0; j < retmat.col; j++) {
                if (i < _i) {
                    if (j < _j) {
                        retmat.values[retmat.col * i + j] =
                            this->values[this->col * i + j];
                    } else {
                        retmat.values[retmat.col * i + j] =
                            this->values[this->col * i + (j + 1)];
                    }
                } else {
                    if (j < _j) {
                        retmat.values[retmat.col * i + j] =
                            this->values[this->col * (i + 1) + j];
                    } else {
                        retmat.values[retmat.col * i + j] =
                            this->values[this->col * (i + 1) + (j + 1)];
                    }
                }
            }
        }
        return retmat;
    }

    /**
     * @brief Stack matrixes along vertical
     *
     * @param _mat  Matrix to stack
     * @return const Mat<T> Stacked matrix
     */
    const Mat<T> Vstack(const Mat<T> &_mat) const {
        assert(this->col == _mat.col);
        Mat<T> retmat(this->row + _mat.row, this->col);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                retmat.values[retmat.col * i + j] =
                    this->values[this->col * i + j];
            }
        }
        for (int i = 0; i < _mat.row; i++) {
            for (int j = 0; j < _mat.col; j++) {
                retmat.values[retmat.col * (i + this->row) + j] =
                    _mat.values[_mat.col * i + j];
            }
        }
        return retmat;
    }

    /**
     * @brief Stack matrixes along horizontal
     *
     * @param _mat  Matrix to stack
     * @return const Mat<T> Stacked matrix
     */
    const Mat<T> Hstack(const Mat<T> &_mat) const {
        assert(this->row == _mat.row);
        Mat<T> retmat(this->row, this->col + _mat.col);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                retmat.values[retmat.col * i + j] =
                    this->values[this->col * i + j];
            }
        }
        for (int i = 0; i < _mat.row; i++) {
            for (int j = 0; j < _mat.col; j++) {
                retmat.values[retmat.col * i + (j + this->col)] =
                    _mat.values[_mat.col * i + j];
            }
        }
        return retmat;
    }

    /**
     * @brief Get submatrix
     *
     * @param _row          Start index of row
     * @param _col          Start index of column
     * @param _h            Height of submatrix
     * @param _w            Width of submatrix
     * @return const Mat<T> Submatrix
     */
    const Mat<T> Block(int _row, int _col, int _h, int _w) const {
        assert(0 <= _row && 0 <= _col && 0 < _h && 0 < _w &&
               _row + _h <= this->row && _col + _w <= this->col);
        Mat<T> retmat(_h, _w);
        for (int i = 0; i < _h; i++) {
            for (int j = 0; j < _w; j++) {
                retmat.values[retmat.col * i + j] =
                    this->values[this->col * (_row + i) + (_col + j)];
            }
        }
        return retmat;
    }

    /**
     * @brief Get identity matrix
     *
     * @param _row      Matrix size
     * @return Mat<T>   Identity matrix
     */
    static Mat<T> Identity(int _row) {
        assert(0 < _row);
        Mat<T> retmat(_row, _row);
        for (int i = 0; i < retmat.row; i++) {
            retmat.values[retmat.col * i + i] = 1;
        }
        return retmat;
    }

   private:
    int row, col;
    T *values;
};

/**
 * @brief Add matrix to stream
 *
 * @tparam U                Element type of matrix
 * @param _out              Stream
 * @param _mat              Source matrix
 * @return std::ostream&    Stream updated
 */
template <class U>
std::ostream &operator<<(std::ostream &_out, const Mat<U> &_mat) {
    for (int i = 0; i < _mat.row; i++) {
        for (int j = 0; j < _mat.col; j++) {
            _out << _mat.values[_mat.col * i + j] << "\t";
        }
        _out << std::endl;
    }
    return _out;
}

/**
 * @brief Get multipled matrix
 *
 * @tparam U        Type of coefficient and matrix
 * @param _a        Multiple coefficient
 * @param _mat      Applied matrix
 * @return Mat<U>   Multipled matrix
 */
template <class U>
Mat<U> operator*(U _a, const Mat<U> &_mat) {
    return _mat * _a;
}
}  // namespace PANSFE
