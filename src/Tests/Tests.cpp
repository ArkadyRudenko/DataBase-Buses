#include <sstream>

#include "Tests.h"
#include "TestsJson.h"
#include "FunctionsForTests.h"

#include "test_runner.h"
#include "profile.h"

#include "AllResources.h"

using namespace std;

void SimpleTest() {
    stringstream ss = LoadTest1();
    stringstream exp = LoadTest1Exp();
    ASSERT_EQUAL(RemoveSpaces(exp), GoBaseBuses(ss));
}

void SecondTest() {
    stringstream ss = LoadTest2();
    stringstream exp = LoadTest2Exp();
    ASSERT_EQUAL(RemoveSpaces(exp), GoBaseBuses(ss));
}

void ThirdTest() {
    stringstream ss = LoadTest3();
    stringstream exp = LoadTest3Exp();
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
    RUN_TEST(tr, SecondTest);
    RUN_TEST(tr, ThirdTest);
}