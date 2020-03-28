//
//  8_simple_vector.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/17/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <cassert>

template<typename T>
class simple_vector {
public:
    simple_vector(size_t size) {
        capacity_ = size;
        array = new T[size];
    }
    
    ~simple_vector() {
        delete[] array;
    }
    
    size_t size() const { return size_; }
    
    size_t capacity() const {
        return capacity_;
    }
    
    void push_back(T element) {
        ensureSize();
        array[size_++] = element;
    }
    
    T& operator[](size_t i) {
        return array[i];
    }
    
    const T* begin() const { return array; }
    const T* end() const { return array + size_; }
    
    T* begin() { return array; }
    T* end() { return array + size_; }
    
private:
    size_t size_;
    size_t capacity_;
    T* array;
    
    void ensureSize() {
        if (capacity_ == size_) {
            capacity_ *= 2;
            T* newArray = new T[capacity_];
            for (int i = 0; i < size_; ++i) {
                newArray[i] = array[i];
            }
            
            delete[] array;
            array = newArray;
            
        }
    }
};

int main8() {
    simple_vector<int> v(2);
    v.push_back(1);
    v.push_back(2);
    
    assert(v.size() == 2);
    assert(v.size() == v.capacity());
    
    v.push_back(3);
    assert(v.capacity() == 4);
    assert(v.size() == 3);
    
    
    return 0;
}
