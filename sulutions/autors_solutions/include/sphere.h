//
// Created by arkady on 03.02.2022.
//

#ifndef BASEBUSES2_SPHERE_H
#define BASEBUSES2_SPHERE_H


#pragma once

#include <cmath>

namespace Sphere {
    double ConvertDegreesToRadians(double degrees);

    struct Point {
        double latitude;
        double longitude;

        static Point FromDegrees(double latitude, double longitude);
    };

    double Distance(Point lhs, Point rhs);
}

#endif //BASEBUSES2_SPHERE_H
