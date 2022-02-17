//
// Created by arkady on 30.01.2022.
//

#ifndef BASEBUSES_GETROUTEINFO_H
#define BASEBUSES_GETROUTEINFO_H

#include "StateListen.h"

namespace Requests {
    class GetRouteInfo : public StateListen {
    public:
        Json::Node Listen(BaseBuses &buses, const std::map<std::string, Json::Node> &map) override;
    };
}

#endif //BASEBUSES_GETROUTEINFO_H
