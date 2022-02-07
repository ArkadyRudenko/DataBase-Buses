#pragma once

#include <istream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {

    class Node;
    using Dict = std::map<std::string, Node>;

    class Node : std::variant<std::vector<Node>,
            Dict,
            int,
            std::string,
            double,
            bool> {
    private:
        template <typename Z>
        const Z& GetType() const {
            return std::get<Z>(*this);
        }
        bool is_empty;
    public:
        using variant::variant;

        Node() {
            is_empty = true;
        };

        template<typename T>
        void push_back(std::string key, T value) {
            if((*this).HasType<std::map<std::string, Node>>()) {
                std::get<std::map<std::string, Node>>(*this).insert({key, value});
            } else if(is_empty) {
                std::stringstream ss;
                ss << "{}";
                std::map<std::string, Node> result;
                *this = result;
                this->push_back(key, value);
            }
            is_empty = false;
        }
        void push_back(double item);
        void push_back(int item);
        void push_back(Node);
        void push_back(std::string);
        void push_back(bool);

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

        double AsDouble() const {
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

    template <typename Value>
    void PrintValue(const Value& value, std::ostream& output) {
        output << value;
    }

    template <>
    void PrintValue<Dict>(const Dict& dict, std::ostream& output);
}