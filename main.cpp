#include <iostream>
#include <ranges>
#include <vector>
#include <map>

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

    auto requests = Load(cin).GetRoot().AsMap();
    BaseBuses baseBuses = BaseBusesBuilder()
            .BuildBase(
                    requests["base_requests"].AsArray(),
                    requests["routing_settings"].AsMap(),
                    requests["render_settings"].AsMap()
                    );

    cout << BaseBusesProcess(baseBuses, requests["stat_requests"]) << endl;

    return 0;
}