#pragma once
#include "BusInfo.h"

std::string RemoveSpaces(std::string_view str);

std::vector<std::string> Split(std::string_view str, char c);

//std::vector<std::string> ReadStop(const Json::Node& stops);

std::unordered_map<std::string, int> getTokens(std::string_view str);