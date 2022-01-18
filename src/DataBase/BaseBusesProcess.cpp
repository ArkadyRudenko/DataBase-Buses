#include "BaseBusesProcess.h"
#include "StateListen.h"
#include "GetBusInfo.h"

using namespace std;
using MapStates = unordered_map<string, shared_ptr<StateListen>>;

void BaseBusesProcess(BaseBuses &baseBuses, istream &is, ostream& os) {
    int count_command;
    is >> count_command;
    MapStates mapStates = CreateMapStates();
    for (int i = 0; i < count_command; ++i) {
        string command;
        is >> command;
        mapStates.at(command)->Listen(baseBuses, os, is);
    }
}

using namespace StateListening;

MapStates CreateMapStates() {
    MapStates mapStates;
    mapStates.insert({"Bus", make_shared<GetBusInfo>()});
    return mapStates;
}
