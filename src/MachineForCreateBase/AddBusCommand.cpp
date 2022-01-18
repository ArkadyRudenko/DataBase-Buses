#include <sstream>

#include "AddBusCommand.h"
#include "PasreRequests.h"

using namespace std;

void AddBusCommand::Execute(BaseBuses& baseBuses, std::istream &is) {
    string id_bus;
    getline(is, id_bus, ':');
    is.ignore(1);
    baseBuses.AddBus(RemoveSpaces(id_bus), ReadStop(is));
}
