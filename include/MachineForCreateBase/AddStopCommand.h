#pragma once
#include <unordered_map>

#include "CommandBuild.h"
#include "json.h"

class AddStopCommand : public CommandBuild {
public:
    void Execute(BaseBuses&, const std::map<std::string, Json::Node>&) override;
};

std::unordered_map<std::string, int> CreateMapStops(
            const std::map<std::string, Json::Node>&);