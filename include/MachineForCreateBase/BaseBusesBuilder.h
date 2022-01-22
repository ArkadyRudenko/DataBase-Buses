#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>

#include "BaseBuses.h"
#include "CommandBuild.h"
#include "nlohmann/json.hpp"

class BaseBusesBuilder {
public:
    BaseBuses BuildBase(const nlohmann::json& base_requests);
private:
    std::unordered_map<std::string, std::shared_ptr<CommandBuild>> commands;

    void CreateCommands();
};

std::vector<std::shared_ptr<nlohmann::json>> GetSortedRequests(const nlohmann::json&);