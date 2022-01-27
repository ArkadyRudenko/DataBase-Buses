#pragma once

#include <istream>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {

    class Node : std::variant<std::vector<Node>,
            std::map<std::string, Node>,
            int,
            std::string,
            double,
            bool> {
    public:
        using variant::variant;

        const auto &AsArray() const {
            return std::get<std::vector<Node>>(*this);
        }

        const auto &AsMap() const {
            return std::get<std::map<std::string, Node>>(*this);
        }

        int AsInt() const {
            return std::get<int>(*this);
        }

        const auto &AsString() const {
            return std::get<std::string>(*this);
        }

        const double AsDouble() const {
            if(std::holds_alternative<int>(*this)) {
                return static_cast<double>(std::get<int>(*this));
            } else {
                return std::get<double>(*this);
            }
        }

        const auto AsBool() const {
            return std::get<bool>(*this);
        }

        void operator[](const std::string& key);

        template <typename Z>
        bool HasType() const {
            return std::holds_alternative<Z>(*this);
        }

        template <typename Z>
        const Z& Get() const {
            return std::get<Z>(*this);
        }
    };

    class Document {
    public:
        explicit Document(Node root);

        const Node &GetRoot() const;

    private:
        Node root;
    };

    Document Load(std::istream &input = std::cin);

    std::ostream& operator<<(std::ostream& os, const Node& dt);
}