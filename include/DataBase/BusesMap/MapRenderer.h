#pragma once
//
// Created by arkady on 16.02.2022.
//

#ifndef BASEBUSES_MAPRENDERER_H
#define BASEBUSES_MAPRENDERER_H

#include <vector>
#include <unordered_map>

#include "RenderSettings.h"
#include "json.h"
#include "Stop.h"
#include "BusInfo.h"

using StopsDict = std::unordered_map<std::string, Stop>;
using BusesDict = std::unordered_map<std::string, BusInfo>;

class MapRenderer {
public:
    MapRenderer(const StopsDict&, const BusesDict&, const Json::Node&);
    Svg::Document Render() const;
private:
    RenderSettings settings_;
    const BusesDict& buses_dict_;
    std::map<std::string, Svg::Point> stops_coords_;
    std::map<std::string, Svg::Color> buses_colors_;

    void RenderBusLines(Svg::Document& svg) const;
    void RenderBusLabels(Svg::Document& svg) const;
    void RenderStopPoints(Svg::Document& svg) const;
    void RenderStopLabels(Svg::Document& svg) const;

    static const std::unordered_map<std::string, void (MapRenderer::*)(Svg::Document&) const> LAYER_ACTIONS;
};

std::map<std::string, Svg::Point> MakeCoordinates(const StopsDict& stops_dict,
                                                  const RenderSettings& render_Settings);
static std::map<std::string, Svg::Color> ChooseBusColors(const BusesDict& buses_dict,
                                                           const RenderSettings& render_Settings);

std::vector<std::string> ParseLayers(const Json::Node &node);
static Svg::Point ParsePoint(const Json::Node &);
Svg::Color MakeColor(const Json::Node &);
Svg::Color MakeRgbColor(const Json::Node &);
std::vector<Svg::Color> ParsePaletteColor(const Json::Node &);
RenderSettings ParseRenderSettings(const Json::Node &json);

#endif //BASEBUSES_MAPRENDERER_H