#include <ranges>
#include <algorithm>
#include <sstream>

#include "BaseBusesBuilder.h"
#include "AddBusCommand.h"
#include "AddStop.h"

using namespace std;
//namespace rng = std::ranges;

BaseBuses BaseBusesBuilder::BuildBase(std::istream &is) {
    BaseBuses baseBuses;
    CreateCommands();

    int count_command;
    is >> count_command;
    vector<string> all_commands;
    for (int i = 0; i < count_command + 1; ++i) {
        string command;
        getline(is, command);
        all_commands.push_back(move(command));
    }

    vector<string_view> commands_for_sorting(all_commands.size());
    for (int i = 0; i < all_commands.size(); i++) {
        commands_for_sorting[i] = all_commands[i];
    }
    // TODO rng
    partition(commands_for_sorting.begin(), commands_for_sorting.end(), [](const string_view str) {
        return str.substr(0, 4) == "Stop";
    });

    stringstream sorted_stream;
    CreateStream(sorted_stream, commands_for_sorting);

    for (int i = 0; i < count_command; ++i) {
        string command;
        sorted_stream >> command;
        try {
            commands.at(command)->Execute(baseBuses, sorted_stream); // TODO
        } catch (logic_error& error) {
            cerr << error.what() << endl;
        }
    }
    return baseBuses;
}

void BaseBusesBuilder::CreateCommands() {
    commands.insert({"Stop", make_shared<AddStop>()});
    commands.insert({"Bus", make_shared<AddBusCommand>()});
}

void BaseBusesBuilder::CreateStream(stringstream& sorted_stream, vector<string_view>& commands_) {
    for(auto str : commands_) {
        sorted_stream << str << "\n";
    }
}
