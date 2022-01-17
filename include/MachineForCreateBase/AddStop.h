#include "CommandBuild.h"

class AddStop : public CommandBuild {
public:
    void Execute(BaseBuses &buses, std::istream &is) override;
};
