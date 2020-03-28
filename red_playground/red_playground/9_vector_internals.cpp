//
//  9_vector_internals.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/17/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <vector>

#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

void checkSizeAndCapacity(const vector<int>& v) {
    //const pointer since 'const vector<int>& v'
    const int* data = v.data();
    
    cout << "size" << endl;
    for (size_t i = 0; i < v.size(); i++) {
        cout << *(data + i) << " ";
    }
    cout << endl;
    
    cout << "capacity" << endl;
    for (size_t i = 0; i < v.capacity(); i++) {
        cout << *(data + i) << " ";
    }
    cout << endl;
}

void shrinkToFit(vector<int>& v) {
    cout << "capacity before = " << v.capacity() << endl;
    v.shrink_to_fit();
    cout << "capacity after = " << v.capacity() << endl;
}

int vectorInsert(vector<int>& v, size_t size) {
    auto start = system_clock::now();
    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }
    auto end = system_clock::now();
    
    return duration_cast<milliseconds>(end - start).count();
}

void resizeForBigVectors() {
    size_t size = 20000000;
    
    vector<int> v; 
    
    cout << "without resize " << vectorInsert(v, size) << endl;
    
    vector<int> v1;
    v1.resize(size);
    cout << "with resize " << vectorInsert(v1, size) << endl;
    
    vector<int> v2(size);
    cout << "with resize " << vectorInsert(v2, size) << endl;
}

int main9() {
//    vector<int> v { 1, 2, 3 };
//    v.push_back(4);
//    checkSizeAndCapacity(v);
//    shrinkToFit(v);
    
    resizeForBigVectors();
    
    return 0;
}
