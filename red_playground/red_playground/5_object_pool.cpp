//
//  5_object_pool.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/16/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <stdio.h>

#include <queue>
#include <vector>
#include <string>

#include <algorithm>
#include <exception>
#include <cassert>

using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        T* obj = TryAllocate();
        
        if (obj == nullptr) {
            obj = new T;
        }
        
        allocated.push_back(obj);
        
        return obj;
    }
    
    T* TryAllocate() {
        if (deallocated.empty()) {
            return nullptr;
        }
        
        T* obj = deallocated.front();
        deallocated.pop();
        return obj;
    }
    
    void Deallocate(T* object) {
        auto it = find(begin(allocated), end(allocated), object);
        if (it == end(allocated)) {
            throw invalid_argument("object doesn't belong to the pool");
        }
        
        deallocated.push(*it);
        allocated.erase(it);
    }
    
    ~ObjectPool() {
        while (allocated.size() != 0) {
            T* obj = allocated[allocated.size() - 1];
            delete obj;
            allocated.pop_back();
        }
        
        while (deallocated.size() != 0) {
            T* obj = deallocated.front();
            delete obj;
            deallocated.pop();
        }
    }

private:
    vector<T*> allocated;
    queue<T*> deallocated;
};

void testPool() {
    ObjectPool<string> pool;
    
    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();
    
    *p1 = "first";
    *p2 = "second";
    *p3 = "third";
    
    pool.Deallocate(p2);
    assert(*pool.Allocate() == "second");
    
    pool.Deallocate(p3);
    pool.Deallocate(p1);
    assert(*pool.Allocate() == "third");
    assert(*pool.Allocate() == "first");
    
    pool.Deallocate(p1);
}

int main5() {
    testPool();
    
    return 0;
}
