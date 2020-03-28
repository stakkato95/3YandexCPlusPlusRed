//
//  18_assignments_stats_stats.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/20/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//
#pragma once

#include "18_assignments_stats_http_request.h"

#include <string_view>
#include <map>
using namespace std;

class Stats {
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;
    
private:
    using StatsMap = map<string_view, int>;
    StatsMap methods;
    StatsMap uris;
};

HttpRequest ParseRequest(string_view line);
