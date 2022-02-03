//
// Created by arkady on 02.02.2022.
//

#ifndef BASEBUSES_ITEMPATH_H
#define BASEBUSES_ITEMPATH_H

enum EdgeType {
    WAIT = 0,
    BUS
};

struct ItemPath {
    EdgeType type;
    std::string name{};
    size_t span_count{};
    double time{};
};

#endif //BASEBUSES_ITEMPATH_H
