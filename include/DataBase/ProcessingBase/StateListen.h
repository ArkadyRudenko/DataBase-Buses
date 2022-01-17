#pragma once

#include "BaseBuses.h"

class StateListen {
public:
    virtual void Listen(BaseBuses&, std::ostream&, std::istream&) = 0;
};
