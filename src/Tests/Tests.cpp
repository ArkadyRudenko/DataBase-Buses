#include "Tests.h"
#include "GenereateLongTest.h"

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

void SimpleOnDataBaseTest() {
    stringstream is;
    is << "10\n"
          "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
          "Stop Marushkino: 55.595884, 37.209755\n"
          "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
          "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
          "Stop Rasskazovka: 55.632761, 37.333324\n"
          "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
          "Stop Biryusinka: 55.581065, 37.64839\n"
          "Stop Universam: 55.587655, 37.645687\n"
          "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
          "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
          "3\n"
          "Bus 256\n"
          "Bus 750\n"
          "Bus 751";
    string expected = "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length\n"
                      "Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length\n"
                      "Bus 751: not found\n";
    stringstream realresult;
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase(is);
    BaseBusesProcess(baseBuses, is, realresult);
    ASSERT_EQUAL(expected, realresult.str());
}

void ExceptionOnDataBaseTest() {
    stringstream is;
    is << "10\n"
          "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
          "Stop Marushkino: 55.595884, 37.209755\n"
          "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
          "Bus 750( Tolstopaltsevo - Marushkino - Rasskazovka\n"
          "Stop Rasskazovka: 55.632761, 37.333324\n"
          "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
          "Stop Biryusinka: 55.581065, 37.64839\n"
          "Stop Universam: 55.587655, 37.645687\n"
          "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
          "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
          "3\n"
          "Bus 256\n"
          "Bus 750\n"
          "Bus 751";
    string expected = "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length\n"
                      "Bus 750: not found\n"
                      "Bus 751: not found\n";
    stringstream real_result;
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase(is);
    BaseBusesProcess(baseBuses, is, real_result);
    ASSERT_EQUAL(expected, real_result.str());
}

void StringBusesOnDataBaseTest() {
    stringstream is;
    is << "10\n"
          "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
          "Stop Marushkino: 55.595884, 37.209755\n"
          "Bus BUS25: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
          "Bus B B: Tolstopaltsevo - Marushkino - Rasskazovka\n"
          "Stop Rasskazovka: 55.632761, 37.333324\n"
          "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
          "Stop Biryusinka: 55.581065, 37.64839\n"
          "Stop Universam: 55.587655, 37.645687\n"
          "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
          "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
          "3\n"
          "Bus BUS25\n"
          "Bus B B\n"
          "Bus 751";
    string expected = "Bus BUS25: 6 stops on route, 5 unique stops, 4371.02 route length\n"
                      "Bus B B: 5 stops on route, 3 unique stops, 20939.5 route length\n"
                      "Bus 751: not found\n";
    stringstream real_result;
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase(is);
    BaseBusesProcess(baseBuses, is, real_result);
    ASSERT_EQUAL(expected, real_result.str());
}


void TestSameStopsBusesOnDataBaseTest() {
    stringstream is;
    is << "9\n"
          "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
          "Stop Marushkino: 55.595884, 37.209755\n"
          "Bus 100: Tolstopaltsevo - Marushkino - Rasskazovka - Biryusinka - Tolstopaltsevo - Marushkino\n"
          "Stop Rasskazovka: 55.632761, 37.333324\n"
          "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
          "Stop Biryusinka: 55.581065, 37.64839\n"
          "Stop Universam: 55.587655, 37.645687\n"
          "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
          "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
          "1\n"
          "Bus 100\n";
    string expected = "Bus 100: 11 stops on route, 4 unique stops, 4371.02 route length\n";

    stringstream real_result;
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase(is);
    BaseBusesProcess(baseBuses, is, real_result);
//    ASSERT_EQUAL(expected, real_result.str());
}


void LongTestOnDataBase() {
    stringstream is;
    Generate(is);
    BaseBuses baseBuses = BaseBusesBuilder().BuildBase(is);
    stringstream is_process;
    stringstream is_result;
    GenerateReq(is_process);
    BaseBusesProcess(baseBuses, is_process, is_result);
}

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, SimpleOnReadStopTest);
    RUN_TEST(tr, SimpleOnReadStopWithTireTest);
    RUN_TEST(tr, SimpleOnDataBaseTest);
    RUN_TEST(tr, StringBusesOnDataBaseTest);
    RUN_TEST(tr, TestSameStopsBusesOnDataBaseTest);
//    RUN_TEST(tr, ExceptionTestOnDataBase);
    {
        LOG_DURATION("Long Test");
        LongTestOnDataBase();
    }
}