
//
//  25_move_optimisation.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <string>

#include <map>

using namespace std;

class Person {
public:
    Person() = default;
    
    //methdo for calls like
    //person.setName("Kate");
    //where pass a temporary string WITHOUT creating a local variable
//    void setName(string& newName) {
//        objAttrs["name"] = newName;
//    }
    
    //methdo for calls like
    //string name = "Kate";
    //person.setName(name);
    //where pass a temporary string WITH creating a local variable
//    void setName(const string& newName) {
//        objAttrs["name"] = newName;
//    }

    //we replace BOTH methods above with a single method
    //for calls like this 'person.setName("Kate");' we have two moves:
    //1 first happens automatically (passing temp variable to method), because of c++
    //1 second happens because of 'move(newName)'
    void setName(string newName) {
        objAttrs["name"] = move(newName);
    }
    
    void setLastName(string newLastName) {
        objAttrs["lastName"] = move(newLastName);
    }
    
    string getName() {
        return objAttrs["name"];
    }
    
    string getLastName() {
        return objAttrs["lastName"];
    }
    
private:
    map<string, string> objAttrs;
};

int main25() {
    Person p;
    p.setName("");
    
    return 0;
}
