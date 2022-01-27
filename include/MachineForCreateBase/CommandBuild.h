#pragma once

#include <iostream>
#include <map>

#include "BaseBuses.h"
#include "json.h"

class CommandBuild {
public:
    virtual void Execute(BaseBuses&, const std::map<std::string, Json::Node>&) = 0;
};