#pragma once
#include <cassert>
#include <iostream>

namespace PANSFE {
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

        template<class U>
	    friend std::ostream& operator<<(std::ostream &_out, const Mat<U> &_mat);

private:
        int row, col;
        T *values;
    };

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
}