#include <iostream>
#include <ranges>
#include <algorithm>

#include "BaseBusesBuilder.h"
#include "BaseBusesProcess.h"
#include "Tests.h"
#include "json.h"


using namespace std;
using namespace Json;

int main() {
    TestAll();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

//    auto requests = Load(cin).GetRoot().AsMap();
//    BaseBuses baseBuses = BaseBusesBuilder()
//            .BuildBase(
//                    requests["base_requests"]
//                    );
//
//    BaseBusesProcess(baseBuses, requests["stat_requests"]);

    return 0;
}