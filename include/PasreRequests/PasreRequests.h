#pragma once
#include "BusInfo.h"

std::string RemoveSpaces(std::string_view str);

std::vector<std::string> Split(std::string_view str, char c);

std::pair<std::vector<std::string>, Route> ReadStop(std::istream &is);

std::unordered_map<std::string, int> getTokens(std::string_view str);