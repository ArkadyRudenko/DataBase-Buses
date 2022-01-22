#include <iostream>
#include <ranges>
#include <algorithm>

#include "BaseBusesBuilder.h"
#include "BaseBusesProcess.h"
#include "Tests.h"
#include "nlohmann/json.hpp"


using namespace std;
using namespace nlohmann;

int main() {
//    TestAll();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    stringstream ss = GetStream();

    json requests = json::parse(GetStream());

    BaseBuses baseBuses = BaseBusesBuilder().BuildBase(requests["base_requests"]);

    BaseBusesProcess(baseBuses, requests["stat_requests"]);

    return 0;
}