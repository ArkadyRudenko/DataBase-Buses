#pragma once
//
// Created by arkady on 16.02.2022.
//

#ifndef BASEBUSES_ROUTERMAP_H
#define BASEBUSES_ROUTERMAP_H

#include <vector>

#include "RenderSettings.h"
#include "json.h"

class RouterMap {
public:
    RouterMap(const Json::Dict&);
private:
    RenderSettings settings;
};

Svg::Point MakePoint(const std::vector<Json::Node> &);
Svg::Color MakeColor(const std::vector<Json::Node> &);
std::vector<Svg::Color> MakePaletteColor(const std::vector<Json::Node> &);


#endif //BASEBUSES_ROUTERMAP_H
