//
//  28_what_cant_be_copied.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <string>

#include <vector>

using namespace std;

class Uncopied {
public:
    Uncopied() { cout << "created" << endl; }
    Uncopied(const Uncopied& other) = delete;
    Uncopied(Uncopied&& rhs) { cout << "moved" << endl; }
};

void showCustomUncopiedClass() {
    Uncopied source1;
    Uncopied source2;
    
    //compilation error
    //    Uncopied target1(source1);
    //    Uncopied target2 = source2;
    
    //compiles
    
    Uncopied target1(move(source1));
    Uncopied target2 = move(source2);
}

void showSystemUncopiedClasses() {
    vector<ofstream> v;
    v.reserve(5);
    
    for (int i = 0; i < v.capacity(); ++i) {
        ofstream stream(to_string(i) + ".txt");
//        v.push_back(stream); //compilation error. stream can't be copied
        v.push_back(move(stream));
    }
    
    for (ofstream& stream : v) {
        stream << "Vector is ready" << endl;
    }
}

int main28() {
    //    showCustomUncopiedClass();
    showSystemUncopiedClasses();
    
    return 0;
}
