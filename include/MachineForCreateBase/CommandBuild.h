#pragma once

#include <iostream>

#include "BaseBuses.h"
#include "nlohmann/json.hpp"

class CommandBuild {
public:
    virtual void Execute(BaseBuses&, nlohmann::json&) = 0;
};