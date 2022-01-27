#include <iostream>
#include <ranges>
#include <algorithm>
#include <iomanip>

#include "BaseBusesBuilder.h"
#include "BaseBusesProcess.h"
#include "Tests.h"
#include "json.h"


using namespace std;
using namespace Json;

int main() {
//    TestAll();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    stringstream ss = GetStreamNew();

    auto requests = Load(cin).GetRoot().AsMap();
    BaseBuses baseBuses = BaseBusesBuilder()
            .BuildBase(
                    requests["base_requests"]
                    );

    BaseBusesProcess(baseBuses, requests["stat_requests"]);

    return 0;
}

/*
[
{ "curvature": 1.36124,
"request_id": 2080291871,
"route_length": 5950,
"stop_count": 6,
"unique_stop_count": 5
},
{ "curvature": 1.31808,
"request_id": 2002770042,
"route_length": 13800,
"stop_count": 5,
"unique_stop_count": 3
},
{ "error_message": "not found",
"request_id": 21967229
},
{ "error_message": "not found",
"request_id": 404935781
},
{ "buses": [
],
"request_id": 2138303887
},
{ "buses": [
"256",
"828"
],
"request_id": 618459820
},

]
 */