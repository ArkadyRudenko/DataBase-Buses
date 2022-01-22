#include <unordered_map>

#include "CommandBuild.h"

class AddStopCommand : public CommandBuild {
public:
    void Execute(BaseBuses&, nlohmann::json&) override;
};

std::unordered_map<std::string, int> CreateMapStops(const nlohmann::json&);