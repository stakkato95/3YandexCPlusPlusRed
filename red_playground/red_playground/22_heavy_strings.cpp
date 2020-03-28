//
//  22_heavy_strings.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <string>

#include <vector>
#include <map>
#include <set>

#include <cassert>

using namespace std;


vector<vector<string>> GroupHeavyStrings(vector<string> strings) {
    // Напишите реализацию функции,
    // использовав не более 1 копирования каждого символа
    
    map<set<char>, vector<string>> groups;
    
    for (const string& str : strings) {
        
        set<char> key;
        for (const char& c : str) {
            key.insert(c);
        }
        
        groups[move(key)].push_back(move(str));
    }
    
    vector<vector<string>> result;
    //old style
//    for (const pair<set<char>, vector<string>> pair : groups) {
//        result.push_back(move(pair.second));
//    }
    
    //new style
    for (auto& [key, value] : groups) {
        result.push_back(move(value));
    }
    
    return result;
}


void TestGroupingABC() {
    vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    
    assert(groups.size() == 2);
    sort(begin(groups), end(groups));
    assert(groups[0] == vector<string>({"caab", "abc", "bacc"}));
    assert(groups[1] == vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
    vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    
    assert(groups.size() == 4);
    sort(begin(groups), end(groups));
    assert(groups[0] == vector<string>({"laptop", "paloalto"}));
    assert(groups[1] == vector<string>({"law", "wall", "awl"}));
    assert(groups[2] == vector<string>({"port"}));
    assert(groups[3] == vector<string>({"top", "pot"}));
}

void testHowSetWorks() {
    char hello[] = { 'h', 'e', 'l', 'l', 'o' };
    char hallo[] = { 'h', 'a', 'l', 'l', 'o' };
    
    set<char> strs;
    for (const char& c : hello) {
        strs.insert(c);
    }
    for (const char& c : hallo) {
        strs.insert(c);
    }
    
    for (const char& c : strs) {
        cout << c << endl;
    }
}

int main22() {
//    TestGroupingABC();
    TestGroupingReal();
    
    return 0;
}
