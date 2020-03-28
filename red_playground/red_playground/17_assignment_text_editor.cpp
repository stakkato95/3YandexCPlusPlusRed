//
//  17_assignment_text_editor.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/20/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <list>
#include <vector>

#include <string>

using namespace std;

class Editor {
public:
    Editor() : cursorPosition { 0 } { }
    void Left() {
        if (cursorPosition == 0) {
            return;
        }
        
        cursorPosition--;
    }
    
    void Right() {
        if (cursorPosition == text.size()) {
            return;
        }
        
        cursorPosition++;
    }
    
    void Insert(char token) {
        text.insert(next(begin(text), cursorPosition), token);
        Right();
    }
    
    void Copy(size_t tokens) {
        buffer.clear();
        
        list<char>::iterator copyStart = next(begin(text), cursorPosition);
        list<char>::iterator copyEnd = isInBounds(tokens) ? next(begin(text), cursorPosition + tokens) : end(text);
        buffer.insert(begin(buffer), copyStart, copyEnd);
    }
    
    void Cut(size_t tokens) {
        Copy(tokens);
        
        list<char>::iterator eraseStart = next(begin(text), cursorPosition);
        list<char>::iterator copyEnd = isInBounds(tokens) ? next(begin(text), cursorPosition + tokens) : end(text);
        
        text.erase(eraseStart, copyEnd);
    }
    
    void Paste() {
        text.insert(next(begin(text), cursorPosition), begin(buffer), end(buffer));
    }
    
    string GetText() const {
        string txt = string(begin(text), end(text));
        txt.insert(cursorPosition, "|");
        
        return txt;
    }
private:
    list<char> text;
    size_t cursorPosition;
    vector<char> buffer;
    
    bool isInBounds(size_t tokens) {
        return cursorPosition + tokens < text.size();
    }
};

void print(const Editor& editor) {
    cout << "\"" << editor.GetText() << "\"" << endl;
}

int main17() {
    Editor editor;
    
    ///////////////////////////////////////////////////////
    vector<char> hello { 'h', 'e', 'l', 'l', 'o' };
    for (const char& c : hello) {
        editor.Insert(c);
    }
    print(editor);
    
    ///////////////////////////////////////////////////////
    for (size_t i = 0; i < hello.size(); ++i) {
        editor.Left();
    }
    print(editor);
    
    ///////////////////////////////////////////////////////
    editor.Cut(hello.size());
    print(editor);
    
    ///////////////////////////////////////////////////////
    editor.Paste();
    print(editor);
    
    ///////////////////////////////////////////////////////
    for (size_t i = 0; i < hello.size(); ++i) {
        editor.Right();
    }
    print(editor);
    
    ///////////////////////////////////////////////////////
    editor.Insert(' ');
    print(editor);
    
    ///////////////////////////////////////////////////////
    vector<char> world { 'w', 'o', 'r', 'l', 'd' };
    for (const char& c : world) {
        editor.Insert(c);
    }
    print(editor);
    
    ///////////////////////////////////////////////////////
    for (size_t i = 0; i < world.size(); ++i) {
        editor.Left();
    }
    print(editor);
    
    ///////////////////////////////////////////////////////
    editor.Copy(world.size());
    
    ///////////////////////////////////////////////////////
    for (size_t i = 0; i < hello.size() + 1; ++i) {
        editor.Left();
    }
    print(editor);
    
    ///////////////////////////////////////////////////////
    editor.Insert(',');
    print(editor);
    
    ///////////////////////////////////////////////////////
    editor.Left();
    print(editor);
    
    ///////////////////////////////////////////////////////
    editor.Insert(' ');
    editor.Left();
    editor.Paste();
    print(editor);
    
    ///////////////////////////////////////////////////////
    for (size_t i = 0; i < 100; ++i) {
        editor.Right();
    }
    editor.Insert('!');
    print(editor);
    
    ///////////////////////////////////////////////////////
    for (size_t i = 0; i < 100; ++i) {
        editor.Left();
    }
    print(editor);
    
    return 0;
}
