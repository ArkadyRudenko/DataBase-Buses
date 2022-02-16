#pragma once
//
// Created by arkady on 12.02.2022.
//

#ifndef SVG_TEST_H
#define SVG_TEST_H


#include <sstream>
#include <vector>
#include <variant>
#include <optional>
#include <memory>
#include <utility>
#include <string>
#include <utility>

namespace Svg {

    struct Point {
        double x = 0;
        double y = 0;
    };

    struct Rgb {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
    };

    struct Font {
        uint32_t font_size;
        std::string font_family;
    };

    using Color = std::variant<std::monostate, Rgb, std::string>;
    const Color NoneColor{};

    void RenderColor(std::ostream &out, std::monostate) {
        out << "none";
    }

    void RenderColor(std::ostream &out, Rgb rgb) {
        out << "rgb(" << static_cast<int>(rgb.red)
            << "," << static_cast<int>(rgb.green)
            << "," << static_cast<int>(rgb.blue) << ")";
    }

    void RenderColor(std::ostream &out, const std::string &str) {
        out << str;
    }

    void RenderColor(std::ostream& out, const Color& color) {
        visit([&out](const auto& value) { RenderColor(out, value); },
              color);
    }

    template<typename Child>
    class Figure {
    private:
        Child &GetLink() {
            return *static_cast<Child *>(this);
        }

    private:
        Color fill_color_;
        Color stroke_color_;
        double stroke_width_ = 1.0;
        std::optional<std::string> stroke_line_cap_;
        std::optional<std::string> stroke_line_join_;

    public:

        virtual Child &SetFillColor(const Color &color) {
            fill_color_ = color;
            return GetLink();
        }

        virtual Child &SetStrokeColor(const Color &stroke_color) {
            stroke_color_ = stroke_color;
            return GetLink();
        }

        virtual Child &SetStrokeWidth(double stroke_width) {
            stroke_width_ = stroke_width;
            return GetLink();
        }

        virtual Child &SetStrokeLineCap(const std::string &stroke_line_cap) {
            stroke_line_cap_ = stroke_line_cap;
            return GetLink();
        }

        virtual Child &SetStrokeLineJoin(const std::string &stroke_line_join) {
            stroke_line_join_ = stroke_line_join;
            return GetLink();
        }

        void RenderAttrs(std::ostream& out) const {
            out << "fill=\"";
            RenderColor(out, fill_color_);
            out << "\" ";
            out << "stroke=\"";
            RenderColor(out, stroke_color_);
            out << "\" ";
            out << "stroke-width=\"" << stroke_width_ << "\" ";
            if (stroke_line_cap_) {
                out << "stroke-linecap=\"" << *stroke_line_cap_ << "\" ";
            }
            if (stroke_line_join_) {
                out << "stroke-linejoin=\"" << *stroke_line_join_ << "\" ";
            }
        }
    };

    class Object {
    public:
        virtual void Render(std::ostream &out) const = 0;

        virtual ~Object() = default;
    };

    class Circle : public Object, public Figure<Circle> {
    public:
        Circle &SetCenter(Point);
        Circle &SetRadius(double);
        void Render(std::ostream& out) const override;
    private:
        Point centre;
        double radius = 1.0;
    };

    void Circle::Render(std::ostream& out) const {
        out << "<circle ";
        out << "cx=\"" << centre.x << "\" ";
        out << "cy=\"" << centre.y << "\" ";
        out << "r=\"" << radius << "\" ";
        Figure::RenderAttrs(out);
        out << "/>";
    }

    class Polyline : public Object, public Figure<Polyline> {
    public:
        Polyline &AddPoint(Point);
        void Render(std::ostream& out) const override;
    private:
        std::vector<Point> vertices;
    };

    void Polyline::Render(std::ostream& out) const {
        out << "<polyline ";
        out << "points=\"";
        bool first = true;
        for (const Point point : vertices) {
            if (first) {
                first = false;
            } else {
                out << " ";
            }
            out << point.x << "," << point.y;
        }
        out << "\" ";
        Figure::RenderAttrs(out);
        out << "/>";
    }

    class Text : public Object, public Figure<Text> {
    public:
        Text &SetPoint(Point);
        Text &SetOffset(Point);
        Text &SetFontSize(uint32_t);
        Text &SetFontFamily(const std::string &);
        Text &SetData(const std::string &);
        void Render(std::ostream& out) const override;
    private:
        std::string text;
        Point base_point;
        Point offset_;
        uint32_t font_size_ = 1;
        std::optional<std::string> font_family_;
    };

    void Text::Render(std::ostream& out) const {
        out << "<text ";
        out << "x=\"" << base_point.x << "\" ";
        out << "y=\"" << base_point.y << "\" ";
        out << "dx=\"" << offset_.x << "\" ";
        out << "dy=\"" << offset_.y << "\" ";
        out << "font-size=\"" << font_size_ << "\" ";
        if (font_family_) {
            out << "font-family=\"" << *font_family_ << "\" ";
        }
        Figure::RenderAttrs(out);
        out << ">";
        out << text;
        out << "</text>";
    }

    class Document : public Object {
    public:
        template <typename ObjectType>
        void Add(ObjectType object);

        void Render(std::ostream& out) const override;

    private:
        std::vector<std::unique_ptr<Object>> objects_;
    };

    template <typename ObjectType>
    void Document::Add(ObjectType object) {
        objects_.push_back(std::make_unique<ObjectType>(std::move(object)));
    }

    Circle &Circle::SetCenter(Point centre_) {
        centre = centre_;
        return *this;
    }

    Circle &Circle::SetRadius(double radius_) {
        radius = radius_;
        return *this;
    }

    void Document::Render(std::ostream &os) const {
        os << R"(<?xml version="1.0" encoding="UTF-8" ?>)";
        os << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)";

        for (const auto &item: objects_) {
            item->Render(os);
        }

        os << "</svg>";
    }

    template<typename T>
    void RecordItem(std::ostream &os, const std::string &str, T value) {
        os << str << "=\"" << value << "\" ";
    }


    Polyline &Polyline::AddPoint(Point point) {
        vertices.push_back(point);
        return *this;
    }

    Text &Text::SetPoint(Point point) {
        base_point = point;
        return *this;
    }

    Text &Text::SetOffset(Point offset) {
        offset_ = offset;
        return *this;
    }

    Text &Text::SetFontSize(uint32_t font_size) {
        font_size_ = font_size;
        return *this;
    }

    Text &Text::SetFontFamily(const std::string &font_family) {
        font_family_ = font_family;
        return *this;
    }

    Text &Text::SetData(const std::string &text_) {
        text = text_;
        return *this;
    }

}

#endif //SVG_TEST_H
