//
// Created by arkady on 16.02.2022.
//

#include <vector>

#include "RouterMap.h"

using namespace std;

RouterMap::RouterMap(const Json::Dict &settings_) {
    settings.width = settings_.at("width").AsDouble();
    settings.height = settings_.at("height").AsDouble();
    settings.padding = settings_.at("padding").AsDouble();
    settings.stop_radius = settings_.at("stop_radius").AsDouble();
    settings.line_width = settings_.at("line_width").AsDouble();
    settings.stop_label_font_size = settings_.at("stop_label_font_size").AsInt();
    settings.stop_label_offset = MakePoint(settings_.at("stop_label_offset").AsArray());
    settings.underlayer_color = MakeColor(settings_.at("underlayer_color").AsArray());
    settings.underlayer_width = settings_.at("underlayer_width").AsDouble();
    settings.color_palette = MakePaletteColor(settings_.at("color_palette").AsArray());
}

Svg::Point MakePoint(const vector<Json::Node> &point) {
    return {point.front().AsDouble(), point[1].AsDouble()};
}

Svg::Color MakeColor(const vector<Json::Node> &color) {
    if (color.size() == 3) {
        return Svg::Rgb{
                static_cast<uint8_t>(color[0].AsInt()),
                static_cast<uint8_t>(color[1].AsInt()),
                static_cast<uint8_t>(color[2].AsInt())
        };
    } else {
        return Svg::Rgba{
                static_cast<uint8_t>(color[0].AsInt()),
                static_cast<uint8_t>(color[1].AsInt()),
                static_cast<uint8_t>(color[2].AsInt()),
                color[3].AsDouble()
        };
    }
}

Svg::Color MakeColor(const string &color) {
    return color;
}


std::vector<Svg::Color> MakePaletteColor(const vector<Json::Node> &palette) {
    vector<Svg::Color> result;
    for (const auto &color: palette) {
        if(color.HasType<string>()) {
            result.emplace_back(color.AsString());
        } else {
            result.push_back(MakeColor(color.AsArray()));
        }
    }
    return result;
}

