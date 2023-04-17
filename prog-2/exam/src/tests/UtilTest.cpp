#include <stdlib.h>
#include <iostream>
#include <string>
#include "Util.hpp"

#define NUMBER_OF_RANDOM_TESTS 1000

using namespace std;

void testSplit() {
    string data1 = "ABC,DEF,10,2899.99";
    string data2 = "ABC,DEF,10,2899.99,";
    string data3 = ",DEF,10,";
    string data4 = "ABC,DEF,Z,2899.99";
    string data5 = "ABC,DEF,,";
    char separator = ',';

    vector<string> result1 = Util::split(data1, separator);
    if (result1.size() != 4 || result1[0] != "ABC" || result1[1] != "DEF" || result1[2] != "10" || result1[3] != "2899.99") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=first is incorrect (separator: \",\")" << endl;
    }

    vector<string> result2 = Util::split(data2, separator);
    if (result2.size() != 5 || result2[0] != "ABC" || result2[1] != "DEF" || result2[2] != "10" || result2[3] != "2899.99" || result2[4] != "") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=second is incorrect (separator: \",\")" << endl;
    }

    vector<string> result3 = Util::split(data3, separator);
    if (result3.size() != 4 || result3[0] != "" || result3[1] != "DEF" || result3[2] != "10" || result3[3] != "") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=third is incorrect (separator: \",\")" << endl;
    }

    vector<string> result4 = Util::split(data4, separator);
    if (result4.size() != 4 || result4[0] != "ABC" || result4[1] != "DEF" || result4[2] != "Z" || result4[3] != "2899.99") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=fourth is incorrect (separator: \",\")" << endl;
    }

    vector<string> result5 = Util::split(data5, separator);
    if (result5.size() != 4 || result5[0] != "ABC" || result5[1] != "DEF" || result5[2] != "" || result5[3] != "") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=fifth is incorrect (separator: \",\")" << endl;
    }

    data1 = "ABC;DEF;10;2899.99";
    data2 = "ABC;DEF;10;2899.99;";
    data3 = ";DEF;10;";
    data4 = "ABC;DEF;Z;2899.99";
    data5 = "ABC;DEF;;";
    separator = ';';

    result1 = Util::split(data1, separator);
    if (result1.size() != 4 || result1[0] != "ABC" || result1[1] != "DEF" || result1[2] != "10" || result1[3] != "2899.99") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=first is incorrect (separator: \";\")" << endl;
    }

    result2 = Util::split(data2, separator);
    if (result2.size() != 5 || result2[0] != "ABC" || result2[1] != "DEF" || result2[2] != "10" || result2[3] != "2899.99" || result2[4] != "") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=second is incorrect (separator: \";\")" << endl;
    }

    result3 = Util::split(data3, separator);
    if (result3.size() != 4 || result3[0] != "" || result3[1] != "DEF" || result3[2] != "10" || result3[3] != "") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=third is incorrect (separator: \";\")" << endl;
    }

    result4 = Util::split(data4, separator);
    if (result4.size() != 4 || result4[0] != "ABC" || result4[1] != "DEF" || result4[2] != "Z" || result4[3] != "2899.99") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=fourth is incorrect (separator: \";\")" << endl;
    }

    result5 = Util::split(data5, separator);
    if (result5.size() != 4 || result5[0] != "ABC" || result5[1] != "DEF" || result5[2] != "" || result5[3] != "") {
        cout << "%TEST_FAILED% time=0 testname=testSplit (UtilsTest) message=fifth is incorrect (separator: \";\")" << endl;
    }
}

void testGetRandomNumber() {
    int from = 0;
    int to = 100;

    for (int i = 0; i < NUMBER_OF_RANDOM_TESTS; ++i) {
        int result = Util::getRandomNumber(to, from);

        if (result < 0 || result >= to) {
            cout << "%TEST_FAILED% time=0 testname=testGetRandomNumber (UtilTest) message=" + to_string(result) + " should be between " + to_string(from) + " and " + to_string(to) << endl;
        }
    }

    from = -100;
    to = 1;

    for (int i = 0; i < NUMBER_OF_RANDOM_TESTS; ++i) {
        int result = Util::getRandomNumber(to, from);

        if (result < from || result >= to) {
            cout << "%TEST_FAILED% time=0 testname=testGetRandomNumber (UtilTest) message=" + to_string(result) + " should be between " + to_string(from) + " and " + to_string(to) << endl;
        }
    }
}

void testGetRandomElement() {
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    bool chosenElements[20]{};

    for (int i = 0; i < NUMBER_OF_RANDOM_TESTS; ++i) {
        int element = Util::getRandomElement(v);
        chosenElements[element] = true;
    }

    for (int i = 0; i < 20; ++i) {
        if (!chosenElements[i]) {
            cout << "%TEST_FAILED% time=0 testname=testGetRandomElement (UtilTest) message=" + to_string(i) + " should be chosen" << endl;
        }
    }
}

void stringFormatTest() {
    string s = "Sophia Schmidt";
    string result;

    cout << s.length() << endl;

    result = Util::extendToLength(s, 7);
    if (result.length() != 14 || result != "Sophia Schmidt") {
        cout << "%TEST_FAILED% time=0 testname=stringFormatTest (UtilTest) message=first" << endl;
    }

    result = Util::extendToLength(s, 14);
    if (result.length() != 14 || result != "Sophia Schmidt") {
        cout << "%TEST_FAILED% time=0 testname=stringFormatTest (UtilTest) message=second" << endl;
    }

    result = Util::extendToLength(s, 20);
    if (result.length() != 20 || result != "Sophia Schmidt      ") {
        cout << "%TEST_FAILED% time=0 testname=stringFormatTest (UtilTest) message=third" << endl;
    }
}

void testTryParseInt() {
    string s1 = "";
    string s2 = "3";
    string s3 = "314";
    string s4 = "p";
    string s5 = "1.9";
    string s6 = " ";
    int min = 1, max = 3;

    int i1, i2, i3, i4, i5, i6;

    bool int1Correct = false == Util::tryParseInt(s1, i1, min, max);
    bool int2Correct = true == Util::tryParseInt(s2, i2, min, max);
    bool int3Correct = false == Util::tryParseInt(s3, i3, min, max);
    bool int4Correct = false == Util::tryParseInt(s4, i4, min, max);
    bool int5Correct = true == Util::tryParseInt(s5, i5, min, max);
    bool int6Correct = false == Util::tryParseInt(s6, i6, min, max);

    if (!int1Correct) {
        cout << "%TEST_FAILED% time=0 testname=testTryParseInt (UtilTest) message=" + s1 + " should not be parsable!" << endl;
    }

    if (!int2Correct) {
        cout << "%TEST_FAILED% time=0 testname=testTryParseInt (UtilTest) message=" + s2 + " should be parsed to 3 but is " + to_string(i2) << endl;
    }

    if (!int3Correct) {
        cout << "%TEST_FAILED% time=0 testname=testTryParseInt (UtilTest) message=" + s3 + " should be parsed to 314 but not in the correct interval!" << endl;
    }

    if (!int4Correct) {
        cout << "%TEST_FAILED% time=0 testname=testTryParseInt (UtilTest) message=" + s4 + " should not be parsable!" << endl;
    }

    if (!int5Correct) {
        cout << "%TEST_FAILED% time=0 testname=testTryParseInt (UtilTest) message=" + s5 + " should be parsed to 1 but is " + to_string(i5) << endl;
    }

    if (!int6Correct) {
        cout << "%TEST_FAILED% time=0 testname=testTryParseInt (UtilTest) message=" + s6 + " should not be parsable!" << endl;
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% UtilTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testSplit (UtilTest)" << endl;
    testSplit();
    cout << "%TEST_FINISHED% time=0 testSplit (UtilTest)" << endl;

    cout << "%TEST_STARTED% testGetRandomNumber (UtilTest)" << endl;
    testGetRandomNumber();
    cout << "%TEST_FINISHED% time=0 testGetRandomNumber (UtilTest)" << endl;

    cout << "%TEST_STARTED% testGetRandomElement (UtilTest)" << endl;
    testGetRandomElement();
    cout << "%TEST_FINISHED% time=0 testGetRandomElement (UtilTest)" << endl;

    cout << "%TEST_STARTED% stringFormatTest (UtilTest)" << endl;
    stringFormatTest();
    cout << "%TEST_FINISHED% time=0 stringFormatTest (UtilTest)" << endl;

    cout << "%TEST_STARTED% testTryParseInt (UtilTest)" << endl;
    testTryParseInt();
    cout << "%TEST_FINISHED% time=0 testTryParseInt (UtilTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
