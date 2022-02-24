//
// Created by arkady on 16.02.2022.
//

#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <map>
#include <limits>
#include <memory>

#include "RouterMap.h"
#include "svg.h"

using namespace std;

RouterMap::RouterMap(const StopsDict &stops_dict,
                     const BusesDict &buses_dict,
                     const Json::Dict &settings_) {
    settings.width = settings_.at("width").AsDouble();
    settings.height = settings_.at("height").AsDouble();
    settings.padding = settings_.at("padding").AsDouble();
    settings.stop_radius = settings_.at("stop_radius").AsDouble();
    settings.line_width = settings_.at("line_width").AsDouble();
    settings.stop_label_font_size = settings_.at("stop_label_font_size").AsInt();
    settings.stop_label_offset = MakePoint(settings_.at("stop_label_offset"));
    settings.underlayer_color = MakeColor(settings_.at("underlayer_color"));
    settings.underlayer_width = settings_.at("underlayer_width").AsDouble();
    settings.color_palette = MakePaletteColor(settings_.at("color_palette"));
    settings.bus_label_font_size = settings_.at("bus_label_font_size").AsInt();
    settings.bus_label_offset = MakePoint(settings_.at("bus_label_offset").AsArray());
//    settings.layers = MakeLayers(settings_.at("layers"));

    BuildMap(stops_dict, buses_dict);
}

// TODO
void RouterMap::BuildMap(const StopsDict &stops_dict, const BusesDict &buses_dict) {
    double max_lon = -1., min_lon = 181.,
            max_lat = -1., min_lat = 181.;

    for (const auto &stop: stops_dict) {
        if (stop.second.longitude > max_lon) {
            max_lon = stop.second.longitude;
        }
        if (stop.second.latitude > max_lat) {
            max_lat = stop.second.latitude;
        }
        if (stop.second.longitude < min_lon) {
            min_lon = stop.second.longitude;
        }
        if (stop.second.latitude < min_lat) {
            min_lat = stop.second.latitude;
        }
    }

    double width_zoom_coef = (settings.width - 2 * settings.padding) / (max_lon - min_lon);
    double height_zoom_coef = (settings.height - 2 * settings.padding) / (max_lat - min_lat);
    double zoom_coef = min(width_zoom_coef, height_zoom_coef); // TODO Nun
    if ((max_lon - min_lon) == 0) {
        zoom_coef = height_zoom_coef;
    }
    if ((max_lat - min_lat) == 0) {
        zoom_coef = width_zoom_coef;
    } else if ((max_lon - min_lon) == 0 and (max_lat - min_lat) == 0) {
        zoom_coef = 0;
    }
    map<string, Svg::Point> stops_coordinates;

    for (const auto &stop: stops_dict) {
        if ((max_lon - min_lon) == 0 and (max_lat - min_lat) == 0) {
            stops_coordinates.insert({stop.second.name,
                                      {settings.padding,
                                       settings.padding}});
        } else {
            stops_coordinates.insert({stop.second.name,
                                      {(stop.second.longitude - min_lon) * zoom_coef + settings.padding,
                                       (max_lat - stop.second.latitude) * zoom_coef + settings.padding}});
        }
    }

    map<string, Svg::Color> buses_colors;
    for (const auto &bus: buses_dict) {
        buses_colors[bus.first];
    }
    int i = 0;
    for (auto &bus: buses_colors) {
        bus.second = settings.color_palette[i++];
        if (i == settings.color_palette.size()) {
            i = 0;
        }
    }
    // ------------ RENDER ------------- //
    Svg::Document map_document;

    for (const auto &bus: buses_colors) {
        StopsList stopsList = buses_dict.at(bus.first).getListStops();
        Svg::Polyline polyline;
        polyline.SetStrokeColor(buses_colors[bus.first])
                .SetStrokeWidth(settings.line_width)
                .SetStrokeLineCap("round")
                .SetStrokeLineJoin("round");
        for (const auto &stop: stopsList) {
            polyline.AddPoint(stops_coordinates.at(stop->name));
        }
        map_document.Add(move(polyline));
    }

    for (const auto &bus: buses_colors) {
        StopsList stopsList = buses_dict.at(bus.first).getListStops();
        vector<Svg::Point> points;
        if (Route::ANNULAR == buses_dict.at(bus.first).getRoute()) {
            points.push_back(stops_coordinates.find(stopsList[0]->name)->second);
        } else {
            points.push_back(stops_coordinates.find(stopsList[0]->name)->second);
            if(stopsList[stopsList.size() / 2]->name != stopsList[0]->name) {
                points.push_back(stops_coordinates.find(stopsList[stopsList.size() / 2]->name)->second);
            }
        }

        for(const auto& point : points) {

            map_document.
                    Add(Svg::Text{}
                                .SetPoint(point)
                                .SetOffset(settings.bus_label_offset)
                                .SetFontSize(settings.bus_label_font_size)
                                .SetFontFamily("Verdana")
                                .SetFontWeight("bold")
                                .SetData(bus.first)
                                        // additionally
                                .SetStrokeColor(settings.underlayer_color)
                                .SetFillColor(settings.underlayer_color)
                                .SetStrokeWidth(settings.underlayer_width)
                                .SetStrokeLineCap("round")
                                .SetStrokeLineJoin("round"));
            map_document.
                    Add(Svg::Text{}
                                .SetPoint(point)
                                .SetOffset(settings.bus_label_offset)
                                .SetFontSize(settings.bus_label_font_size)
                                .SetFontFamily("Verdana")
                                .SetFontWeight("bold")
                                .SetData(bus.first)
                                        // additionally
                                .SetFillColor(bus.second)
            );
        }
    }

    for (const auto &stop: stops_coordinates) {
        map_document.
                Add(Svg::Circle{}
                            .SetCenter(stop.second)
                            .SetRadius(settings.stop_radius)
                            .SetFillColor("white")
        );
    }

    for (const auto &stop: stops_coordinates) {
        map_document.
                Add(Svg::Text{}
                            .SetPoint(stop.second)
                            .SetOffset(settings.stop_label_offset)
                            .SetFontSize(settings.stop_label_font_size)
                            .SetFontFamily("Verdana")
                            .SetData(stop.first)
                            .SetStrokeColor(settings.underlayer_color)
                            .SetFillColor(settings.underlayer_color)
                            .SetStrokeWidth(settings.underlayer_width)
                            .SetStrokeLineCap("round")
                            .SetStrokeLineJoin("round")
        );
        map_document.
                Add(Svg::Text{}
                            .SetPoint(stop.second)
                            .SetOffset(settings.stop_label_offset)
                            .SetFontSize(settings.stop_label_font_size)
                            .SetFontFamily("Verdana")
                            .SetData(stop.first)
                            .SetFillColor("black"));

    }
    stringstream ss;
    map_document.Render(ss);
    for (const char ch: ss.str()) {
        if (ch == '\"' or ch == '\\') {
            result_svg.push_back('\\');
        }
        result_svg.push_back(ch);
    }
}

std::string_view RouterMap::GetSvgDoc() {
//    string res;
//    for(char ch : result_svg) {
//        if(ch != 92) {
//            res += ch;
//        }
//    }
//    cout << "\n WORKING VERSION=\n" << res << '\n';
    return result_svg;
}

std::vector<std::string> MakeLayers(const Json::Node &layers) {
    vector<string> result;
    for(const auto& node : layers.AsArray()) {
        result.push_back(node.AsString());
    }
    return result;
}

Svg::Point MakePoint(const Json::Node &point) {
    return {point.AsArray().front().AsDouble(), point.AsArray()[1].AsDouble()};
}

Svg::Color MakeColor(const Json::Node &color) {
    if (color.HasType<string>()) {
        return Svg::Color(color.AsString());
    } else {
        return MakeRgbColor(color.AsArray());
    }
}

Svg::Color MakeRgbColor(const vector<Json::Node> &color) {
    if (color.size() == 3) {
        return Svg::Rgb{
                static_cast<uint8_t>(color[0].AsInt()),
                static_cast<uint8_t>(color[1].AsInt()),
                static_cast<uint8_t>(color[2].AsInt())
        };
    } else if (color.size() == 4) {
        return Svg::Rgba{
                static_cast<uint8_t>(color[0].AsInt()),
                static_cast<uint8_t>(color[1].AsInt()),
                static_cast<uint8_t>(color[2].AsInt()),
                color[3].AsDouble()
        };
    }
}

std::vector<Svg::Color> MakePaletteColor(const Json::Node &palette) {
    vector<Svg::Color> result;
    result.reserve(palette.AsArray().size());
    for (const auto &color : palette.AsArray()) {
        result.push_back(MakeColor(color));
    }
    return result;
}