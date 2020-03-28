//
//  12_iterator_invalidation.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/19/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void vectorInvalidatesIterators() {
    vector<int> v { 1 };
    vector<int>::iterator it = begin(v);
    
    cout << "vector. before insertions [0] = " << *it << endl;
    
    for (int i = 0; i < 2000; ++i) {
        v.push_back(i);
    }
    
    //iterator is completely invalidated
    cout << "vector. after insertions [0] = " << *it << endl;
}

void dequeKeepsIterators() {
    deque<int> d { 1 };
    deque<int>::iterator it = begin(d);
    
    cout << "deque.  before insertions [0] = " << *it << endl;
    
    for (int i = 0; i < 2000; ++i) {
        d.push_back(i);
    }
    
    //iterator of a deque (after insertion of elements) is valid ONLY for collection BEFORE insertions
    //old iterator knows nothing about new collection
    cout << "deque.  after insertions [0] = " << *it << endl;
    
    //it will cause srash, since old iterator knows nothing about new size of the collection
//    cout << "deque.  after insertions [last] = " << *(it + d.size() - 1) << endl;
}

void listIterators() {
    //are not invalidated in any case
}

int main12() {
    //pointer points to any place in memory.           can move in any direction.             knows nothing about structure of container.
    //reference points only to one place in memory.    can't move.                            knows nothing about structure of container.
    //iterator points only to elements of a container. can move over elements of a container. knows structure of container.
    
    vectorInvalidatesIterators();
    dequeKeepsIterators();
    listIterators();
    
    return 0;
}
