#include <sstream>
#include <iostream>
#include <iomanip>
#include "TestsJson.h"
#include "test_runner.h"
#include "json.h"

using namespace Json;
using namespace std;

void JsonSimpleTest() {
    stringstream ss;
    ss << R"({"type": "Stop", "name": "Rasskazovka",
            "road_distances" : {"Marushkino": 3900} })";
    Node node = Load(ss).GetRoot();

    ASSERT_EQUAL("Stop", node.AsMap().at("type").AsString());
    ASSERT_EQUAL("Rasskazovka", node.AsMap().at("name").AsString());
    for(const auto&[key, value] : node.AsMap().at("road_distances").AsMap()) {
        ASSERT_EQUAL("Marushkino", key);
        ASSERT_EQUAL(3900, value.AsInt());
    }
}

void JsonArrayTest() {
    stringstream ss;
    ss << R"({"type": "Bus", "stops" : ["Biryulyovo Zapadnoye",
                                        "Biryusinka"]})";
    Node node = Load(ss).GetRoot();

    ASSERT_EQUAL("Bus", node.AsMap().at("type").AsString());
    ASSERT_EQUAL("Biryulyovo Zapadnoye", node.AsMap().at("stops").AsArray()[0].AsString());
    ASSERT_EQUAL("Biryusinka", node.AsMap().at("stops").AsArray()[1].AsString());
}

void JsonArrayTestN() {
    stringstream ss;
    ss << "{\"type\"\n      :\"Bus\", \n\n\"stops\" : [\"Biryulyovo Zapadnoye\",\"Biryusinka\"]}";
    Node node = Load(ss).GetRoot();

    ASSERT_EQUAL("Bus", node.AsMap().at("type").AsString());
    ASSERT_EQUAL("Biryulyovo Zapadnoye", node.AsMap().at("stops").AsArray()[0].AsString());
    ASSERT_EQUAL("Biryusinka", node.AsMap().at("stops").AsArray()[1].AsString());
}

void JsonAccessTest() {
    stringstream ss;
    ss << R"({"type": "Bus","stops" : ["Biryulyovo Zapadnoye",
                                        "Biryusinka"]})";
    Node node = Load(ss).GetRoot();
    ASSERT_EQUAL(true, (node.HasType<map<string, Node>>()));
    ASSERT_EQUAL("Bus", (node.AsMap().at("type").Get<string>()))
}

void JsonBigTest() {
    stringstream ss;
    ss << R"([{
                "type": "Bus",
                "stops" : ["Biryulyovo Zapadnoye",
                           "Biryusinka"],
                "is_bool": true
                },
                {
                "type": "Stop",
                "stops" : ["Stop1",
                           "Stop2"],
                "is_bool": true,
                "is_double": 5
                }])";
    auto node = Load(ss).GetRoot().AsArray();

    ASSERT_EQUAL(true, (node[0].AsMap().at("is_bool").AsBool()));
    ASSERT_EQUAL("Bus", (node[0].AsMap().at("type").AsString()));
    ASSERT_EQUAL("Biryusinka", (node[0].AsMap().at("stops").AsArray()[1].AsString()));
    ASSERT_EQUAL(5., (node[1].AsMap().at("is_double").AsDouble()));
}

void JsonPrintTest() {
    stringstream ss;
    ss << R"({"type": "Bus", "stops" : ["Biryulyovo Zapadnoye",
                                        "Biryusinka"], "MyBool" : true})";
    Node node = Load(ss).GetRoot();
}

void JsonDoubleTest() {
    stringstream ss;
    ss << R"({"d1": 1,
                "d2": 55.611087,
                "d3": 37.20829,
                "d4": 55.595884,
                "d5": 37.209755
                "d6": 37.645687
            })";
    auto node = Load(ss).GetRoot().AsMap();
    node["d1"].AsDouble();
    ASSERT_EQUAL(1, (node["d1"].AsInt()));
//    ASSERT_EQUAL(55.611087, (node["d2"].AsDouble()));
//    ASSERT_EQUAL(37.20829, (node["d3"].AsDouble()));
//    ASSERT_EQUAL(55.595884, (node["d4"].AsDouble()));
//    ASSERT_EQUAL(37.209755, (node["d5"].AsDouble()));
//    ASSERT_EQUAL(37.645687, (node["d6"].AsDouble()));
};

void TestJsonAll() {
    TestRunner tr;
    RUN_TEST(tr, JsonSimpleTest);
    RUN_TEST(tr, JsonArrayTest);
    RUN_TEST(tr, JsonAccessTest);
//    RUN_TEST(tr, JsonPrintTest);
    RUN_TEST(tr, JsonArrayTestN);
    RUN_TEST(tr, JsonBigTest);
    RUN_TEST(tr, JsonDoubleTest);
}