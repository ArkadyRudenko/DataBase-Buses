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
//                os << '\n';
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
            os << "["; // \n
            int i = 0, size = node.AsArray().size();
            for (const auto &item: node.AsArray()) {
                os << item;
                if (i != size - 1) {
                    os << ',';
                }
//                os << '\n'; // \n
                i++;
            }
            os << "]";
        }
        return os;
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

    Node LoadInt(istream &input) {
        int result = 0;
        while (isdigit(input.peek())) {
            result *= 10;
            result += input.get() - '0';
        }
        return Node(result);
    }

    Node LoadDouble(istream &input) {
        string result;
        bool is_double = false;
        while (isdigit(input.peek()) || input.peek() == '.' || input.peek() == '-') {
            if (input.peek() == '.') {
                is_double = true;
            }
            result += input.get();
        }
        if (is_double) {
            return Node(strtod(result.c_str(), nullptr));
        } else {
            return Node(static_cast<int>(strtol(result.c_str(), nullptr, 10)));
        }
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
        } else if (c == '-' or isdigit(c)) {
            input.putback(c);
            return LoadDouble(input);
        } else if (c == 'f' or c == 't') {
            input.putback(c);
            return LoadBool(input);
        } else {
            input.putback(c);
            return LoadInt(input);
        }
    }

    void Node::push_back(double item) {
        if ((*this).HasType<vector<Node>>()) {
            get<std::vector<Node>>(*this).emplace_back(item);
        } else if (is_empty) {
            stringstream ss;
            ss << "[]";
            *this = LoadNode(ss);
            this->push_back(item);
        }
        is_empty = false;
    }

    void Node::push_back(int item) {
        if ((*this).HasType<vector<Node>>()) {
            get<std::vector<Node>>(*this).emplace_back(item);
        } else if (is_empty) {
            stringstream ss;
            ss << "[]";
            *this = Json::LoadNode(ss);
            this->push_back(item);
        }
        is_empty = false;
    }

    void Node::push_back(Node item) {
        if ((*this).HasType<vector<Node>>()) {
            get<std::vector<Node>>(*this).emplace_back(item);
        } else if (is_empty) {
            stringstream ss;
            ss << "[]";
            *this = LoadNode(ss);
            this->push_back(item);
        }
        is_empty = false;
    }

    void Node::push_back(std::string item) {
        if ((*this).HasType<vector<Node>>()) {
            get<std::vector<Node>>(*this).emplace_back(item);
        } else if (is_empty) {
            stringstream ss;
            ss << "[]";
            *this = LoadNode(ss);
            this->push_back(item);
        }
        is_empty = false;
    }

    void Node::push_back(bool item) {
        if ((*this).HasType<vector<Node>>()) {
            get<std::vector<Node>>(*this).emplace_back(item);
        } else if (is_empty) {
            stringstream ss;
            ss << "[]";
            *this = LoadNode(ss);
            this->push_back(item);
        }
        is_empty = false;
    }

    Document Load(istream &input) {
        return Document{LoadNode(input)};
    }

}