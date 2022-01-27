#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>

#include "BaseBuses.h"
#include "CommandBuild.h"
#include "json.h"

class BaseBusesBuilder {
public:
    BaseBuses BuildBase(const Json::Node& base_requests);
private:
    std::unordered_map<std::string, std::shared_ptr<CommandBuild>> commands;

    void CreateCommands();
};

std::vector<std::shared_ptr<Json::Node>> GetSortedRequests(const Json::Node&);