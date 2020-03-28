//
//  2_cout_cin.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 2/27/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <random>

using namespace std;

struct Widget {
    Widget() {
        cout << "created" << endl;
    }
    
    ~Widget() {
        cout << "deleted" << endl;
    }
};

void testPointers() {
    int* pInt = new int;
    *pInt = 12;
    cout << *pInt << endl;
    
    int& refInt = *pInt;
    cout << refInt << endl;
    refInt = 13;
    cout << refInt << endl;
    cout << *pInt << endl;
}

void testRandom() {
    mt19937_64 rangom_gen;
    uint64_t i = rangom_gen();
}

void testCtorDestructor() {
    Widget* w = new Widget;
    delete w;
}

int main4() {
//    testPointers();
//    testRandom();
    testCtorDestructor();
    
    return 0;
}
