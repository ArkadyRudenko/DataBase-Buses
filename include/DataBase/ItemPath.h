//
// Created by arkady on 02.02.2022.
//

#ifndef BASEBUSES_ITEMPATH_H
#define BASEBUSES_ITEMPATH_H

#include <variant>

struct RouteInfo {
    double total_time;

    struct BusItem {
        std::string bus_name;
        double time;
        size_t span_count;
    };
    struct WaitItem {
        std::string stop_name;
        double time;
    };

    using Item = std::variant<BusItem, WaitItem>;
    std::vector<Item> items;
};

#endif //BASEBUSES_ITEMPATH_H
