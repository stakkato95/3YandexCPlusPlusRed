//
//  36_assignment_synchronized_wrapper.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/27/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <mutex>

#include <utility>

using namespace std;

template<typename T>
class synchronized {
public:
    synchronized(T initial = T()) : value { move(initial) } { }
    
    struct access {
        T& value_ref;
        lock_guard<mutex> lock;
    };
    
    access getAccess() {
        return { value, lock_guard<mutex>(m) };
    }
private:
    T value;
    mutex m;
};

int main36() {
    synchronized<int> sync;
    {
        auto a = sync.getAccess();
        a.value_ref = 10;
    }
    
    cout << sync.getAccess().value_ref << endl;
    
    return 0;
}
