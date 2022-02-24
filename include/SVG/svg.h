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

    struct Rgba {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        double alpha = 0;
    };

    using Color = std::variant<std::monostate, Rgb, Rgba, std::string>;
    const Color NoneColor{};

    void RenderColor(std::ostream &out, std::monostate);
    void RenderColor(std::ostream &out, Rgb rgb);
    void RenderColor(std::ostream &out, Rgba rgba);
    void RenderColor(std::ostream &out, const std::string &str);
    void RenderColor(std::ostream& out, const Color& color);

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

    class Polyline : public Object, public Figure<Polyline> {
    public:
        Polyline &AddPoint(Point);
        void Render(std::ostream& out) const override;
    private:
        std::vector<Point> vertices;
    };

    class Text : public Object, public Figure<Text> {
    public:
        Text &SetPoint(Point);
        Text &SetOffset(Point);
        Text &SetFontSize(uint32_t);
        Text &SetFontFamily(const std::string &);
        Text &SetData(const std::string &);
        Text &SetFontWeight(const std::string &);
        void Render(std::ostream& out) const override;
    private:
        std::string text;
        Point base_point;
        Point offset_;
        uint32_t font_size_ = 1;
        std::optional<std::string> font_family_;
        std::optional<std::string> font_weight_;
    };

    class Document : public Object {
    public:
        template <typename ObjectType>
        void Add(ObjectType object) {
            objects_.push_back(std::make_unique<ObjectType>(std::move(object)));
        }

        void Render(std::ostream& out) const override;

    private:
        std::vector<std::unique_ptr<Object>> objects_;
    };
}

#endif //SVG_TEST_H
