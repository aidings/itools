#ifndef ITOOLS_H_
#define ITOOLS_H_
#include "libnpy/npy.hpp"
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>

using namespace std;


namespace itools{

template <typename ScaleValue>
class Matrix{
public:
    Matrix(std::vector<unsigned long int> shape, ScaleValue* data=NULL){

        this->shape = shape;
        int64_t size = accumulate(shape.begin(), shape.end(), 1, multiplies<int64_t>());
        assert(size > 0);
        if(data == NULL){
            this->data = vector<ScaleValue>(size);
        }
        else{
            this->data = vector<ScaleValue>(data, data+size);
        }
    }

    void save(const std::string &filename){
        npy::npy_data<ScaleValue> d;
        d.data = this->data;
        d.shape = this->shape;
        d.fortran_order = false;
        npy::write_npy<ScaleValue>(filename, d);
    }

    void load(const std::string &filename){
        npy::npy_data<ScaleValue> data = npy::read_npy<ScaleValue>(filename);
        this->data = data.data;
        this->shape = data.shape;
    }

    void reshape(std::vector<unsigned long int> shape){
        int64_t size = accumulate(shape.begin(), shape.end(), 1, multiplies<int64_t>());
        assert(size == this->data.size());
        this->shape = shape;
    }

    void show(){
        int32_t s = 1;
        std::vector<int32_t> shapes;
        cout << "matrix shape: " << "[";
        for (int i = 0; i < this->shape.size(); i++){
            if (i == this->shape.size()-1)
                cout << this->shape[i] << "]" << endl;
            else
                cout << this->shape[i] << " ";

            s *= this->shape[i]; 
            shapes.push_back(s);
        }
        cout << "data: " << endl;
        for (int i = 0; i < this->data.size(); i++){
            cout << this->data[i] << endl;
        }
    }

    const ScaleValue* get_data(){
        return this->data.data();
    }

    std::vector<unsigned long int>& get_shape(){
        return this->shape;
    }

private:
    vector<ScaleValue> data;
    vector<unsigned long int> shape;
};
};

#endif