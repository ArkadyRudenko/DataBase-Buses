#include <iostream>
#include <ranges>
#include <algorithm>

#include "BaseBusesBuilder.h"
#include "BaseBusesProcess.h"
#include "Tests.h"
#include "profile.h"

using namespace std;
namespace rng = std::ranges;

int main() {
    TestAll();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase();
    BaseBusesProcess(baseBuses);

}