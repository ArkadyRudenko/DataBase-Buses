#pragma once
#include <iostream>

#include "BaseBuses.h"
#include "StateListen.h"
#include "nlohmann/json.hpp"

void BaseBusesProcess(BaseBuses &baseBuses,
                      const nlohmann::json&,
                      std::ostream& os = std::cout);

using MapStates = std::unordered_map<std::string, std::shared_ptr<StateListen>>;

MapStates CreateMapStates();