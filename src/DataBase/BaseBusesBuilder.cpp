#include "BaseBusesBuilder.h"
#include "AddBusCommand.h"
#include "AddStop.h"

using namespace std;

BaseBuses BaseBusesBuilder::BuildBase(std::istream &is) {
    BaseBuses baseBuses;
    CreateCommands();
    int count_command;
    is >> count_command;
    for (int i = 0; i < count_command; ++i) {
        string command;
        is >> command;
        try {
            commands.at(command)->Execute(baseBuses, is);
        } catch (logic_error error) {
            cerr << error.what() << endl;
        }
    }
    return baseBuses;
}

void BaseBusesBuilder::CreateCommands() {
    commands.insert({"Stop", make_shared<AddStop>()});
    commands.insert({"Bus", make_shared<AddBusCommand>()});
}
