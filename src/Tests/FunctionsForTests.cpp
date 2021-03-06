#include "FunctionsForTests.h"
#include "BaseBuses.h"
#include "BaseBusesBuilder.h"
#include "BaseBusesProcess.h"
#include "json.h"

using namespace std;
using namespace Json;

string RemoveSpaces(stringstream& ss) {
    string res;
    char ch;
    while (ss >> ch) {
        if(ch != ' ' and ch != '\n') {
            res.push_back(ch);
        }
    }
    return res;
}

string GoBaseBuses(stringstream& input) {
    auto requests = Load(input).GetRoot().AsMap();
    BaseBuses baseBuses = BaseBusesBuilder()
            .BuildBase(
                    requests["base_requests"].AsArray(),
                    requests["routing_settings"].AsMap()
            );
    stringstream output;
    BaseBusesProcess(baseBuses, requests["stat_requests"], output);
    return RemoveSpaces(output);
}