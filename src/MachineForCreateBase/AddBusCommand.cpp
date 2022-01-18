#include "AddBusCommand.h"
#include "PasreRequests.h"

using namespace std;

void AddBusCommand::Execute(BaseBuses& baseBuses, std::istream &is) {
    int id_bus;
    is >> id_bus;
    if (is.peek() != ':') {
        string wrong_line;
        getline(is, wrong_line);
        throw logic_error("Expected \':\', but was: " + to_string((wrong_line[0])));
    }
    is.ignore(1);
    baseBuses.AddBus(id_bus, ReadStop(is));
#ifdef TEST
    cout << "Bus ID = "<< id_bus << "<>\n";
#endif
}
