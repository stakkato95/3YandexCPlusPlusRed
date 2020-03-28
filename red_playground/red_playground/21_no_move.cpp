//
//  21_no_move.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/20/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <vector>

#include <string>

#include <utility>

using namespace std;

string makeString() {
    return "c++";
}

int main21() {
    //don't use move semantics
    //1 for copying 'const' variables. it doesn't work
    vector<string> v;
    const string str = makeString();
    cout << str << endl;
    v.push_back(move(str));
    cout << str << " - no effect on 'const string'" << endl;
    
    //2 for copying variables on stack. like move() on a function wich returns std::array
    
    return 0;
}
