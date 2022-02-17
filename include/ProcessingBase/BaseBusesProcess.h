#pragma once
#include <iostream>

#include "BaseBuses.h"
#include "StateListen.h"
#include "json.h"

Json::Node BaseBusesProcess(BaseBuses &baseBuses,
                      const Json::Node&);

using MapStates = std::unordered_map<std::string, std::shared_ptr<Requests::StateListen>>;

MapStates CreateMapStates();