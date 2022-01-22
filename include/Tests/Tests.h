#pragma once

#include <sstream>

#include "BaseBuses.h"
#include "BaseBusesBuilder.h"
#include "PasreRequests.h"
#include "BaseBusesProcess.h"

#include "test_runner.h"
#include "profile.h"

using namespace std;

stringstream GetStream();

void TestAll();