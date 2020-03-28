//
//  31_advanced_vector.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <exception>

#include <utility>

#include <cassert>

using namespace std;

class StringNonCopyable : public string {
public:
    using string::string;
    StringNonCopyable(string&& other) : string(move(other)) {}
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

template<typename T>
class move_vector {
public:
    move_vector() : capacity_ { 4 } {
        data = new T[capacity_];
    }
    
    explicit move_vector(size_t capacity) : capacity_ { capacity }  {
        data = new T[capacity_];
    }
    
    ~move_vector() {
        delete[] data;
    }
    
    T& operator[](size_t index) {
        if (index > size_ - 1) {
            throw invalid_argument("index is out of bounds");
        }
        
        return data[index];
    }
    
    T* begin() { return data; }
    T* end() { return data + size_; }
    
    size_t size() const {
        return size_;
    }
    
    size_t capacity() const {
        return capacity_;
    }
    
    void pushBack(T value) {
        ensureSize();
        data[size_++] = move(value);
    }
    
private:
    T* data;
    size_t size_ = 0;
    size_t capacity_;
    
    void ensureSize() {
        if (size_ == capacity_) {
            T* newData = new T[capacity_ * 2];
            move(begin(), end(), newData);
            
            delete[] data;
            data = newData;
        }
    }
};

void testWithCustomClass() {
    move_vector<StringNonCopyable> strings;
    static const int SIZE = 10;
    for (int i = 0; i < SIZE; ++i) {
        strings.pushBack(StringNonCopyable(to_string(i)));
    }
    for (int i = 0; i < SIZE; ++i) {
        assert(strings[i] == to_string(i));
    }
}

void testWithStream() {
    ifstream stream("text.txt");
    
    move_vector<ifstream> v;
    v.pushBack(move(stream));
    v.pushBack(ifstream ("text1.txt"));
}

int main31() {
    testWithCustomClass();
    testWithStream();
    
    return 0;
}
