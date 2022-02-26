#include <iostream>
#include <ranges>
#include <vector>
#include <cmath>
#include <limits>
#include <map>

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

    auto requests = Load(cin).GetRoot().AsMap();
    BaseBuses baseBuses = BaseBusesBuilder()
            .BuildBase(requests);

    cout << BaseBusesProcess(baseBuses, requests["stat_requests"]) << endl;
}