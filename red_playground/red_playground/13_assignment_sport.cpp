//
//  13_sport_assignment.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/19/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
#include <map>

using namespace std;

void placeSportsman(list<int>& row, int number, int putBefore) {
    row.remove(number);
    list<int>::iterator it = find(begin(row), end(row), putBefore);
    row.insert(it, number);
}

void print(const list<int>& row) {
    for (const int& i : row) {
        cout << i << " ";
    }
    cout << endl;
}

int main13() {
    list<int> row { 5 };
    placeSportsman(row, 42, 0);
    placeSportsman(row, 17, 42);
    placeSportsman(row, 13, 0);
    placeSportsman(row, 123, 42);
    placeSportsman(row, 5, 13);
    print(row);

    return 0;
}
