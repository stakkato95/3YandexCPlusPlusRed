//
//  18_assignments_stats_server_stats.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/20/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <array>
#include <string>
#include <string_view>

using namespace std;

class RequestParams {
public:
    RequestParams() : size { 0 } { }
    
    void pushBack(const string_view& view) {
        http[size++] = view;
    }
    
    string_view getMethod() const { return http[0]; }
    
    string_view getPath() const { return http[1]; }
    
    string_view getVersion() const { return http[2]; }
private:
    array<string_view, 3> http;
    size_t size;
};

RequestParams getRequestParameters(string_view view) {
    RequestParams params;
    
    while (true) {
        size_t space = view.find(' ');
        params.pushBack(view.substr(0, space));
        view.remove_prefix(space + 1);
        
        if (space == view.npos) {
            break;
        }
    }
    
    return params;
}

int main18() {
    string httpRequestString = "GET /products HTTP/1.1";
    RequestParams params = getRequestParameters(httpRequestString);
    cout << params.getMethod() << "-->" << params.getPath() << "-->" << params.getVersion() << endl;
    
    return 0;
}
