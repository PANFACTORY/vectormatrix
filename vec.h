#pragma once
#include <cassert>
#include <iostream>

namespace PANSFE {
    template<class T>
    class Vec {
public:
        Vec() {
            this->size = 0;
            this->values = nullptr;
        }
        Vec(int _size, T _value = T()) {
            this->size = _size;
            this->values = new T[this->size];
            for (int i = 0; i < this->size; i++) {
                this->values[i] = _value;
            }
        }
        Vec(const std::initializer_list<T> &_values) {
            this->size = _values.size();
            this->values = new T[this->size];
            for(int i = 0; i < this->size; i++){
                this->values[i] = *(_values.begin() + i);
            }
        }
        Vec(const Vec<T> &_vec) {
            this->size = _vec.size;
            if (_vec.values) {
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

        const Vec<T> operator+(const Vec<T> &_vec) const;
        const Vec<T> operator-() const;
        const Vec<T> operator-(const Vec<T> &_vec) const;
        const Vec<T> operator*(T _a) const;
        T operator*(const Vec<T> &_vec) const;
        const Vec<T> operator/(T _a) const;

        template<class U>
	    friend std::ostream& operator<<(std::ostream &_out, const Vec<U> &_vec);
        template<class U>
        friend Vec<U> operator*(U _a, const Vec<U> &_vec);

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
    const Vec<T> Vec<T>::operator+(const Vec<T> &_vec) const {
        assert(this->size == _vec.size);
        Vec<T> retvec = *this;
        retvec += _vec;
        return retvec;
    }

    template<class T>
    const Vec<T> Vec<T>::operator-() const {
        Vec<T> retvec = *this;
        for (int i = 0; i < retvec.size; i++) {
            retvec[i] = -retvec[i];
        }
        return retvec;
    }

    template<class T>
    const Vec<T> Vec<T>::operator-(const Vec<T> &_vec) const {
        assert(this->size == _vec.size);
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
}