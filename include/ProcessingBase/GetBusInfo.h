#pragma once

#include "StateListen.h"
#include "json.h"

namespace Requests {

    class GetBusInfo : public StateListen {
    public:
        Json::Node Listen(BaseBuses&, const std::map<std::string, Json::Node>&) override;
    };

}