#pragma once
#include <cassert>
#include <iostream>
#include <cmath>

#include "mat.h"

namespace PANSFE {
    template<class T>
    class Mat;

    template<class T>
    class Vec {
public:
        Vec() {
            this->size = 0;
            this->values = nullptr;
        }
        Vec(int _size, T _value = T()) {
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
        Vec(const std::initializer_list<T> &_values) {
            this->size = _values.size();
            if (this->size > 0) {
                this->values = new T[this->size];
                for(int i = 0; i < this->size; i++){
                    this->values[i] = *(_values.begin() + i);
                }
            } else {
                this->values = nullptr;
            }
        }
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
        ~Vec() {
            if (this->values) {
                delete[] this->values;
            }
        }

        int Size() const;
        T& operator[](int _i);  //  without validation
        T& operator()(int _i);  //  with validation

        Vec<T>& operator=(const Vec<T> &_vec);
        Vec<T>& operator+=(const Vec<T> &_vec);
        Vec<T>& operator-=(const Vec<T> &_vec);
        Vec<T>& operator*=(T _a);
        Vec<T>& operator/=(T _a);
        Vec<T>& operator^=(const Vec<T> &_vec);

        const Vec<T> operator+(const Vec<T> &_vec) const;
        const Vec<T> operator-() const;
        const Vec<T> operator-(const Vec<T> &_vec) const;
        const Vec<T> operator*(T _a) const;
        T operator*(const Vec<T> &_vec) const;
        const Vec<T> operator/(T _a) const;
        const Vec<T> operator^(const Vec<T> &_vec) const;

        operator Mat<T>() const {
            Mat<T> retmat(this->size, 1);
            for (int i = 0; i < retmat.row*retmat.col; i++) {
                retmat.values[i] = this->values[i];
            }
            return retmat;
        }

        operator T() const {
            assert(this->size == 1);
            return this->values[0];
        }

        template<class U>
	    friend std::ostream& operator<<(std::ostream &_out, const Vec<U> &_vec);
        template<class U>
        friend Vec<U> operator*(U _a, const Vec<U> &_vec);

        T Norm() const;
        const Vec<T> Normal() const;
        const Vec<T> Vstack(const Vec<T> &_vec) const;
        const Mat<T> Hstack(const Mat<T> &_mat) const;
        const Vec<T> Block(int _head, int _length) const;
        const Mat<T> Transpose() const;
        const Mat<T> Diagonal() const;

        template<class U>
        friend class Mat;

private:
        int size;
        T *values;
    };

    template<class T>
    int Vec<T>::Size() const {
        return this->size;
    }

    template<class T>
    T& Vec<T>::operator[](int _i) {
        return this->values[_i];
    }

    template<class T>
    T& Vec<T>::operator()(int _i) {
        assert(0 <= _i && _i < this->size);
        return this->values[_i];
    }

    template<class T>
    Vec<T>& Vec<T>::operator=(const Vec<T> &_vec) {
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

    template<class T>
    Vec<T>& Vec<T>::operator+=(const Vec<T> &_vec) {
        assert(this->size == _vec.size);
        for (int i = 0; i < this->size; i++) {
            this->values[i] += _vec.values[i];
        }
        return *this;
    }

    template<class T>
    Vec<T>& Vec<T>::operator-=(const Vec<T> &_vec) {
        *this += -_vec;
        return *this;
    }

    template<class T>
    Vec<T>& Vec<T>::operator*=(T _a) {
        for (int i = 0; i < this->size; i++) {
            this->values[i] *= _a;
        }
        return *this;
    }

    template<class T>
    Vec<T>& Vec<T>::operator/=(T _a) {
        for (int i = 0; i < this->size; i++) {
            this->values[i] /= _a;
        }
        return *this;
    }

    template<class T>
    Vec<T>& Vec<T>::operator^=(const Vec<T> &_vec) {
        assert(this->size == 3 && _vec.size == 3);
        Vec<T> retvec(3);
        retvec[0] = this->values[1]*_vec.values[2] - this->values[2]*_vec.values[1];
        retvec[1] = this->values[2]*_vec.values[0] - this->values[0]*_vec.values[2];
        retvec[2] = this->values[0]*_vec.values[1] - this->values[1]*_vec.values[0];
        *this = retvec;
        return *this;
    }

    template<class T>
    const Vec<T> Vec<T>::operator+(const Vec<T> &_vec) const {
        Vec<T> retvec = *this;
        retvec += _vec;
        return retvec;
    }

    template<class T>
    const Vec<T> Vec<T>::operator-() const {
        Vec<T> retvec = *this;
        for (int i = 0; i < retvec.size; i++) {
            retvec.values[i] = -retvec.values[i];
        }
        return retvec;
    }

    template<class T>
    const Vec<T> Vec<T>::operator-(const Vec<T> &_vec) const {
        Vec<T> retvec = *this;
        retvec -= _vec;
        return retvec;
    }

    template<class T>
    const Vec<T> Vec<T>::operator*(T _a) const {
        Vec<T> retvec = *this;
        retvec *= _a;
        return retvec;
    }

    template<class T>
    T Vec<T>::operator*(const Vec<T> &_vec) const {
        assert(this->size == _vec.size);
        T retvalue = T();
        for (int i = 0; i < this->size; i++) {
            retvalue += this->values[i]*_vec.values[i];
        }
        return retvalue;
    }

    template<class T>
    const Vec<T> Vec<T>::operator/(T _a) const {
        Vec<T> retvec = *this;
        retvec /= _a;
        return retvec;
    }

    template<class T>
    const Vec<T> Vec<T>::operator^(const Vec<T> &_vec) const {
        Vec<T> retvec = *this;
        retvec ^= _vec;
        return retvec;
    }

    template<class U>
    std::ostream& operator<<(std::ostream &_out, const Vec<U> &_vec) {
        for (int i = 0; i < _vec.size; i++) {
            _out << _vec.values[i] << std::endl;
        }
        return _out;
    }

    template<class U>
    Vec<U> operator*(U _a, const Vec<U> &_vec) {
        return _vec*_a;
    }

    template<class T>
    T Vec<T>::Norm() const {
        return sqrt((*this)*(*this));
    }

    template<class T>
    const Vec<T> Vec<T>::Normal() const {
        Vec<T> retvec = *this;
        return retvec/retvec.Norm();
    }

    template<class T>
    const Vec<T> Vec<T>::Vstack(const Vec<T> &_vec) const {
        Vec<T> retvec(this->size + _vec.size);
        for (int i = 0; i < this->size; i++) {
            retvec.values[i] = this->values[i];
        }
        for (int i = 0; i < _vec.size; i++) {
            retvec.values[i + this->size] = _vec.values[i];
        }
        return retvec;
    }

    template<class T>
    const Mat<T> Vec<T>::Hstack(const Mat<T> &_mat) const {
        assert(this->size == _mat.row);
        Mat<T> retmat(this->size, _mat.col + 1);
        for (int i = 0; i < retmat.row; i++) {
            retmat.values[retmat.col*i] = this->values[i];
            for (int j = 0; j < retmat.col; j++) {
                retmat.values[retmat.col*i + (j + 1)] = _mat.values[_mat.col*i + j];
            }
        }
        return retmat;
    }

    template<class T>
    const Vec<T> Vec<T>::Block(int _head, int _length) const {
        assert(0 <= _head && 0 <= _length && _head + _length < this->size);
        Vec<T> retvec(_length);
        for (int i = 0; i < retvec.size; i++) {
            retvec.values[i] = this->values[_head + i];
        }
        return retvec;
    }

    template<class T>
    const Mat<T> Vec<T>::Transpose() const {
        Mat<T> retmat(1, this->size);
        for(int i = 0; i < retmat.row*retmat.col; i++){
            retmat.values[i] = this->values[i];
        }
        return retmat;
    }

    template<class T>
    const Mat<T> Vec<T>::Diagonal() const {
        Mat<T> retmat(this->size, this->size);
        for (int i = 0; i < this->size; i++) {
            retmat.values[retmat.col*i + i] = this->values[i];
        }
        return retmat;
    }
}