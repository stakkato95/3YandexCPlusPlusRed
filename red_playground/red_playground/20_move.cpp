//
//  20_move.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/20/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <sstream>

#include <string>

#include <vector>

#include <utility>

using namespace std;

void showCopyingStrings() {
    string s1 = "hello";
    string s2 = s1;
    
    s2.append(" world");
    
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
}

void showCopyingStringsToVector() {
    vector<string> v;
    
    string s1 = "hello";
    v.push_back(s1);
    
    s1.append("1");
    v[0].append("2");
    
    v.push_back("hello");
    string* s3 = &v[1];
    s3->append("3");
    v[1].append("4");
    
    v.push_back("hello");
    string& s4 = v[2];
    s4.append("5");
    v[2].append("6");
    
    cout << "str = " << s1 << endl;
    cout << "v[0] = " << v[0] << endl;
    cout << endl;
    cout << "s3 = " << *s3 << endl;
    cout << "v[1] = " << v[1] << endl;
    cout << endl;
    cout << "s4 = " << s4 << endl;
    cout << "v[2] = " << v[2] << endl;
}

void showCopyingVectors() {
    //when adding a string to a vector its value is copied completely (char array is copied)
    //so, move semantics avoids copying a temporary value to array and stores the value itself in array
    
    vector<string> s1 { "hello" };
    vector<string> s2 = s1;
    vector<string> s3 { s1[0] };
    
    s1[0].append("1");
    s2[0].append("2");
    s3[0].append("3");
    
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s2[0] = " << s2[0] << endl;
    cout << "s3[0] = " << s3[0] << endl;
}

////////////////////////////////////////////////////////////////////////////////

vector<string> readString(istream& stream, bool useMove) {
    cout << "useMove = " << (useMove ? "true" : "false") << endl;
    
    vector<string> strs;
    string temp;
    while (stream >> temp) {
        if (useMove) {
            cout << "before = \"" << temp;
            
            //after calling move 'readString' doesn't own the value of temp object anymore
            strs.push_back(move(temp));
            
            cout << "\", after = \"" << temp << "\"" << endl;
        } else {
            //'readString' has access to the original value of temp
            //and vector 'strs' has a copy of it (deep copy, char array is copied)
            strs.push_back(temp);
        }
    }
    
    return strs;
}

void showMoveSemantics() {
    string text = "hello world c++ java programming python c c#";
    istringstream ss(text);
    
    readString(ss, false);
    
    cout << endl;
    ss.clear();
    ss.seekg(0, ios::beg);
    readString(ss, true);
}

////////////////////////////////////////////////////////////////////////////////

vector<string> syntheticSplitIntoWords(const string& str) {
    vector<string> result;
    string temp;
    
    for (const char c : str) {
        if (c == ' ') {
            result.push_back(temp);
            temp.clear();
        } else {
            temp.push_back(c);
        }
    }
    result.push_back(temp);
    
    return result;
}

vector<string> syntheticSplitIntoWordsWithMove(const string& str) {
    vector<string> result;
    string temp;
    
    for (const char c : str) {
        if (c == ' ') {
            result.push_back(move(temp));
        } else {
            temp.push_back(c);
        }
    }
    result.push_back(move(temp));
    
    return result;
}

void print(const vector<string>& v) {
    for (const string& s : v) {
        cout << s << " ";
    }
    cout << endl;
}

void showMoveSemanticsTwo() {
    string text = "hello world c++ java programming python c c#";
    
    vector<string> s1 = syntheticSplitIntoWords(text);
    print(s1);
    
    vector<string> s2 = syntheticSplitIntoWordsWithMove(text);
    print(s2);
}


int main20() {
//    showCopyingStrings();
//    showCopyingStringsToVector();
//    showCopyingVectors();
//    showMoveSemantics();
//    showMoveSemanticsTwo();
    
    //move says compiler that an object is a temporary one
    //and the object (or its content, like with string) won't be used in current function
    
    return 0;
}
