//
//  2_cout_cin.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 2/27/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <set>

using namespace std;

int main3() {
    set<int> numbers;
    for (int i = 0; i < 1000000; i++) {
        numbers.insert(i);
    }
    const int x = 10000;
    
    //works slower
    cout << *lower_bound(begin(numbers), end(numbers), x) << endl;
    
    //works faster
    cout << *numbers.lower_bound(x) << endl;
    
    
    return 0;
}
