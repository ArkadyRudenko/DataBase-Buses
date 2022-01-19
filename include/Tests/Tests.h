#pragma once

#include <sstream>

#include "BaseBuses.h"
#include "BaseBusesBuilder.h"
#include "PasreRequests.h"
#include "BaseBusesProcess.h"

#include "test_runner.h"
#include "profile.h"

using namespace std;

void SimpleOnReadStopTest();

void SimpleOnReadStopWithTireTest();

void SimpleOnDataBaseTest();

void StringBusesOnDataBaseTest();

void SameStopsBusesOnDataBaseTest();

void CheckInfoStopsBusesOnDataBaseTest();

void LongOnDataBaseTest();

void TestAll();