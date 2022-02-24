#include <sstream>

#include "json.h"

using namespace std;

namespace Json {

    Document::Document(Node root) : root(move(root)) {
    }

    ostream &operator<<(ostream &os, const Node &node) {
        if (node.HasType<map<string, Node>>()) {
            os << "{ ";
            int i = 0, size = node.AsMap().size();
            for (const auto&[key, value]: node.AsMap()) {
                os << "\"" << key << "\"" << ": ";
                os << value;
                if (i != size - 1) {
                    os << ',';
                }
                i++;
            }
            os << "}";
        } else if (node.HasType<string>()) {
            os << "\"" << node.AsString() << "\"";
        } else if (node.HasType<double>()) {
            os << node.AsDouble();
        } else if (node.HasType<int>()) {
            os << node.AsInt();
        } else if (node.HasType<bool>()) {
            os << (node.AsBool() ? "true" : "false");
        } else if (node.HasType<vector<Node>>()) {
            os << "[";
            int i = 0, size = node.AsArray().size();
            for (const auto &item: node.AsArray()) {
                os << item;
                if (i != size - 1) {
                    os << ',';
                }
                i++;
            }
            os << "]";
        }
        return os;
    }

    template <>
    void PrintValue<Dict>(const Dict& dict, std::ostream& output) {
        output << '{';
        bool first = true;
        for (const auto& [key, node]: dict) {
            if (!first) {
                output << ", ";
            }
            first = false;
            PrintValue(key, output);
            output << ": ";
            output << node;
        }
        output << '}';
    }

    const Node &Document::GetRoot() const {
        return root;
    }

    Node LoadNode(istream &input);

    Node LoadArray(istream &input) {
        vector<Node> result;

        for (char c; input >> c && c != ']';) {
            if (c != ',') {
                input.putback(c);
            }
            result.push_back(LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNumber(istream& input) {
        bool is_negative = false;
        if (input.peek() == '-') {
            is_negative = true;
            input.get();
        }
        int int_part = 0;
        while (isdigit(input.peek())) {
            int_part *= 10;
            int_part += input.get() - '0';
        }
        if (input.peek() != '.') {
            return Node(int_part * (is_negative ? -1 : 1));
        }
        input.get();  // '.'
        double result = int_part;
        double frac_mult = 0.1;
        while (isdigit(input.peek())) {
            result += frac_mult * (input.get() - '0');
            frac_mult /= 10;
        }
        return Node(result * (is_negative ? -1 : 1));
    }

    Node LoadBool(istream &input) {
        char ch;
        if ((ch = input.get()) == 't' and
            input.get() == 'r' and
            input.get() == 'u' and
            input.get() == 'e') {
            return Node(true);
        } else if (ch == 'f' and
                   input.get() == 'a' and
                   input.get() == 'l' and
                   input.get() == 's' and
                   input.get() == 'e') {
            return Node(false);
        }
    }

    Node LoadString(istream &input) {
        string line;
        getline(input, line, '"');
        return Node(move(line));
    }

    Node LoadDict(istream &input) {
        map<string, Node> result;

        for (char c; input >> c && c != '}';) {
            if (c == ',') {
                input >> c;
            }

            string key = LoadString(input).AsString();
            input >> c;
            result.emplace(move(key), LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNode(istream &input) {
        char c;
        input >> c;

        if (c == '[') {
            return LoadArray(input);
        } else if (c == '{') {
            return LoadDict(input);
        } else if (c == '"') {
            return LoadString(input);
        } else if (c == 't' || c == 'f') {
            input.putback(c);
            return LoadBool(input);
        } else {
            input.putback(c);
            return LoadNumber(input);
        }
    }

    Document Load(istream &input) {
        return Document{LoadNode(input)};
    }

}