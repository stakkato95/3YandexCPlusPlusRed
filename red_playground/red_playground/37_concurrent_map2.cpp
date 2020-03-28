//
//  38_concurrent_map2.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/27/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <map>
#include <vector>

#include <mutex>
#include <future>

#include <string>

#include <algorithm>
#include <random>

#include <chrono>
#include <ctime>

using namespace std;

using namespace std::chrono;

class my_lock {
public:
    my_lock(mutex& mtx) : m { mtx }, isLocked { true } {
        m.lock();
    }
    
    ~my_lock() {
        m.unlock();
    }
    
    operator bool() {
        return isLocked;
    }
    
    void setUnlocked() {
        isLocked = false;
    }
private:
    mutex& m;
    bool isLocked;
};

#define my_synchronized(mutx) for(my_lock lck = my_lock(mutx); lck; lck.setUnlocked())

template<typename K, typename V>
class my_concurrent_map {
public:
    explicit my_concurrent_map(size_t parallelThreads) : sections { vector<mutex>(parallelThreads) } { }
    
    my_concurrent_map() : sections { vector<mutex>(thread::hardware_concurrency()) } { }
    
    V& get(const K& key) const {
        return table[hash<K>{}(key)];
    }
    
    void put(const K& key, const V& value) {
        size_t hashValue = hash<K>{}(key);
        mutex& mtx = sections[hashValue % sections.size()];
        
        my_synchronized(mtx) {
            table[key] = value;
        }
    }
private:
    vector<mutex> sections;
    map<K, V> table;
};

void threadRoutine(my_concurrent_map<int, int>& concurrentMap, int seed, size_t repeatTimes) {
    vector<int> updates(500000 * repeatTimes);
    iota(begin(updates), end(updates), -updates.size() / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));
    for (const int& i : updates) {
        concurrentMap.put(i, i);
    }
    
//    cout << this_thread::get_id() << " finished" << endl;
}

void showSingleThread(size_t mutexCount, size_t threadsCount, size_t repeatTimes) {
    my_concurrent_map<int, int> concurrentMap(mutexCount);
    
    auto start = system_clock::now();
    
    vector<future<void>> f;
    for (size_t i = 0; i < threadsCount; ++i) {
        f.push_back(async(launch::async, threadRoutine, ref(concurrentMap), i, repeatTimes));
    }
    for (const future<void>& fut : f) {
        fut.wait();
    }
    
    auto end = system_clock::now();
    long result = duration_cast<milliseconds>(end - start).count();
    
    cout << "mutexCount=" << mutexCount << ", threadsCount=" << threadsCount << ", result=" << result << " millis" << endl;
}

int main37() {
    cout << "ONE MUTEX" << endl;
    showSingleThread(1, 1, 8);
    showSingleThread(1, 8, 1);
    
    cout << endl << "MULTIPLE MUTEX" << endl;
    showSingleThread(4, 4, 2);
    showSingleThread(8, 8, 1);
    
    return 0;
}
