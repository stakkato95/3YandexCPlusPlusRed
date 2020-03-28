//
//  test.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/16/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <unistd.h>

#include <iostream>
#include <string>

#define GetCurrentDir getcwd

using namespace std;

int maint() {
    char buff[100];
    GetCurrentDir( buff, FILENAME_MAX );
    string current_working_dir(buff);
    
    cout << current_working_dir << endl;
    
    return 0;
}
