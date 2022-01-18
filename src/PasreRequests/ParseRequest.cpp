#include <algorithm>
#include <sstream>
#include <string>

#include "PasreRequests.h"

using namespace std;
namespace rng = std::ranges;


string RemoveSpaces(string_view str) {
    if (str.front() == ' ') {
        str.remove_prefix(1);
    }
    if (str.back() == ' ') {
        str.remove_suffix(1);
    }
    return string(str);
}


vector<string> Split(string_view str, char c) {
    vector<string> result;

    while (true) {
        size_t space = str.find(c);
        result.push_back(RemoveSpaces(
                str.substr(0, space
                )));

        if (space == str.npos) {
            break;
        } else {
            str.remove_prefix(space + 1);
        }
    }
#ifdef TEST
    for (auto &s: result) {
        cout << s << "|" << endl;
    }
#endif
    return result;
}

vector<string> ReadStop(istream &is) {
    string line;
    char top;
    getline(is, line);
    auto it = rng::find_if(line, [](char ch) {
        return ch == '>';
    });
    if (it == line.end()) {
        top = '-';
    } else {
        top = '>';
    }

    return Split(line, top);
}