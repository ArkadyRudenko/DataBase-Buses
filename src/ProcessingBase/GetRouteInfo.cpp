//
// Created by arkady on 30.01.2022.
//

#include <string>

#include "GetRouteInfo.h"
#include "json.h"

using namespace Json;
using namespace std;

void GetRouteInfo::Listen(BaseBuses &buses,
                          const std::map<std::string, Json::Node> &route_settings,
                          std::ostream &os) {
    Node res;
    res.push_back("request_id"s, route_settings.at("id").AsInt());
//    res.push_back("total_time"s, /* get_from_data_base double */);
    Node items;
//    for(;;) {
//        items;
//    }
    res.push_back("items"s, items);
    os << res;
}
