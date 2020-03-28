//
//  34_concurrency.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/24/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <string>

#include <vector>

#include <future>

//#include <utility>

using namespace std;

string duplicateStrings(const string& s, const string& threadName) {
    cout << "in " << threadName << endl;
    return s + s + s;
}

string doubleDuplicateStrings(const string& s) {
    future<string> future = async([&s] {
        this_thread::sleep_for(1s);
        return duplicateStrings(s, "worker");
    });
    return duplicateStrings(s, "main") + future.get();
}

void howFutureWorks() {
    vector<future<string>> futures;
    
    //1
    string result1 = "";
    for (size_t i = 0; i < 100500; ++i) {
        futures.push_back(async([] {
            //local variable should be there. otherweise doesn't compile
            string hello = "hello world";
            return hello;
        }));
    }
    
    //2
    for (size_t i = 0; i < 100500; ++i) {
        async([] {
            string hello = "hello world";
            return hello;
        });
    }
    
    //3
    for (size_t i = 0; i < 100500; ++i) {
        future<string> f = async([] {
            //local variable should be there. otherweise doesn't compile
            string hello = "hello world";
            return hello;
        });
        f.get();
    }
    
    //2 & 3 are equivalent.
    //it means that next loop iteration doesn't start till previous is finished
    //in 2 at the end of each loop iteration destructor of a future is called
    //method  'get(); is called in destructor and waits till the end of lambda's execution
}

int main34() {
    cout << doubleDuplicateStrings("hello ") << endl;
    return 0;
}
