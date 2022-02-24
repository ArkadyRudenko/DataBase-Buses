#pragma once
//
// Created by arkady on 16.02.2022.
//

#ifndef BASEBUSES_ROUTERMAP_H
#define BASEBUSES_ROUTERMAP_H

#include <vector>
#include <unordered_map>

#include "RenderSettings.h"
#include "json.h"
#include "Stop.h"
#include "BusInfo.h"

using StopsDict = std::unordered_map<std::string, Stop>;
using BusesDict = std::unordered_map<std::string, BusInfo>;

class RouterMap {
public:
    RouterMap(const StopsDict&, const BusesDict&, const Json::Dict&);
    std::string_view GetSvgDoc();
private:
    void BuildMap(const StopsDict&, const BusesDict&);
private:
    RenderSettings settings;
    std::string result_svg;


};

std::vector<std::string> MakeLayers(const Json::Node &node);
Svg::Point MakePoint(const Json::Node &);
Svg::Color MakeColor(const Json::Node &);
Svg::Color MakeRgbColor(const std::vector<Json::Node> &);
std::vector<Svg::Color> MakePaletteColor(const Json::Node &);

#endif //BASEBUSES_ROUTERMAP_H
