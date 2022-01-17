#pragma once

#include <iostream>

#include "BaseBuses.h"

class CommandBuild {
public:
    virtual void Execute(BaseBuses&, std::istream& is) = 0;
};