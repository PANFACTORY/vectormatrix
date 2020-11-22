#pragma once
#include <cassert>
#include <iostream>

#include "vec.h"

namespace PANSFE {
    template<class T>
    class Vec;

    template<class T>
    class Mat {
public:
        Mat() {
            this->row = 0;
            this->col = 0;
            this->values = nullptr;
        }
        Mat(int _row, int _col, T _value = T()) {
            this->row = _row;
            this->col = _col;
            if (this->row*this->col > 0) {
                this->values = new T[this->row*this->col];
                for (int i = 0; i < this->row*this->col; i++) {
                    this->values[i] = _value;
                }
            } else {
                this->values = nullptr;
            }
        }
        Mat(const std::initializer_list<std::initializer_list<T> > &_values) {
            this->row = _values.size();
            if (this->row > 0) {
                this->col = _values.begin()->size();
                if (this->row*this->col) {
                    this->values = new T[this->row*this->col];
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
        Mat(const Mat<T> &_mat) {
            this->row = _mat.row;
            this->col = _mat.col;
            if (this->row*this->col > 0) {
                this->values = new T[this->row*this->col];
                for (int i = 0; i < this->row*this->col; i++) {
                    this->values[i] = _mat.values[i];
                }
            } else {
                this->values = nullptr;
            }
        }
        ~Mat() {
            if (this->values) {
                delete[] this->values;
            }
        }

        int Row() const;
        int Col() const;
        T* operator[](int _i);          //  without validation
        T& operator()(int _i, int _j);  //  with validation

        Mat<T>& operator=(const Mat<T> &_mat);
        Mat<T>& operator+=(const Mat<T> &_mat);
        Mat<T>& operator-=(const Mat<T> &_mat);
        Mat<T>& operator*=(T _a);
        Mat<T>& operator*=(const Mat<T> &_mat);
        Mat<T>& operator/=(T _a);

        const Mat<T> operator+(const Mat<T> &_mat) const;
        const Mat<T> operator-() const;
        const Mat<T> operator-(const Mat<T> &_mat) const;
        const Mat<T> operator*(T _a) const;
        const Mat<T> operator*(const Mat<T> &_mat) const;
        const Vec<T> operator*(const Vec<T> &_vec) const;
        const Mat<T> operator/(T _a) const;

        operator Vec<T>() const {
            assert(this->col == 1);
            Vec<T> retvec(this->row);
            for (int i = 0; i < retvec.size; i++) {
                retvec.values[i] = this->values[i];
            }
            return retvec;
        }

        operator T() const {
            assert(this->row == 1 && this->col == 1);
            return this->values[0];
        }

        template<class U>
	    friend std::ostream& operator<<(std::ostream &_out, const Mat<U> &_mat);
        template<class U>
        friend Mat<U> operator*(U _a, const Mat<U> &_mat);

        const Mat<T> Transpose() const;
        T Determinant() const;
        const Mat<T> Inverse() const;
        const Mat<T> Cofactor(int _i, int _j) const;
        const Mat<T> Vstack(const Mat<T> &_mat) const;
        const Mat<T> Hstack(const Mat<T> &_mat) const;
        const Mat<T> Block(int _row, int _col, int _h, int _w) const;

        static Mat<T> Identity(int _row);

        template<class U>
        friend class Vec;

private:
        int row, col;
        T *values;
    };

    template<class T>
    int Mat<T>::Row() const {
        return this->row;
    }

    template<class T>
    int Mat<T>::Col() const {
        return this->col;
    }

    template<class T>
    T* Mat<T>::operator[](int _i) {
        return &this->values[this->col*_i];
    }

    template<class T>
    T& Mat<T>::operator()(int _i, int _j) {
        assert(0 <= _i && _i < this->row && 0 <= _j && _j < this->col);
        return this->values[this->col*_i + _j];
    }

    template<class T>
    Mat<T>& Mat<T>::operator=(const Mat<T> &_mat) {
        if (this != &_mat) {
            if (this->values) {
                delete[] this->values;
            }
            this->row = _mat.row;
            this->col = _mat.col;
            this->values = new T[this->row*this->col];
            for (int i = 0; i < this->row*this->col; i++) {
                this->values[i] = _mat.values[i];
            }
        }
        return *this;
    }

    template<class T>
    Mat<T>& Mat<T>::operator+=(const Mat<T> &_mat) {
        assert(this->row == _mat.row && this->col == _mat.col);
        for (int i = 0; i < this->row*this->col; i++) {
            this->values[i] += _mat.values[i];
        }
        return *this;
    }

    template<class T>
    Mat<T>& Mat<T>::operator-=(const Mat<T> &_mat) {
        *this += -_mat;
        return *this;
    }

    template<class T>
    Mat<T>& Mat<T>::operator*=(T _a) {
        for (int i = 0; i < this->row*this->col; i++) {
            this->values[i] *= _a;
        }
        return *this;
    }

    template<class T>
    Mat<T>& Mat<T>::operator*=(const Mat<T> &_mat) {
        assert(this->col == _mat.row);
        Mat<T> retmat(this->row, _mat.col);
        for (int i = 0; i < retmat.row; i++) {
            for (int j = 0; j < retmat.col; j++) {
                for (int k = 0; k < this->col; k++) {
                    retmat.values[retmat.col*i + j] += this->values[this->col*i + k]*_mat.values[_mat.col*k + j];
                }
            }
        }
        *this = retmat;
        return *this;
    }

    template<class T>
    Mat<T>& Mat<T>::operator/=(T _a) {
        for (int i = 0; i < this->row*this->col; i++) {
            this->values[i] /= _a;
        }
        return *this;
    }

    template<class T>
    const Mat<T> Mat<T>::operator+(const Mat<T> &_mat) const {
        Mat<T> retmat = *this;
        retmat += _mat;
        return retmat;
    }

    template<class T>
    const Mat<T> Mat<T>::operator-() const {
        Mat<T> retmat = *this;
        for (int i = 0; i < retmat.row*retmat.col; i++) {
            retmat.values[i] = -retmat.values[i];
        }
        return retmat;
    }

    template<class T>
    const Mat<T> Mat<T>::operator-(const Mat<T> &_mat) const {
        Mat<T> retmat = *this;
        retmat -= _mat;
        return retmat;
    }

    template<class T>
    const Mat<T> Mat<T>::operator*(T _a) const {
        Mat<T> retmat = *this;
        retmat *= _a;
        return retmat;
    }

    template<class T>
    const Mat<T> Mat<T>::operator*(const Mat<T> &_mat) const {
        Mat<T> retmat = *this;
        retmat *= _mat;
        return retmat;
    }

    template<class T>
    const Vec<T> Mat<T>::operator*(const Vec<T> &_vec) const {
        assert(this->col == _vec.size);
        Vec<T> retvec(this->row);
        for(int i = 0; i < this->row; i++){
            for(int j = 0; j < this->col; j++){
                retvec.values[i] += this->values[this->col*i + j]*_vec.values[j];
            }
        }
        return retvec;
    }

    template<class T>
    const Mat<T> Mat<T>::operator/(T _a) const {
        Mat<T> retmat = *this;
        retmat /= _a;
        return retmat;
    }

    template<class U>
    std::ostream& operator<<(std::ostream &_out, const Mat<U> &_mat) {
        for (int i = 0; i < _mat.row; i++) {
            for (int j = 0; j < _mat.col; j++) {
                _out << _mat.values[_mat.col*i + j] << "\t";
            }
            _out << std::endl;
        }
        return _out;
    }

    template<class U>
    Mat<U> operator*(U _a, const Mat<U> &_mat) {
        return _mat*_a;
    }

    template<class T>
    const Mat<T> Mat<T>::Transpose() const {
        Mat<T> retmat(this->col, this->row);
        for (int i = 0; i < retmat.row; i++) {
            for (int j = 0; j < retmat.col; j++) {
                retmat.values[retmat.col*i + j] = this->values[this->col*j + i];
            }
        }
        return retmat;
    }

    template<class T>
    T Mat<T>::Determinant() const {
        assert(this->row == this->col && 0 < this->row);
        if (this->row == 1) {
            return this->values[0];
        } else if (this->row == 2) {
            return this->values[0]*this->values[3] - this->values[1]*this->values[2];
        } else if (this->row == 3) {
            return - this->values[8]*this->values[1]*this->values[3] - this->values[7]*this->values[5]*this->values[0] - this->values[2]*this->values[4]*this->values[6]
                    + this->values[6]*this->values[1]*this->values[5] + this->values[7]*this->values[3]*this->values[2] + this->values[0]*this->values[4]*this->values[8];
        } else {
            T retvalue = T();
            for(int i = 0; i < this->row; i++){
                retvalue += pow(-1.0, i)*this->values[this->col*i]*this->Cofactor(i, 0).Determinant();
            }
            return retvalue;
        }
    }

    template<class T>
    const Mat<T> Mat<T>::Inverse() const {
        assert(this->row == this->col);
        Mat<T> retmat(this->row, this->col);
        if (this->row == 1) {
            retmat.values[0] = 1/this->values[0];
            return retmat;
        } else {
            for(int i = 0; i < this->row; i++){
                for(int j = 0; j < this->col; j++){
                    retmat.values[retmat.col*i + j] = pow(-1.0, i + j)*this->Cofactor(j, i).Determinant();
                }
            }
            return retmat/this->Determinant();
        }
    }
        
    template<class T>
    const Mat<T> Mat<T>::Cofactor(int _i, int _j) const {
        assert(0 <= _i && _i < this->row && 0 <= _j && _j < this->col);
        Mat<T> retmat(this->row - 1, this->col - 1);
        for(int i = 0; i < retmat.row; i++){
            for(int j = 0; j < retmat.col; j++){
                if (i < _i) {
                    if (j < _j) {
                        retmat.values[retmat.col*i + j] = this->values[this->col*i + j];
                    } else {
                        retmat.values[retmat.col*i + j] = this->values[this->col*i + (j + 1)];
                    }
                } else {
                    if (j < _j) {
                        retmat.values[retmat.col*i + j] = this->values[this->col*(i + 1) + j];
                    } else {
                        retmat.values[retmat.col*i + j] = this->values[this->col*(i + 1) + (j + 1)];
                    }
                }
            }
        }
        return retmat;
    }

    template<class T>
    const Mat<T> Mat<T>::Vstack(const Mat<T> &_mat) const {
        assert(this->col == _mat.col);
        Mat<T> retmat(this->row + _mat.row, this->col);
        for(int i = 0; i < this->row; i++){
            for(int j = 0; j < this->col; j++){
                retmat.values[retmat.col*i + j] = this->values[this->col*i + j];
            }
        }
        for(int i = 0; i < _mat.row; i++){
            for(int j = 0; j < _mat.col; j++){
                retmat.values[retmat.col*(i + this->row) + j] = _mat.values[_mat.col*i + j];
            }
        }
        return retmat;
    }

    template<class T>
    const Mat<T> Mat<T>::Hstack(const Mat<T> &_mat) const {
        assert(this->row == _mat.row);
        Mat<T> retmat(this->row, this->col + _mat.col);
        for(int i = 0; i < this->row; i++){
            for(int j = 0; j < this->col; j++){
                retmat.values[retmat.col*i + j] = this->values[this->col*i + j];
            }
        }
        for(int i = 0; i < _mat.row; i++){
            for(int j = 0; j < _mat.col; j++){
                retmat.values[retmat.col*i + (j + this->col)] = _mat.values[_mat.col*i + j];
            }
        }
        return retmat;
    }

    template<class T>
    const Mat<T> Mat<T>::Block(int _row, int _col, int _h, int _w) const {
        assert(0 <= _row && 0 <= _col && 0 < _h && 0 < _w && _row + _h <= this->row && _col + _w <= this->col);
        Mat<T> retmat(_h, _w);
        for(int i = 0; i < _h; i++){
            for(int j = 0; j < _w; j++){
                retmat.values[retmat.col*i + j] = this->values[this->col*(_row + i) + (_col + j)];
            }
        }
        return retmat;
    }

    template<class T>
    Mat<T> Mat<T>::Identity(int _row) {
        assert(0 < _row);
        Mat<T> retmat(_row, _row);
        for (int i = 0; i < retmat.row; i++) {
            retmat.values[retmat.col*i + i] = 1;
        }
        return retmat;
    }
}