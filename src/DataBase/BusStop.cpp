#include <iostream>
#include "BusStop.h"

BusStop::BusStop(std::string name, double latitude, double longitude)
        : name(move(name)), latitude(latitude), longitude(longitude) {
}

void BusStop::setLengths(std::unordered_map<std::string, int> lengths) {
    lengths_ = move(lengths);
}

const std::unordered_map<std::string, int> &BusStop::getLengths() const {
    return lengths_;
}

void BusStop::AddLength(const std::pair<std::string, int> &length_item) {
    auto it = lengths_.find(length_item.first);
    if (it == lengths_.end()) {
        lengths_.insert(length_item);
    }
}

int BusStop::GetLengthByStop(const std::string &stop_name) {
    return lengths_.find(stop_name)->second;
}

void BusStop::SplitTwoMaps(const std::unordered_map<std::string, int> &new_map) {
    for (const auto &item: new_map) {
        if (auto it = lengths_.find(item.first); it != lengths_.end()) {
            it->second = item.second;
        } else {
            lengths_.insert(item);
        }
    }
}

void BusStop::SetCoordinates(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

