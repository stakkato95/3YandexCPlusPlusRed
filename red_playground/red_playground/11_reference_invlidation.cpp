//
//  11_reference_invlidation.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/19/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

using namespace std;

int overwriteStack() {
    int a = 100;
    int b = 100;
    int c = 400;
    int d = 900;
    return a + b + c + d;
}

//error, because client now have to take care of all the reference handling
int& returnNumber(int num) {
    int a = num;
    return a;
}

int main11() {
    //reference to a deleteted value
//    int* a = new int(12);
//    int& refA = *a;
//    delete a;
//    cout << "deleted a = " << refA << endl;
    
    
    //error - won't compile
//    int* b;
//    int& refB = *b;
//    cout << "random location in memory b = " << refB << endl;
    
    
    //reference handling
    int& c = returnNumber(10);
    
    return 0;
}
