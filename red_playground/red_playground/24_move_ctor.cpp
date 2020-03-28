//
//  24_move_ctor.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;

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
    
    //'simple_vector&& other' is a non-const reference to a temp object, that we want to move
    simple_vector(simple_vector&& other) {
        array = other.array;
        capacity_ = other.capacity_;
        size_ = other.size_;
        
        other.array = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
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
    
    void operator=(simple_vector&& rhs) {
        array = rhs.array;
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        
        rhs.array = nullptr;
        rhs.size_ = 0;
        rhs.capacity_ = 0;
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

void showNullptrDeletion() {
    int* a = nullptr;
    delete a;
    cout << "deleting a nullptr doesn't cause a crash" << endl;
}

template<typename T>
void printMove(const simple_vector<T>& v) {
    if (v.size() == 0) {
        cout << "(empty)" << endl;
    }
    
    for (const T& item : v) {
        cout << item << " ";
    }
    cout << endl;
}

void showMoveAssignment() {
    simple_vector<int> source(1);
    source.push_back(100500);
    
    simple_vector<int> target(2);
    target = move(source);
    
    cout << "target size = " << target.size() << endl;
    printMove(target);
    
    cout << endl;
    
    cout << "source size = " << source.size() << endl;
    printMove(source);
}

void showMoveAssignmentCtor() {
    simple_vector<int> source(1);
    source.push_back(100500);
    
    simple_vector<int> target(move(source));
    
    cout << "target size = " << target.size() << endl;
    printMove(target);
    
    cout << endl;
    
    cout << "source size = " << source.size() << endl;
    printMove(source);
}

void vectorExample() {
    vector<int> target;
    vector<int> source;
    
    //call to 'operator=(const vector<int>&)'
    //copying is done
    target = source;
    
    //call to 'operator=(vector<int>&&)'
    //move is done
    target = vector<int>(5);
    
    //call to 'operator=(vector<int>&&)'
    //move is done
    target = move(source);
}

int main24() {
//    vectorExample();
//    showMoveAssignment();
    showMoveAssignmentCtor();
    
    return 0;
}
