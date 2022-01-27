#pragma once

#include "CommandBuild.h"
#include "BusInfo.h"
#include "json.h"

class AddBusCommand : public CommandBuild {
public:
    void Execute(BaseBuses&, const std::map<std::string, Json::Node>&) override;
};

std::vector<std::string> CreateVectorStops(const Json::Node&);

Route GetRoute(const Json::Node&);
