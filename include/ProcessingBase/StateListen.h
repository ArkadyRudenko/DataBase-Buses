#pragma once
#include <map>

#include "BaseBuses.h"
#include "json.h"

class StateListen {
public:
    virtual void Listen(BaseBuses&, const std::map<std::string, Json::Node>&, std::ostream&) = 0;
};
