//
// Created by arkady on 16.02.2022.
//

#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <set>

#include "MapRenderer.h"
#include "Projector.h"
#include "svg.h"

using namespace std;

MapRenderer::MapRenderer(const StopsDict &stops_dict,
                     const BusesDict &buses_dict,
                     const Json::Node &settings)
                     :
        settings_(ParseRenderSettings(settings)),
        buses_dict_(buses_dict),
        stops_coords_(MakeCoordinates(stops_dict, settings_)),
        buses_colors_(ChooseBusColors(buses_dict, settings_))
                     {
                     }


const unordered_map<string, void (MapRenderer::*)(Svg::Document&) const> MapRenderer::LAYER_ACTIONS = {
        {"bus_lines",   &MapRenderer::RenderBusLines},
        {"bus_labels",  &MapRenderer::RenderBusLabels},
        {"stop_points", &MapRenderer::RenderStopPoints},
        {"stop_labels", &MapRenderer::RenderStopLabels},
};

Svg::Document MapRenderer::Render() const {
    Svg::Document svg;

    for (const auto& layer : settings_.layers) {
        (this->*LAYER_ACTIONS.at(layer))(svg);
    }

    return svg;
}

std::map<std::string, Svg::Point> MakeCoordinates(const StopsDict& stops_dict,
                                                  const RenderSettings& settings_) {
    vector<Svg::Point> points;
    points.reserve(stops_dict.size());
    for (const auto& [_, stop_ptr] : stops_dict) {
        points.push_back({stop_ptr.latitude, stop_ptr.longitude});
    }

    const double max_width = settings_.width;
    const double max_height = settings_.height;
    const double padding = settings_.padding;

    const Projector projector(
            begin(points), end(points),
            max_width, max_height, padding
    );

    map<string, Svg::Point> stops_coords;
    for (const auto& [stop_name, stop_ptr] : stops_dict) {
        stops_coords[stop_name] = projector({stop_ptr.latitude, stop_ptr.longitude});
    }

    return stops_coords;

}

static std::map<std::string, Svg::Color> ChooseBusColors(const BusesDict& buses_dict,
                                                                  const RenderSettings& render_settings) {
    const auto& palette = render_settings.palette;
    map<string, Svg::Color> bus_colors;

    set<string> sorted_buses;
    for(const auto& [bus_name, _] : buses_dict) {
        sorted_buses.insert(bus_name);
    }

    int idx = 0;
    for (const auto& bus_name : sorted_buses) {
        bus_colors[bus_name] = palette[idx++ % palette.size()];
    }
    return bus_colors;
}

std::vector<std::string> ParseLayers(const Json::Node &layers) {
    vector<string> result;
    for (const auto &node: layers.AsArray()) {
        result.push_back(node.AsString());
    }
    return result;
}

static Svg::Point ParsePoint(const Json::Node& json) {
    const auto& array = json.AsArray();
    return {
            array[0].AsDouble(),
            array[1].AsDouble()
    };
}

Svg::Color MakeColor(const Json::Node &color) {
    if (color.HasType<string>()) {
        return Svg::Color(color.AsString());
    } else {
        return MakeRgbColor(color);
    }
}

Svg::Color MakeRgbColor(const Json::Node &json) {
    const auto& array = json.AsArray();
    assert(array.size() == 3 || array.size() == 4);
    if (array.size() == 3) {
        return Svg::Rgb{
                static_cast<uint8_t>(array[0].AsInt()),
                static_cast<uint8_t>(array[1].AsInt()),
                static_cast<uint8_t>(array[2].AsInt())
        };
    } else if (array.size() == 4) {
        return Svg::Rgba{
                static_cast<uint8_t>(array[0].AsInt()),
                static_cast<uint8_t>(array[1].AsInt()),
                static_cast<uint8_t>(array[2].AsInt()),
                array[3].AsDouble()
        };
    }
}

std::vector<Svg::Color> ParsePaletteColor(const Json::Node &palette) {
    vector<Svg::Color> result;
    result.reserve(palette.AsArray().size());
    for (const auto &color: palette.AsArray()) {
        result.push_back(MakeColor(color));
    }
    return result;
}

RenderSettings ParseRenderSettings(const Json::Node &json) {
    const Json::Dict& render_settings = json.AsMap();
    return {
            .width = render_settings.at("width").AsDouble(),
            .height = render_settings.at("height").AsDouble(),
            .padding = render_settings.at("padding").AsDouble(),
            .stop_radius = render_settings.at("stop_radius").AsDouble(),
            .line_width = render_settings.at("line_width").AsDouble(),
            .stop_label_font_size = render_settings.at("stop_label_font_size").AsInt(),
            .stop_label_offset = ParsePoint(render_settings.at("stop_label_offset")),
            .underlayer_color = MakeColor(render_settings.at("underlayer_color")),
            .underlayer_width = render_settings.at("underlayer_width").AsDouble(),
            .palette = ParsePaletteColor(render_settings.at("color_palette")),
            .bus_label_font_size = render_settings.at("bus_label_font_size").AsInt(),
            .bus_label_offset = ParsePoint(render_settings.at("bus_label_offset")),
            .layers = ParseLayers(render_settings.at("layers")),
    };
}

void MapRenderer::RenderBusLines(Svg::Document &svg) const {
    set<string> sorted_buses;
    for(const auto& [bus_name, _] : buses_dict_) {
        sorted_buses.insert(bus_name);
    }

    for (const auto& bus_name : sorted_buses) {
        const auto& stops =  buses_dict_.find(bus_name)->second.getListStops();
        if (stops.empty()) {
            continue;
        }
        Svg::Polyline line;
        line.SetStrokeColor(buses_colors_.at(bus_name))
                .SetStrokeWidth(settings_.line_width)
                .SetStrokeLineCap("round").SetStrokeLineJoin("round");
        for (const auto& stop_name : stops) {
            line.AddPoint(stops_coords_.at(stop_name->name));
        }
        svg.Add(line);
    }
}

void MapRenderer::RenderBusLabels(Svg::Document &svg) const {
    for (const auto &bus: buses_colors_) {
        StopsList stopsList = buses_dict_.at(bus.first).getListStops();
        vector<Svg::Point> points;
        if (Route::ANNULAR == buses_dict_.at(bus.first).getRoute()) {
            points.push_back(stops_coords_.find(stopsList[0]->name)->second);
        } else {
            points.push_back(stops_coords_.find(stopsList[0]->name)->second);
            if (stopsList[stopsList.size() / 2]->name != stopsList[0]->name) {
                points.push_back(stops_coords_.find(stopsList[stopsList.size() / 2]->name)->second);
            }
        }

        for (const auto &point: points) {

            const auto base_text =
                    Svg::Text{}
                            .SetPoint(point)
                            .SetOffset(settings_.bus_label_offset)
                            .SetFontSize(settings_.bus_label_font_size)
                            .SetFontFamily("Verdana")
                            .SetFontWeight("bold")
                            .SetData(bus.first);
            svg.Add(
                    Svg::Text(base_text)
                            .SetFillColor(settings_.underlayer_color)
                            .SetStrokeColor(settings_.underlayer_color)
                            .SetStrokeWidth(settings_.underlayer_width)
                            .SetStrokeLineCap("round").SetStrokeLineJoin("round")
            );
            svg.Add(
                    Svg::Text(base_text)
                            .SetFillColor(bus.second)
            );
        }
    }
}

void MapRenderer::RenderStopPoints(Svg::Document &svg) const {
    for (const auto& [stop_name, stop_point] : stops_coords_) {
        svg.Add(Svg::Circle{}
                        .SetCenter(stop_point)
                        .SetRadius(settings_.stop_radius)
                        .SetFillColor("white"));
    }
}

void MapRenderer::RenderStopLabels(Svg::Document &svg) const {
    for (const auto& [stop_name, stop_point] : stops_coords_) {
        const auto base_text =
                Svg::Text{}
                        .SetPoint(stop_point)
                        .SetOffset(settings_.stop_label_offset)
                        .SetFontSize(settings_.stop_label_font_size)
                        .SetFontFamily("Verdana")
                        .SetData(stop_name);
        svg.Add(
                Svg::Text(base_text)
                        .SetFillColor(settings_.underlayer_color)
                        .SetStrokeColor(settings_.underlayer_color)
                        .SetStrokeWidth(settings_.underlayer_width)
                        .SetStrokeLineCap("round").SetStrokeLineJoin("round")
        );
        svg.Add(
                Svg::Text(base_text)
                        .SetFillColor("black")
        );
    }
}
