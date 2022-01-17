#pragma once
#include "CommandBuild.h"

class AddBusCommand : public CommandBuild {
public:
    void Execute(BaseBuses& baseBuses, std::istream &is) override;
};
