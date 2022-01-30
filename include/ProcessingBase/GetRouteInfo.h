//
// Created by arkady on 30.01.2022.
//

#ifndef BASEBUSES_GETROUTEINFO_H
#define BASEBUSES_GETROUTEINFO_H

#include "StateListen.h"


class GetRouteInfo : public StateListen {
public:
    void Listen(BaseBuses &buses, const std::map<std::string, Json::Node> &map, std::ostream &ostream) override;
};


#endif //BASEBUSES_GETROUTEINFO_H
