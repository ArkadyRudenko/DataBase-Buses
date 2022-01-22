#pragma once

#include "CommandBuild.h"
#include "BusInfo.h"
#include "nlohmann/json.hpp"

class AddBusCommand : public CommandBuild {
public:
    void Execute(BaseBuses&, nlohmann::json&) override;
};

std::vector<std::string> CreateVectorStops(const nlohmann::json&);

Route GetRoute(const nlohmann::json&);
