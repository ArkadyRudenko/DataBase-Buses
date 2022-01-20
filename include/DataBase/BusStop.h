#pragma once

#include <string>
#include <unordered_map>

class BusStop {
public:
    BusStop(std::string, double latitude, double longitude);
    std::string name;
    double latitude;
    double longitude;

    void SetCoordinates(double latitude, double longitude);

    void setLengths(std::unordered_map<std::string, int> lengths);

    const std::unordered_map<std::string, int> &getLengths() const;

    void AddLength(const std::pair<std::string, int>&);

    int GetLengthByStop(const std::string& stop_name);

    void SplitTwoMaps(const std::unordered_map<std::string, int>& new_map);

private:
    std::unordered_map<std::string, int> lengths_;
};
