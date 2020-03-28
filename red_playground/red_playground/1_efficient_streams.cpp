//
//  main.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 2/27/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int main1(int argc, const char * argv[]) {
    ofstream out("text.txt");
    
    for (int i = 0; i < 25; i++) {
        //endl resets buffer of a stream
        //not good for performance
        out << "hello world " << i << endl;
    }
    
    return 0;
}
