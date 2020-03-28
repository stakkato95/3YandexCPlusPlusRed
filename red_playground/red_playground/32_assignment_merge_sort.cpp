//
//  32_assignment_merge_sort.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/23/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <string>

#include <vector>

using namespace std;

template<typename RndIt>
void merge(RndIt start, RndIt middle, RndIt finish, back_insert_iterator<vector<typename RndIt::value_type>> inserter) {
    RndIt start2 = middle;
    
    while (start != middle && start2 != finish) {
        if (*start < *start2 || start2 == finish) {
            *inserter = move(*start);
            start++;
        } else {
            *inserter = move(*start2);
            start2++;
        }
        inserter++;
    }
    
    if (start != middle) {
        while (start != middle) {
            *inserter = move(*start);
            start++;
            inserter++;
        }
    }
    
    if (start2 != finish) {
        while (start2 != finish) {
            *inserter = move(*start2);
            start2++;
            inserter++;
        }
    }
}

template<typename RndIt>
void mergeSort(RndIt start, RndIt finish) {
    if (finish - start == 1) {
        return;
    }
    
    int m = (finish - start) / 2;
    RndIt middle = next(start, m);
    
    mergeSort(start, middle);
    mergeSort(middle, finish);
    
    vector<typename RndIt::value_type> temp;
    merge<RndIt>(start, middle, finish, back_inserter(temp));
    
    RndIt it = start;
    for (typename RndIt::value_type& item : temp) {
        *it = move(item);
        it++;
    }
}

template<typename T>
void printArray(vector<T> v) {
    for (const T& item : v) {
        cout << item << " ";
    }
    cout << endl;
}

void sortInts() {
    vector<int> v { 38, 27, 43, 3, 9, 82, 10 };
    mergeSort(begin(v), end(v));
    printArray(v);
}

void sortStrings() {
    vector<string> v { "e", "d", "f", "a", "b", "g", "c" };
    mergeSort(begin(v), end(v));
    printArray(v);
}

int main32() {
//    sortInts();
//    sortStrings();
    
    
    return 0;
}
