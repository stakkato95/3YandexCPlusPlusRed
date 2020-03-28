//
//  16_string_view.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/19/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <vector>

#include <string>
#include <string_view>

using namespace std;

vector<string> splitIntoWords(const string& str) {
    vector<string> result;
    
    string::const_iterator previousSpaceIt = begin(str);
    string::const_iterator spaceIt = begin(str);
    
    while (spaceIt != end(str)) {
        spaceIt = find(previousSpaceIt, end(str), ' ');
        
        if (*spaceIt == ' ') {
            result.push_back(string(previousSpaceIt, spaceIt));
            previousSpaceIt = spaceIt + 1;
        }
    }
    
    result.push_back(string(previousSpaceIt, end(str)));
    
    return result;
}

vector<string_view> splitIntoViews(const string& s) {
    string_view str = s;
    
    vector<string_view> result;
    
    size_t previousSpace = 0;
    size_t currentSpace = 0;
    
    
    while (true) {
        currentSpace = str.find(' ', previousSpace);
        
        bool isEndReached = currentSpace == str.npos;
        result.push_back(isEndReached ? str.substr(previousSpace) : str.substr(previousSpace, currentSpace - previousSpace));
        
        if (currentSpace == str.npos) {
            break;
        }
        previousSpace = currentSpace + 1;
    }
    
    return result;
}

vector<string_view> splitIntoViewsOptimized(string_view s) {
    string_view str = s;
    
    vector<string_view> result;
    
    while (true) {
        size_t space = str.find(' ');
        
        result.push_back(str.substr(0, space));
        
        if (space == str.npos) {
            break;
        }
        str.remove_prefix(space + 1);
    }
    
    return result;
}

void testSplitString() {
    string str = "hello world !";
    vector<string> strs = splitIntoWords(str);
    for (const string& str : strs) {
        cout << "|" << str << "|" << endl;
    }
}

void testSplitStringView() {
    string str = "hello world !";
    vector<string_view> strs = splitIntoViews(str);
    for (const string_view& str : strs) {
        cout << "|" << str << "|" << endl;
    }
}

void testSplitStringViewOptimized() {
    string str = "hello world !";
    vector<string_view> strs = splitIntoViewsOptimized(str);
    for (const string_view& str : strs) {
        cout << "|" << str << "|" << endl;
    }
}

int main16() {
//    testSplitString();
//    testSplitStringView();
    testSplitStringViewOptimized();
    
    return 0;
}
