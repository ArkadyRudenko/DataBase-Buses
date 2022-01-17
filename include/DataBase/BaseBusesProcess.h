#pragma once
#include "BaseBuses.h"
#include "StateListen.h"

void BaseBusesProcess(BaseBuses &baseBuses,
                      std::istream &is = std::cin,
                      std::ostream& os = std::cout);

using MapStates = std::unordered_map<std::string, std::shared_ptr<StateListen>>;

MapStates CreateMapStates();