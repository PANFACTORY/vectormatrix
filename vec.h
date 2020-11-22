#pragma once
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

        Vec<T>& operator=(const Vec<T> &_vec);

        template<class U>
	    friend std::ostream& operator<<(std::ostream &_out, const Vec<U> &_vec);

private:
        int size;
        T *values;
    };

    template<class T>
    int Vec<T>::Size() const {
        return this->size;
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

    template<class U>
    std::ostream& operator<<(std::ostream &_out, const Vec<U> &_vec) {
        for (int i = 0; i < _vec.size; i++) {
            _out << _vec.values[i] << std::endl;
        }
        return _out;
    }
}