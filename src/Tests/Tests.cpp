#include <sstream>

#include "Tests.h"
#include "TestsJson.h"
#include "FunctionsForTests.h"

#include "test_runner.h"
#include "profile.h"

using namespace std;

void SimpleTest() {
    stringstream ss;
    ss << R"({"base_requests": [{"type": "Stop", "name": "Tolstopaltsevo", "latitude": 55.611087, "longitude": 37.20829, "road_distances": {"Marushkino": 3900}}, {"type": "Stop", "name": "Marushkino", "latitude": 55.595884, "longitude": 37.209755, "road_distances": {"Rasskazovka": 9900}}, {"type": "Bus", "name": "256", "stops": ["Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya", "Biryulyovo Passazhirskaya", "Biryulyovo Zapadnoye"], "is_roundtrip": true}, {"type": "Bus", "name": "750", "stops": ["Tolstopaltsevo", "Marushkino", "Rasskazovka"], "is_roundtrip": false}, {"type": "Stop", "name": "Rasskazovka", "latitude": 55.632761, "longitude": 37.333324, "road_distances": {}}, {"type": "Stop", "name": "Biryulyovo Zapadnoye", "latitude": 55.574371, "longitude": 37.6517, "road_distances": {"Biryusinka": 1800, "Universam": 2400, "Rossoshanskaya ulitsa": 7500}}, {"type": "Stop", "name": "Biryusinka", "latitude": 55.581065, "longitude": 37.64839, "road_distances": {"Universam": 750}}, {"type": "Stop", "name": "Universam", "latitude": 55.587655, "longitude": 37.645687, "road_distances": {"Biryulyovo Tovarnaya": 900, "Rossoshanskaya ulitsa": 5600}}, {"type": "Stop", "name": "Biryulyovo Tovarnaya", "latitude": 55.592028, "longitude": 37.653656, "road_distances": {"Biryulyovo Passazhirskaya": 1300}}, {"type": "Stop", "name": "Biryulyovo Passazhirskaya", "latitude": 55.580999, "longitude": 37.659164, "road_distances": {"Biryulyovo Zapadnoye": 1200}}, {"type": "Bus", "name": "828", "stops": ["Biryulyovo Zapadnoye", "Universam", "Rossoshanskaya ulitsa", "Biryulyovo Zapadnoye"], "is_roundtrip": true}, {"type": "Stop", "name": "Rossoshanskaya ulitsa", "latitude": 55.595579, "longitude": 37.605757, "road_distances": {}}, {"type": "Stop", "name": "Prazhskaya", "latitude": 55.611678, "longitude": 37.603831, "road_distances": {}}], "stat_requests": [{"id": 1658724867, "type": "Bus", "name": "256"}, {"id": 1254699557, "type": "Bus", "name": "750"}, {"id": 1323453510, "type": "Bus", "name": "751"}, {"id": 1977602064, "type": "Stop", "name": "Samara"}, {"id": 962310853, "type": "Stop", "name": "Prazhskaya"}, {"id": 888211548, "type": "Stop", "name": "Biryulyovo Zapadnoye"}]})";
    stringstream exp;
    exp << R"([
{ "curvature": 1.36124,"request_id": 1658724867,"route_length": 5950,"stop_count": 6,"unique_stop_count": 5},
{ "curvature": 1.31808,"request_id": 1254699557,"route_length": 27600,"stop_count": 5,"unique_stop_count": 3},
{ "error_message": "not found","request_id": 1323453510},
{ "error_message": "not found","request_id": 1977602064},
{ "buses": [],"request_id": 962310853},
{ "buses": ["256","828"],"request_id": 888211548}
])";
    ASSERT_EQUAL(RemoveSpaces(exp), GoBaseBuses(ss));
}


void RemoveSpacesTest() {
    stringstream ss;
    ss << " P\n\n P\n ";
    ASSERT_EQUAL("PP", RemoveSpaces(ss));
}

void TestAll() {
    TestJsonAll();
    TestRunner tr;
    RUN_TEST(tr, RemoveSpacesTest);
    RUN_TEST(tr, SimpleTest);
}