#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <map>

#include "BaseBuses.h"
#include "CommandBuild.h"
#include "json.h"

class BaseBusesBuilder {
public:
    BaseBuses BuildBase(const std::vector<Json::Node>&, const std::map<std::string, Json::Node>&);
private:
    std::unordered_map<std::string, std::shared_ptr<CommandBuild>> commands;

    void CreateCommands();
};

std::vector<std::shared_ptr<Json::Node>> GetSortedRequests(const std::vector<Json::Node> &requests);