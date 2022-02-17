//
// Created by arkady on 16.02.2022.
//

#include "GetMap.h"
#include "json.h"

namespace Requests {
    using namespace std;
    using namespace Json;

    Node GetMap::Listen(BaseBuses &baseBuses, const std::map<std::string, Json::Node> &id_map) {
        Dict dict;
//        res["id"] = id_map.at("id").AsInt();
        dict["map"] = baseBuses.GetInfoMap();
        return Node(dict);
    }

}