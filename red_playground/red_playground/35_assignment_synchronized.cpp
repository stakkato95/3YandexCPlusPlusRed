//
//  35_assignment_blog_research.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/25/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <mutex>

#include <vector>

#include <future>

using namespace std;

class Lock {
public:
    Lock(mutex& mutex) : m { mutex }, isLocked { true }  {
        m.lock();
    }
    
    operator bool() const { return isLocked; }
    
    void setUnlocked() {
        isLocked = false;
    }
    
    ~Lock() { m.unlock(); }
private:
    mutex& m;
    bool isLocked;
};

#define synchronized(M) for(Lock M##_lock = M; M##_lock; M##_lock.setUnlocked())

mutex m;

void increment(int& counter) {
    counter++;
    cout << counter << endl;
}

void run(int& counter) {
    for (size_t i = 0; i < 30; ++i) {
        synchronized(m) {
            increment(counter);
        }
    }
}

int main35() {
    vector<future<void>> f;
    int count;
    
    for (size_t i = 0; i < 3; ++i) {
        f.push_back(async([&count] { run(count); }));
    }
    
    return 0;
}
