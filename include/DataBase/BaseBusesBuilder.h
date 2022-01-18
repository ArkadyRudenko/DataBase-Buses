#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>

#include "BaseBuses.h"
#include "CommandBuild.h"

class BaseBusesBuilder {
public:
    BaseBuses BuildBase(std::istream& is = std::cin);
private:
    std::unordered_map<std::string, std::shared_ptr<CommandBuild>> commands;

    void CreateCommands();
    void CreateStream(std::stringstream&, std::vector<std::string_view>&);
};