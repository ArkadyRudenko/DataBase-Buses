//
// Created by arkady on 17.02.2022.
//

#include "svg.h"

namespace Svg {
    void RenderColor(std::ostream &out, std::monostate) {
        out << "none";
    }

    void RenderColor(std::ostream &out, Rgb rgb) {
        out << "rgb(" << static_cast<int>(rgb.red)
            << "," << static_cast<int>(rgb.green)
            << "," << static_cast<int>(rgb.blue) << ")";
    }

    void RenderColor(std::ostream &out, Rgba rgba) {
        out << "rgba(" << static_cast<int>(rgba.red)
            << "," << static_cast<int>(rgba.green)
            << "," << static_cast<int>(rgba.blue)
            << "," << rgba.alpha << ")";
    }

    void RenderColor(std::ostream &out, const std::string &str) {
        out << str;
    }

    void RenderColor(std::ostream& out, const Color& color) {
        visit([&out](const auto& value) { RenderColor(out, value); },
              color);
    }

    void Circle::Render(std::ostream& out) const {
        out << "<circle ";
        out << "cx=\"" << centre.x << "\" ";
        out << "cy=\"" << centre.y << "\" ";
        out << "r=\"" << radius << "\" ";
        Figure::RenderAttrs(out);
        out << "/>";
    }

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
        if(font_weight_) {
            out << "font-weight=\"" << *font_weight_ << "\" ";
        }
        Figure::RenderAttrs(out);
        out << ">";
        out << text;
        out << "</text>";
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

    Text &Text::SetFontWeight(const std::string &font_weight) {
        font_weight_ = font_weight;
        return *this;
    }
}