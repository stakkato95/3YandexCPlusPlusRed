//
//  15_assignment_stack_vector.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/19/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <array>

#include <stdexcept>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector() : size { 0 } { }
    
    T& operator[](size_t index) {
        checkIndexOverflow();
        return items[index];
    }
    
    const T& operator[](size_t index) const {
        checkIndexOverflow();
        return items[index];
    }
    
    T* begin() { return &items[0]; }
    T* end() { return &items[size]; } // return pointer to the element BEHIND the last one
    const T* begin() const { return &items[0]; }
    const T* end() const { return &items[size]; } // return pointer to the element BEHIND the last one
    
    size_t Size() const { return size; }
    size_t Capacity() const { return N; }
    
    void PushBack(const T& value) {
        if (size == N) {
            throw overflow_error("stack is full");
        }
        
        items[size++] = value;
    }
    T PopBack() {
        if (size == 0) {
            throw underflow_error("stack is empty");
        }
        
        return items[--size];
    }
    
private:
    array<T, N> items;
    size_t size;
    
    void checkIndexOverflow(size_t index) {
        if (index > size - 1) {
            throw invalid_argument("index out of bounds");
        }
    }
};

void print(StackVector<int, 10>& v) {
    for (int* i = v.begin(); i < v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

int main15() {
    StackVector<int, 10> v;
    
    for (int i = 0; i < 5; ++i) {
        v.PushBack(i);
    }
    print(v);
    
    int removed = v.PopBack();
    cout << "removed=" << removed << endl;
    print(v);
    
    return 0;
}
