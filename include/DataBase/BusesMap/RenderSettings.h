#pragma once
//
// Created by arkady on 16.02.2022.
//

#ifndef BASEBUSES_RENDERSETTINGS_H
#define BASEBUSES_RENDERSETTINGS_H

#include <vector>

#include "svg.h"

struct RenderSettings {
    double width;
    double height;
    double padding;
    double stop_radius;
    double line_width;
    int stop_label_font_size = 1;
    Svg::Point stop_label_offset;
    Svg::Color underlayer_color;
    double underlayer_width;
    std::vector<Svg::Color> palette;
    int bus_label_font_size;
    Svg::Point bus_label_offset;
    std::vector<std::string> layers;
};


#endif //BASEBUSES_RENDERSETTINGS_H
