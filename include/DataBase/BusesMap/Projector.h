#pragma once
//
// Created by arkady on 26.02.2022.
//

#ifndef BASEBUSES_PROJECTOR_H
#define BASEBUSES_PROJECTOR_H

#include <algorithm>

#include "svg.h"
#include "cmath"

bool IsZero(double x);

class Projector {
public:
    template <typename PointInputIt>
    Projector(PointInputIt points_begin, PointInputIt points_end,
              double max_width, double max_height, double padding);

    Svg::Point operator()(Svg::Point point) const;

private:
    double min_lon_ = 0;
    double max_lat_ = 0;
    const double padding_;
    double zoom_coef_ = 0;
};

template <typename PointInputIt>
Projector::Projector(PointInputIt points_begin, PointInputIt points_end,
                     double max_width, double max_height, double padding)
        : padding_(padding)
{
    if (points_begin == points_end) {
        return;
    }

    const auto [left_it, right_it] =
    std::minmax_element(points_begin, points_end,
                        [](Svg::Point lhs, Svg::Point rhs) {
                            return lhs.y < rhs.y;
                        });
    min_lon_ = left_it->y;
    const double max_lon = right_it->y;

    const auto [bottom_it, top_it] =
    std::minmax_element(points_begin, points_end,
                        [](Svg::Point lhs, Svg::Point rhs) {
                            return lhs.x < rhs.x;
                        });
    const double min_lat = bottom_it->x;
    max_lat_ = top_it->x;

    std::optional<double> width_zoom_coef;
    if (!IsZero(max_lon - min_lon_)) {
        width_zoom_coef = (max_width - 2 * padding) / (max_lon - min_lon_);
    }

    std::optional<double> height_zoom_coef;
    if (!IsZero(max_lat_ - min_lat)) {
        height_zoom_coef = (max_height - 2 * padding) / (max_lat_ - min_lat);
    }

    if (width_zoom_coef && height_zoom_coef) {
        zoom_coef_ = std::min(*width_zoom_coef, *height_zoom_coef);
    } else if (width_zoom_coef) {
        zoom_coef_ = *width_zoom_coef;
    } else if (height_zoom_coef) {
        zoom_coef_ = *height_zoom_coef;
    }
}

#endif //BASEBUSES_PROJECTOR_H
