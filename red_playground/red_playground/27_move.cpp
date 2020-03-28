//
//  27_move.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <string>

#include <vector>

#include <algorithm>

using namespace std;

template<typename T>
void printMoveIterator(const vector<T>& v, const string& title) {
    cout << title << endl;
    for (const T& item : v) {
        cout << "\"" << item << "\", ";
    }
    cout << endl;
}

int main27() {
    vector<string> source { "hello", "world", "!!!", "bye", "mars", "???" };
    printMoveIterator(source, "source before move");
    
    vector<string> target(make_move_iterator(begin(source)),
                          make_move_iterator(next(begin(source), 5)));
    
    printMoveIterator(source, "source after move");
    printMoveIterator(target, "target move");
    
    
    return 0;
}
