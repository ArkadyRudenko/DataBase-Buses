#pragma once
#include <iostream>

#include "BaseBuses.h"
#include "StateListen.h"
#include "json.h"

void BaseBusesProcess(BaseBuses &baseBuses,
                      const Json::Node&,
                      std::ostream& os = std::cout);

using MapStates = std::unordered_map<std::string, std::shared_ptr<StateListen>>;

MapStates CreateMapStates();