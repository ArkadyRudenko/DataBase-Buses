//
// Created by arkady on 30.01.2022.
//

#include <string>

#include "GetRouteInfo.h"
#include "ItemPath.h"
#include "json.h"



namespace Requests {
    using namespace Json;
    using namespace std;
    Node GetRouteInfo::Listen(BaseBuses &baseBuses,
                                    const std::map<std::string, Node> &route_settings) {
        Dict dict;
        dict["request_id"] = route_settings.at("id").AsInt();
        if (auto items = baseBuses.GetInfoRoute(route_settings.at("from").AsString(),
                                                route_settings.at("to").AsString())) {
            vector<Node> items_of_path;
            dict["total_time"] = items->total_time;
            for (const auto &item: items->items) {
                Dict dict_item;
                if (holds_alternative<RouteInfo::WaitItem>(item)) {
                    const auto &wait_edge_info = get<RouteInfo::WaitItem>(item);
                    dict_item = {
                            {"type",      "Wait"},
                            {"stop_name", wait_edge_info.stop_name},
                            {"time",      wait_edge_info.time}
                    };
                    items_of_path.push_back(Node(dict_item));
                } else {
                    const auto &bus_edge_info = get<RouteInfo::BusItem>(item);
                    dict_item = {
                            {"type",       "Bus"},
                            {"bus",        bus_edge_info.bus_name},
                            {"time",       bus_edge_info.time},
                            {"span_count", static_cast<int>(bus_edge_info.span_count)}
                    };
                    items_of_path.push_back(Node(dict_item));
                }
            }
            dict["items"] = items_of_path;
        } else {
            dict["error_message"] = "not found";
        }

        return Node(dict);
    }
}

