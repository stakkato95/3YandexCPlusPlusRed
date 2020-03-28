//
//  14_array.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/19/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <tuple>
#include <array>
#include <vector>

#include <string>

#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

class TimeMeasurement {
public:
    TimeMeasurement(string n) {
        name = n;
        start = system_clock::now();
    }
    ~TimeMeasurement() {
        long long runtime = duration_cast<milliseconds>(system_clock::now() - start).count();
        cout << name << " : " << runtime << " millisec" << endl;
    }
private:
    system_clock::time_point start;
    string name;
};

vector<int> getVector(const int i) {
    //vector, which is always allocated on heap
    return { i, i + 1, i + 2, i + 3, i + 4 };
}

tuple<int, int, int, int, int> getTuple(const int i) {
    //normal tuple like in python
    return make_tuple(i, i + 1, i + 2, i + 3, i + 4 );
}

array<int, 5> getArray(const int i) {
    //array, which is stored on !!!STACK!!!. performance feature
    return { i, i + 1, i + 2, i + 3, i + 4 };
}

int main14() {
    const int n = 10'000'000;
    
    {
        TimeMeasurement t("vector");
        for (int i = 0; i < n; ++i) {
            getVector(i);
        }
    }
    {
        TimeMeasurement t("tuple");
        for (int i = 0; i < n; ++i) {
            getTuple(i);
        }
    }
    {
        TimeMeasurement t("array");
        for (int i = 0; i < n; ++i) {
            getArray(i);
        }
    }
    
    return 0;
}
