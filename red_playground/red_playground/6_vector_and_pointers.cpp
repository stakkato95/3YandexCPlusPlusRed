//
//  6_vector_and_pointers.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/16/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <string>

#include <algorithm>

using namespace std;

template<typename T>
class my_vector {
public:
    my_vector(size_t size) {
        data = new T[size];
        end_ = data + size;
    }
    
    T& operator[](size_t i) {
        return *(data + i);// equivalent to data[i]
    }
    
    //non-constant begin() and end() are called when object is passed without 'const'
    T* begin() {
        return data;
    }
    T* end() {
        return end_;
    }
    
    //begin() method is necessary for foreach and standard algorithms
    //foreach reqires const method, if 'for (const auto& ...)'
    //const return pointer in order not to overwrite value in the loop
    const T* begin() const {
        return data;
    }
    
    //end() method is necessary for foreach and standard algorithms
    //foreach reqires const method, if 'for (const auto& ...)'
    //const return pointer in order not to overwrite value in the loop
    const T* end() const {
        return end_;
    }
    
    ~my_vector() {
        delete[] data;
    }
private:
    T* data;
    T* end_;
};

void testMyVector() {
    my_vector<int> nums(5);
    
    for (int i = 0; i < 5; i++) {
        nums[i] = 5 - i;
    }
    
    for (int i = 0; i < 5; i++) {
        cout << nums[i] << endl;
    }
}

void testMyVectorIteration() {
    my_vector<int> nums(5);
    
    for (int i = 0; i < 5; i++) {
        nums[i] = 5 - i;
    }
    
    sort(nums.begin(), nums.end());
    
    cout << "Sorting and iteration with foreach" << endl;
    bool prontDivider = false;
    for (int i : nums) {
        if (prontDivider) {
            cout << ", ";
        }
        prontDivider = true;
        cout << i;
    }
    cout << endl;
}

template<typename T>
void testMyVectorImmutablePrint(const my_vector<T>& v) {
    cout << "Iteration with immutable items in loop" << endl;
    //foreach requires begin() and end() to be const methods
    for (const T& item : v) {
        cout << item << " ";
    }
    cout << endl;
    
    cout << "Iteration with for loop based on iteratos" << endl;
    //foreach unrolls into
    for (const T* it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void testMyVectorImmutability() {
    my_vector<int> nums(5);
    
    for (int i = 0; i < 5; i++) {
        nums[i] = 5 - i;
    }
    
    testMyVectorImmutablePrint(nums);
}

void pointerArithmetic() {
    //like in normal C
    int x = 5;
    int* xAdressOnStack = &x;
    cout << "xAdressOnStack = " << xAdressOnStack << ", x = " << x << endl;
    
    *xAdressOnStack = 7;
    cout << "new x = " << x << endl;
}

void pointersShiftInStack() {
    int a = 1;
    int b = 2;
    int c = 3;
    
    cout << "[ " << *(&b - 1) << ", " << *(&b + 1) << " ]" << endl;
}

void constPointerAndPointerToConstant() {
    int x = 5;
    
    //normal pointer. x is mutable. xPtr is mutable.
    int* xPtr = &x;
    
    //pointer to constant value. x is IMmutable. constX is mutable.
    const int* constX = &x;
    
    //constant pointer to constant value. x is IMmutable. constXconstPtr is IMmutable.
    const int* const constXconstPtr = &x;
}

int main6() {
//    testMyVector();
//    testMyVectorIteration();
//    testMyVectorImmutability();
//    pointerArithmetic();
//    pointersShiftInStack();
//    constPointerAndPointerToConstant();
    
    return 0;
}
