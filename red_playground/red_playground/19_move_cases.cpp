//
//  19_move_cases.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/20/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <vector>

#include <string>

using namespace std;

string getStr() {
    return string(10500, 'a');
}

int main19() {
    vector<string> strs;
    
    //bad code.temporary variable is created on stack
    string s = getStr();
    strs.push_back(s);
    
    //good code. vector automatically points to the string. string is added instantaneously
    strs.push_back(getStr());
    
    //move can happen everywhere, where copying happens
    //1 initialisaiton
    //2 assignment of an existing object with value of another object
    //3 adding elements into container
    //
    //RULE - pass temp objects directly where they are supposted to be used
    //(inserted into collection, assigned to an existing object, see the list above)
    
    return 0;
}
