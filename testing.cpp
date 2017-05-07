#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>

#include "lib/catch.hpp"
//#include "BracketHandler/BracketHandler.h"

using namespace std;

TEST_CASE("IsBracketsValid with invalid brackets", "[IsBracketsValid]") {
    REQUIRE(IsBracketsValid(")") == false);
    REQUIRE(IsBracketsValid("(") == false);
    REQUIRE(IsBracketsValid("]") == false);
    REQUIRE(IsBracketsValid("[") == false);
    REQUIRE(IsBracketsValid(")(") == false);
    REQUIRE(IsBracketsValid("][") == false);
    REQUIRE(IsBracketsValid("(])") == false);
    REQUIRE(IsBracketsValid("[(]") == false);
    REQUIRE(IsBracketsValid("[](") == false);
    REQUIRE(IsBracketsValid("[]())") == false);
    REQUIRE(IsBracketsValid("[())") == false);
    REQUIRE(IsBracketsValid("[()])") == false);
}

TEST_CASE("IsBracketsValid with valid brackets", "[IsBracketsValid]") {
    REQUIRE(IsBracketsValid("()") == true);
    REQUIRE(IsBracketsValid("[]") == true);
    REQUIRE(IsBracketsValid("()[]") == true);
    REQUIRE(IsBracketsValid("[]()") == true);
    REQUIRE(IsBracketsValid("()[]()") == true);
    REQUIRE(IsBracketsValid("([])") == true);
    REQUIRE(IsBracketsValid("[()]") == true);
    REQUIRE(IsBracketsValid("[([])()]()") == true);
}

void TestGenerationBrackets(string outputFileName, int inputLenght)
{
    ofstream outputFile(outputFileName);
    string s("");
    string d("");
    ValidBracketsGenerator(outputFile, inputLenght, s, d, 0);

    ifstream inputFile(outputFileName);
    string fileLine;
    while (getline(inputFile, fileLine))
    {
        REQUIRE(IsBracketsValid(fileLine) == true);
    }
}

TEST_CASE("Generate easy list with valid brackets", "[Generator]") {
    TestGenerationBrackets(std::string("../testdata/output.txt"), 2);
    TestGenerationBrackets(std::string("../testdata/output.txt"), 4);
    TestGenerationBrackets(std::string("../testdata/output.txt"), 6);
    TestGenerationBrackets(std::string("../testdata/output.txt"), 8);
    TestGenerationBrackets(std::string("../testdata/output.txt"), 12);
}