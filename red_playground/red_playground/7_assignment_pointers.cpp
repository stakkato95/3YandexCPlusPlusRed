//
//  7_pointers_assignment.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/16/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;

template <typename T>
void Swap(T* first, T* second) {
    T temp = *first;
    *first = *second;
    *second = temp;
}

template <typename T>
void SortPointers(vector<T*>& pointers) {
    sort(begin(pointers), end(pointers), [](int* a, int* b) { return *a < *b; });
}

void testSwap() {
    int a = 1;
    int b = 2;
    
    Swap(&a, &b);
    
    cout << "a = " << a << ", b = " << b << endl;
}

template <typename T>
void ReversedCopy(T* src, size_t count, T* dst) {
    for (int i = 0; i < count; ++i) {
        *(dst + i) = *(src + count - i - 1);
    }
}

void testSort() {
    vector<int> nums { 1, -4, 8, 0, 12, 4 };
    
    vector<int*> pointers;
    
    for (int i = 0; i < nums.size(); ++i) {
        pointers.push_back(&nums[i]);
    }
    
    SortPointers(pointers);
    
    cout << "pointers ";
    for (int i = 0; i < pointers.size(); ++i) {
        cout << *pointers[i] << " ";
    }
    cout << endl;
    
    cout << "original ";
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

void testReversedCopy() {
    int arr1size = 10;
    int* arr1 = new int[arr1size];
    for (int i = 0; i < arr1size; ++i) {
        *(arr1 + i) = i;
    }
    
    int arr2size = 10;
    int* arr2 = new int[arr2size];
    for (int i = 0; i < arr2size; ++i) {
        *(arr2 + i) = i;
    }
    
    cout << "oroginal" << endl;
    for (int i = 0; i < arr2size; ++i) {
        cout << *(arr2 + i) << " ";
    }
    cout << endl;
    
    ReversedCopy(arr1 + 5, 5, arr2 + 5);
    
    cout << "copied\n";
    for (int i = 0; i < arr2size; ++i) {
        cout << *(arr2 + i) << " ";
    }
    cout << endl;
}

int main7() {
//    testSwap();
//    testSort();
//    testReversedCopy();
    
    return 0;
}
