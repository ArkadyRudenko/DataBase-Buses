//
// Created by arkady on 26.02.2022.
//

#include "Projector.h"

Svg::Point Projector::operator()(Svg::Point point) const {
    return {
            (point.y - min_lon_) * zoom_coef_ + padding_,
            (max_lat_ - point.x) * zoom_coef_ + padding_,
    };
}

bool IsZero(double x) {
    return std::abs(x) < 1e-6;
}