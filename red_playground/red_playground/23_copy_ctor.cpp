//
//  23_copy_ctor.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;

class Logger {
public:
    Logger() { cout << "Normal ctor" << endl; }
    Logger(const Logger&) { cout << "Copy ctor" << endl; }
    
    void operator=(const Logger&) { cout << "Assignment operator" << endl; }
};

template<typename T>
class simple_vector {
public:
    simple_vector(size_t size) {
        capacity_ = size;
        array = new T[size];
    }
    
    simple_vector(const simple_vector& other) {
        cout << "copy ctor is called" << endl;
        
        capacity_ = other.capacity_;
        size_ = other.size_;
        
        array = new T[capacity_];
        copy(other.begin(), other.end(), begin());
        
        //WRONG CODE. 'delete[] array;' shouldn't be called
//        T* newData = new T[size_];
//        copy(begin(other.array), end(other.array), begin(newData));
//        delete[] array;
//        array = newData;
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
    
    void operator=(const simple_vector& rhs) {
        if (capacity_ >= rhs.capacity_) {
            cout << "copy called" << endl;
            copy(rhs.begin(), rhs.end(), begin());
            size_ = rhs.size_;
            return;
        }
        
        //copy-and-swop idiom
        cout << "copy-and-swop called. calling copy ctor..." << endl;
        simple_vector temp(rhs);
        swap(temp.array, array);
        swap(temp.capacity_, capacity_);
        swap(temp.size_, size_);
    }
    
    T* begin() { return array; }
    T* end() { return array + size_; }
    
    const T* begin() const { return array; }
    const T* end() const { return array + size_; }
    
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

void showCopyCasesVector() {
    vector<int> source { 1, 2, 3 };
    
    
    //in both cases 'copy ctor' is called
    //RULE TO REMEMBER. Creation of a new instance is always 'copy ctor'
    vector<int> target2(source);
    vector<int> target1 = source;
    
    
    
    //'copy assignment operator' is called
    vector<int> target3 { 4, 5, 6 };
    target3 = source;
    target3.operator=(source);
}

void showCopyCases() {
    cout << "create new instance" << endl;
    Logger a1;
    
    cout << endl << "copy ctors" << endl;
    Logger a2(a1);
    Logger a3 = a1;
    vector<Logger> v;
    v.push_back(a1);
    
    cout << endl << "create new instance" << endl;
    Logger a4;
    cout << endl << "copy assignment operator" << endl;
    a4 = a1;
}

template<typename T>
void print(const simple_vector<T>& v) {
    for (const T& item : v) {
        cout << item << " ";
    }
    cout << endl;
}

void showCopyCasesSimpleVectorCopyCtor() {
    simple_vector<int> v1(1);
    v1.push_back(1);
    v1.push_back(2);
    
    simple_vector<int> v2 = v1;
    v2.push_back(3);
    
    print(v2);
    print(v1);
}

void showCopyCasesSimpleVectorAssignOperator() {
    simple_vector<int> v1(4);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    
    simple_vector<int> v2(8);
    v2 = v1;
    print(v2);
    
    cout << endl;
    
    simple_vector<int> v3(3);
    v3 = v1;
    print(v3);
}

int main23() {
//    showCopyCases();
//    showCopyCasesSimpleVectorCopyCtor();
    showCopyCasesSimpleVectorAssignOperator();
    
    
    
    return 0;
}
