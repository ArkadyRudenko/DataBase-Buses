//
// Created by arkady on 24.02.2022.
//

#ifndef BASEBUSES_MAPBUILDER_H
#define BASEBUSES_MAPBUILDER_H

#include <memory>

#include "RouterMap.h"

using namespace std;

struct ParametersForWorker {
    const map<string, Svg::Color> &buses_colors;
    const BusesDict &buses_dict;
    const map<string, Svg::Point> &stops_coordinates;
    const RenderSettings &settings;
};

class Worker {
public:
    Worker(const ParametersForWorker param)
            :
            buses_colors(param.buses_colors),
            buses_dict(param.buses_dict),
            stops_coordinates(param.stops_coordinates),
            settings(param.settings) {}

    virtual void Process(unique_ptr<Svg::Document> document) = 0;

    virtual void Run(unique_ptr<Svg::Document> document) {
        // только первому worker-у в пайплайне нужно реализовать этот метод
        throw logic_error("Unimplemented");
    }

    void SetNext(unique_ptr<Worker> worker) {
        nextObject = move(worker);
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Svg::Document> document) const {
        if(nextObject) {
            nextObject->Process(move(document));
        }
    }

    const map <string, Svg::Color> &buses_colors;
    const BusesDict &buses_dict;
    const map <string, Svg::Point> &stops_coordinates;
    const RenderSettings &settings;
private:
    unique_ptr<Worker> nextObject;
};

class SetterBusLines : public Worker {
public:
    SetterBusLines(const ParametersForWorker& params) : Worker(params) {}
    void Process(unique_ptr<Svg::Document> document) override {
        for (const auto &bus: buses_colors) {
            StopsList stopsList = buses_dict.at(bus.first).getListStops();
            Svg::Polyline polyline;
            polyline.SetStrokeColor(buses_colors.at(bus.first))
                    .SetStrokeWidth(settings.line_width)
                    .SetStrokeLineCap("round")
                    .SetStrokeLineJoin("round");
            for (const auto &stop: stopsList) {
                polyline.AddPoint(stops_coordinates.at(stop->name));
            }
            document->Add(move(polyline));
        }

        PassOn(move(document));
    }
};

class SetterStopPoints : public Worker {
public:
    SetterStopPoints(const ParametersForWorker& params) : Worker(params) {}
    void Process(unique_ptr<Svg::Document> document) override {

        for (const auto &stop: stops_coordinates) {
            document->
                    Add(Svg::Circle{}
                                .SetCenter(stop.second)
                                .SetRadius(settings.stop_radius)
                                .SetFillColor("white")
            );
        }

        PassOn(move(document));
    }
};

class SetterBusLabels : public Worker {
public:
    SetterBusLabels(const ParametersForWorker& params) : Worker(params) {}
    void Process(unique_ptr<Svg::Document> document) override {

        for (const auto &bus: buses_colors) {
            StopsList stopsList = buses_dict.at(bus.first).getListStops();
            vector<Svg::Point> points;
            if (Route::ANNULAR == buses_dict.at(bus.first).getRoute()) {
                points.push_back(stops_coordinates.find(stopsList[0]->name)->second);
            } else {
                points.push_back(stops_coordinates.find(stopsList[0]->name)->second);
                if (stopsList[stopsList.size() / 2]->name != stopsList[0]->name) {
                    points.push_back(stops_coordinates.find(stopsList[stopsList.size() / 2]->name)->second);
                }
            }

            for (const auto &point: points) {

                document->
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
                document->
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

        PassOn(move(document));
    }
};

class SetterStopLabels : public Worker {
public:
    SetterStopLabels(const ParametersForWorker& params) : Worker(params) {}
    void Process(unique_ptr<Svg::Document> document) override {
        for (const auto &stop: stops_coordinates) {
            document->
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
            document->
                    Add(Svg::Text{}
                                .SetPoint(stop.second)
                                .SetOffset(settings.stop_label_offset)
                                .SetFontSize(settings.stop_label_font_size)
                                .SetFontFamily("Verdana")
                                .SetData(stop.first)
                                .SetFillColor("black"));

        }
        PassOn(move(document));
    }
};

class Runner : public Worker {
public:
    Runner(const ParametersForWorker& params) : Worker(params) {}

    void Run(unique_ptr<Svg::Document> document) override {
        PassOn(move(document));
    }

    void Process(unique_ptr<Svg::Document> document) override {}
};

class RenderDocument : public Worker {
public:
    RenderDocument(const ParametersForWorker& p, ostream& out) : Worker(p), out(out) {}
    void Process(unique_ptr<Svg::Document> document) override {
        document->Render(out);
    }

private:
    ostream& out;
};

class DocumentBuilder {
public:
    // добавляет в качестве первого обработчика Runner
    explicit DocumentBuilder(ParametersForWorker params_)
    : params(params_)
    {
        workers.push_back(make_unique<Runner>(params));
    }

    DocumentBuilder &SetBusLines() {
        workers.push_back(make_unique<SetterBusLines>(params));
        return *this;
    }

    DocumentBuilder& SetBusLabels() {
        workers.push_back(make_unique<SetterBusLabels>(params));
        return *this;
    }

    DocumentBuilder &SetStopPoints() {
        workers.push_back(make_unique<SetterStopPoints>(params));
        return *this;
    }

    DocumentBuilder &SetStopLabels() {
        workers.push_back(make_unique<SetterStopLabels>(params));
        return *this;
    }

    DocumentBuilder &SetRenderDocument(ostream& out) {
        workers.push_back(make_unique<RenderDocument>(params, out));
        return *this;
    }

    // строит цепочку с помощью метода Worker::SetNext и возвращает первый обработчик в построенной цепочке
    unique_ptr<Worker> Build() {
        for (int i = workers.size() - 1; i > 0; i--) {
            workers[i - 1]->SetNext(move(workers[i]));
        }

        return move(workers.front());
    }

private:
    vector<unique_ptr<Worker>> workers;
    const ParametersForWorker params;
};

#endif //BASEBUSES_MAPBUILDER_H
