#pragma once

#include "BaseBuses.h"
#include "nlohmann/json.hpp"

class StateListen {
public:
    virtual nlohmann::json Listen(BaseBuses&, const nlohmann::json&, std::ostream&) = 0;
};
