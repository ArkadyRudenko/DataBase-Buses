#pragma once
#include <map>

#include "BaseBuses.h"
#include "json.h"

namespace Requests {

    class StateListen {
    public:
        virtual Json::Node Listen(BaseBuses &, const std::map<std::string, Json::Node> &) = 0;
        virtual ~StateListen() = default;
    };
}