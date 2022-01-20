#include <unordered_map>

#include "Tests.h"
#include "GenereateLongTest.h"
#include "AddStop.h"

using namespace std;

void SimpleOnReadStopTest() {
    stringstream is;
    is << " Biryulyovo Zapadnoye > Biryusinka > "
          "Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye";
    vector<string> expected = {
            "Biryulyovo Zapadnoye", "Biryusinka", "Universam",
            "Biryulyovo Tovarnaya", "Biryulyovo Passazhirskaya",
            "Biryulyovo Zapadnoye"
    };
    ASSERT_EQUAL(expected, ReadStop(is).first);
}

void SimpleOnReadStopWithTireTest() {
    stringstream is;
    is << " Biryulyovo Zapadnoye - Biryusinka - "
          "Universam - Biryulyovo Tovarnaya - Biryulyovo Passazhirskaya ";
    vector<string> expected = {
            "Biryulyovo Zapadnoye", "Biryusinka", "Universam",
            "Biryulyovo Tovarnaya", "Biryulyovo Passazhirskaya"
    };
    ASSERT_EQUAL(expected, ReadStop(is).first);
}


void getTokensTest() {
    unordered_map<string, int> expected = {
            {"STOP",                  5},
            {"Biryulyovo Tovarnaya",  900},
            {"Rossoshanskaya ulitsa", 5600}
    };
    ASSERT_EQUAL(expected, getTokens(" 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya, 5m to STOP"));
}

void AddStopTest() {
    stringstream is;
    is << " Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m"
          " to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam";
    string name_stop;

    getline(is, name_stop, ':');
    is.ignore(1);
    double latitude, longitude;
    is >> latitude;
    is.ignore(1);
    is >> longitude;

    if (is.peek() == ',') {
        ASSERT_EQUAL("Biryulyovo Zapadnoye", RemoveSpaces(name_stop));
        ASSERT_EQUAL(latitude, 55.574371);
        ASSERT_EQUAL(longitude, 37.6517);
        is.ignore(1);
        string line;
        getline(is, line);
        unordered_map<string, int> exp {
                {"Universam", 2400}, {"Biryusinka", 1800}, {"Rossoshanskaya ulitsa", 7500}
        };
        ASSERT_EQUAL(exp, getTokens(line));
    }
}

void DifferentLengthTest() {
    stringstream ss;
    ss << "3\n"
          "Stop Stop1: 55, 37, 1000m to Stop2\n"
          "Stop Stop2: 50, 47, 50m to Stop1\n"
          "Bus 1: Stop1 - Stop2\n";
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase(ss);
    stringstream ss_proc;
    ss_proc << "1\n"
               "Bus 1\n";
    stringstream res;
    BaseBusesProcess(baseBuses, ss_proc, res);
    ASSERT_EQUAL("Bus 1: 3 stops on route, 2 unique stops, 1050 route length, 0.0006003184 curvature\n", res.str());
}

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, SimpleOnReadStopTest);
    RUN_TEST(tr, SimpleOnReadStopWithTireTest);
    RUN_TEST(tr, AddStopTest);
    RUN_TEST(tr, getTokensTest);
    RUN_TEST(tr, DifferentLengthTest);
}