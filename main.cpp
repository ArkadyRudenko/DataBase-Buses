#include <iostream>
#include <ranges>
#include <algorithm>

#include "include/DataBase/BaseBusesBuilder.h"
#include "include/DataBase/BaseBusesProcess.h"
#include "include/Tests/Tests.h"

using namespace std;
namespace rng = std::ranges;

int main() {
    TestAll();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase();
    BaseBusesProcess(baseBuses);
}