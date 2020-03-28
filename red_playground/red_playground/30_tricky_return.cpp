//
//  30_tricky_return.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <string>

using namespace std;

pair<ifstream, ofstream> getStreams(const string& name) {
    ifstream is(name + ".in");
    ofstream os(name + ".out");
//    return { is, os }; //compiler wants to copy is & os, BUT streams can't be copied, since copy ctor is deleated
    
    return { move(is), move(os) }; //optimised version
}

pair<ifstream, ofstream> getStreamsOptimized(const string& name) {
    //move is performed automatically
    //most optimised and beautiful version
    return { ifstream(name + ".in"), ofstream(name + ".out") };
}

ifstream makeInputStream() {
    pair<ifstream, ofstream> streams = getStreams("name");
    //we want to return ifstream, BUT ifstream isn't a temporary object
    //it's a PART of a temporary object
    return move(streams.first);
}

ifstream makeInputStreamOptimized() {
    //works fine
    return getStreams("name").first;
}

int main30() {
    
    return 0;
}
