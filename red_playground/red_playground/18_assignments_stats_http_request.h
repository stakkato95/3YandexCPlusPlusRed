//
//  18_assignments_stats_http_request.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/20/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//
#pragma once

#include <string_view>

using namespace std;

struct HttpRequest {
    string_view method, uri, protocol;
};

