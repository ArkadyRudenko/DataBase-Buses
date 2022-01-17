#pragma once

//#define TEST

std::string RemoveSpaces(std::string_view str);

std::vector<std::string> Split(std::string_view str, char c);

std::vector<std::string> ReadStop(std::istream &is);