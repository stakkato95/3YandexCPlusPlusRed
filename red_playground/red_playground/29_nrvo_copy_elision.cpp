//
//  29_nrvo_copy_elision.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

using namespace std;

class NRVOandCopyElision {
public:
    NRVOandCopyElision() { cout << "created" << endl; }
    NRVOandCopyElision(const NRVOandCopyElision& other) { cout << "copied" << endl; }
};

NRVOandCopyElision getObjectNRVO() {
    NRVOandCopyElision obj;
    
    //(some heavy work with the object)
    
    //named return value optimization
    //object will assigned directly to a2 without copying it.
    
    return obj;
}

NRVOandCopyElision getObjectCopyElision() {
    //copy elision. object will assigned directly to a1 without copying it.
    return NRVOandCopyElision();
}

int main29() {
    //copy ctors aren't called at all!
    NRVOandCopyElision a1 = getObjectCopyElision();
    NRVOandCopyElision a2 = getObjectNRVO();
    return 0;
}
