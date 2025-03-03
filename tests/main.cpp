/**
 * @file tests/main.cpp
 * @author Ray Richter
 * @note Main file for testing.
 */

// #define DEBUG
#include "../include/Validator.hpp"
#include <iostream>

#define MSG(msg) std::cout << msg << std::endl

enum class testEnum {
    INVALID,
    TIER1,
    TIER2,
    TIER3,
    TIER4,
    TIER5,
};

struct testStruct {
    const char* name;
    uint32_t id;
    bool operator==(const testStruct &other) const { return name == other.name && id == other.id; }
};

void compareKeys(const VKey_t &a, const VKey_t &b) {
    std::cout << std::endl;
    std::cout << "Comparing keys:";
    std::cout << "\n\tKey a: " <<= a;
    std::cout << "\n\tKey b: " <<= b;
    std::cout << "\n\ta >  b: " << (a >  b ? "TRUE" : "FALSE");
    std::cout << "\n\ta <  b: " << (a <  b ? "TRUE" : "FALSE");
    std::cout << "\n\ta >= b: " << (a >= b ? "TRUE" : "FALSE");
    std::cout << "\n\ta <= b: " << (a <= b ? "TRUE" : "FALSE");
    std::cout << "\n\ta == b: " << (a == b ? "TRUE" : "FALSE");
    std::cout << "\n\ta != b: " << (a != b ? "TRUE" : "FALSE");
    std::cout << "\n\t!a:     " << (a != b ? "TRUE" : "FALSE");    
    std::cout << std::endl;
}

template <class Data_t> void printTypeFlags() {
    std::cout << "Data type: " << typeid(Data_t).name();
    std::cout << ", Flags:";
    std::cout << "\n\tHas == op Flag: " << ((type_flags<Data_t> & EQUALITY_OP  ) ? "TRUE" : "FALSE");
    std::cout << "\n\tHas != op Flag: " << ((type_flags<Data_t> & INEQUALITY_OP) ? "TRUE" : "FALSE");
    std::cout << "\n\tHas < ops Flag: " << ((type_flags<Data_t> & COMPARISON_OP) ? "TRUE" : "FALSE");
    std::cout << "\n\tHas + ops Flag: " << ((type_flags<Data_t> & ARITHMATIC_OP) ? "TRUE" : "FALSE");
    std::cout << "\n\tHas  cout Flag: " << ((type_flags<Data_t> & PRINTABLE_OP ) ? "TRUE" : "FALSE");
    std::cout << std::endl;
}

void returnMath(const VReturn_t &a, const VReturn_t &b, const VKey_t &k) {
    std::cout << std::endl;
    VReturn_t c = a + b;
    std::cout << "Return math tests:";
    std::cout << "\n\tVReturn_t  a: " <<= a;
    std::cout << "\n\tVReturn_t  b: " <<= b;
    std::cout << "\n\tVKey_t     k: " <<= k;
    std::cout << "\n\tc = a + b; c: " <<= c;
    c = a;
    std::cout << "\n\tc =  a;    c: " << c;
    c += b;
    std::cout << "\n\tc += b;    c: " << c;
    c -= k;
    std::cout << "\n\tc -= k;    c: " << c;
    std::cout << "\n\ta >  b: " << (a >  b ? "TRUE" : "FALSE");
    std::cout << "\n\ta <  b: " << (a <  b ? "TRUE" : "FALSE");
    std::cout << "\n\ta >= b: " << (a >= b ? "TRUE" : "FALSE");
    std::cout << "\n\ta <= b: " << (a <= b ? "TRUE" : "FALSE");
    std::cout << "\n\ta == b: " << (a == b ? "TRUE" : "FALSE");
    std::cout << "\n\ta != b: " << (a != b ? "TRUE" : "FALSE");
    std::cout << std::endl;
}

// a and b must have the same subtype
template <class Data_t> void keyedDataMath(const VKeyedData_t<Data_t> &a, const VKeyedData_t<Data_t> &b) {
    std::cout << "Keyed data math tests:";
    std::cout << "\n\tVKeyedData_t a: " <<= a;
    std::cout << "\n\tVKeyedData_t b: " <<= b;
    std::cout << "\n\t-a: " << -a;
    std::cout << "\n\t+b: " << +b;
    std::cout << "\n\ta >  b: " << (a >  b ? "TRUE" : "FALSE");
    std::cout << "\n\ta <  b: " << (a <  b ? "TRUE" : "FALSE");
    std::cout << "\n\ta >= b: " << (a >= b ? "TRUE" : "FALSE");
    std::cout << "\n\ta <= b: " << (a <= b ? "TRUE" : "FALSE");
    std::cout << "\n\ta == b: " << (a == b ? "TRUE" : "FALSE");
    std::cout << "\n\ta != b: " << (a != b ? "TRUE" : "FALSE");
    std::cout << std::endl;
}

template <class Data_t> void keyedListTest(const VKeyedList_t<Data_t> &list) {
    // std::cout << "Keyed list info: " <<= list;
    // std::cout << std::endl;

}

void main() {

    std::cout << "Starting Validator Testing..." << std::endl;

    // VKey_t testing...

    VKey_t testKey, whiteKey = VKey_t::WHITELIST, blackKey = VKey_t::BLACKLIST, smallKey = 5, bigKey = 573789, perfectKey = VKey_t::PERFECT;

    std::cout << "Created a default key: " << testKey; std::cout << std::endl;
    std::cout << "Created a whitelist key: " <<= whiteKey; std::cout << std::endl;
    compareKeys(smallKey, bigKey);
    compareKeys(whiteKey, blackKey);
    compareKeys(bigKey, perfectKey);
    compareKeys(perfectKey, blackKey);

    // VReturn_t testing...

    VReturn_t ret, passRet = VReturn_t::PASS, failRet = VReturn_t::FAIL, perfRet = VReturn_t::PERFECT, ret1 = 12, ret2 = 432, ret3 = 9723;
    returnMath(ret, passRet, testKey);
    returnMath(ret1, ret2, blackKey);
    returnMath(perfRet, failRet, bigKey);
    returnMath(failRet, ret3, perfectKey);

    // Type flags testing...

    printTypeFlags<int>();
    printTypeFlags<float>();
    printTypeFlags<testEnum>();
    printTypeFlags<testStruct>();

    // VKeyedData_t testing...

    VKeyedData_t<int> intData1, intData2 = {VKey_t::BLACKLIST, 10}, intData3 = {100, 20};
    VKeyedData_t<float> fData1(1.0f), fData2(VKey_t::PERFECT, 3.14f), fData3 = {VKey_t::MAXIMUM, 6.28f};
    VKeyedData_t<testEnum> eData1, eData2 = {1, testEnum::TIER1}, eData3 = {2, testEnum::TIER2}, eData4 = {3, testEnum::TIER3};
    VKeyedData_t<testStruct> sData1 = {VKey_t::BLACKLIST, {"a", 1}}, sData2 = {VKey_t::BLACKLIST, {"b", 2}}, 
        sData3 = {VKey_t::BLACKLIST, {"c", 3}}, sData4 = {VKey_t::BLACKLIST, {"d", 4}}, sData5 = {VKey_t::BLACKLIST, {"e", 5}};
    keyedDataMath(intData1, intData2);
    keyedDataMath(fData2, fData3);
    keyedDataMath(eData1, eData3);
    keyedDataMath(sData1, sData2);
    keyedDataMath(sData3, sData4);

    // VKeyedList_t testing...

    VKeyedList_t<int> intList(1);
    VKeyedList_t<float> floatList({{10, 1.0f}, {5, 2.0f}, {2, 3.0f}, {1, 4.0f}, {0, 5.0f}});
    VKeyedList_t<testEnum> enumList;
    VKeyedList_t<testStruct> structList;

    // keyedListTest(intList);
    // keyedListTest(floatList);
    // keyedListTest(enumList);
    // keyedListTest(structList);

    std::cout << "\nVKeyedList_t tests: " << std::endl;
    std::cout << "\tintList.query(0): " << intList.query(0) << std::endl;
    std::cout << "\tintList.query(1): " << intList.query(1) << std::endl;
    std::cout << "\tintList.query(2): " << intList.query(2) << std::endl;
    std::cout << "\n";
    std::cout << "\tintList += std::vector<int>{5, 6, 7};\n"; intList += std::vector<int>{5, 6, 7};
    std::cout << "\tintList += VKeyedData_t<int>{5, 9};\n";   intList += VKeyedData_t<int>{5, 9};
    std::cout << "\tintList -= {11, 12, 13, 14, 15};\n";      intList -= {11, 12, 13, 14, 15};
    std::cout << "\n";
    std::cout << "\tintList(5):  " << intList(5)  << std::endl;
    std::cout << "\tintList(9):  " << intList(9)  << std::endl;
    std::cout << "\tintList(15): " << intList(15) << std::endl;
    std::cout << "\n";
    std::cout << "\tfloatList.query(0.0f): " << floatList.query(0.0f) << std::endl;
    std::cout << "\tfloatList.query(1.0f): " << floatList.query(1.0f) << std::endl;
    std::cout << "\tfloatList.query(1.5f): " << floatList.query(1.5f) << std::endl;
    std::cout << "\tfloatList.query(2.0f): " << floatList.query(2.0f) << std::endl;
    std::cout << "\tfloatList.query(3.0f): " << floatList.query(3.0f) << std::endl;
    std::cout << "\tfloatList.query(4.0f): " << floatList.query(4.0f) << std::endl;
    std::cout << "\tfloatList.query(5.0f): " << floatList.query(5.0f) << std::endl;
    std::cout << "\n";
    std::cout << "\tenumList -= testEnum::TIER1\n"; enumList -= testEnum::TIER1;
    std::cout << "\tenumList -= testEnum::TIER2\n"; enumList -= testEnum::TIER2;
    std::cout << "\tenumList -= testEnum::TIER3\n"; enumList -= testEnum::TIER3;
    std::cout << "\tenumList -= testEnum::TIER4\n"; enumList -= testEnum::TIER4;
    std::cout << "\n";
    std::cout << "\tenumList.query(TIER4): " << enumList.query(testEnum::TIER4) << std::endl;
    std::cout << "\tenumList.query(TIER5): " << enumList.query(testEnum::TIER5) << std::endl;

// // Lets assume something has 4 int traits and we want to find the best candidate out of a list of candidates
//     // 1. Create a validator for each trait
//     Validator<int> V1, V2, V3, V4;
    
//     // 2. Set valid conditions for each trait
//     //  2a. Trait 1 must be > 10 or == 1
//     VKeyedList_t<int> trait1 = {{VKey_t::MINIMUM, 10}, {VKey_t::WHITELIST, 1}};
//     V1 += trait1; // or V1.add(trait1);
//     //  2b. Trait 2 must not be -21, -22, -23, or -24
//     VList_t<int> trait2 = {-21, -22, -23, -24};
//     V2 -= trait2; // or V2.add(VKey_t::BLACKLIST, trait2);
//     //  2c. Trait 3 can be any value. Leave the validator empty
//     V3;
//     //  2d. Trait 4 has values with higher scores than others
//     VKeyedList_t<int> trait4 = { // {score, value}
//         {1,  0}, {1,  1}, {1,  2}, {4,  3}, {4,  4}, {4,  5}, {3,  6}, {3,  7}, {7,  8}, {7,  9}, 
//         {1, 10}, {1, 11}, {1, 12}, {4, 13}, {4, 14}, {4, 15}, {3, 16}, {3, 17}, {7, 18}, {7, 19}, 
//     };
//     V4 += trait4;

//     // 3. Get a list of candidates and their traits
//     std::vector<std::vector<int>> intCandidates = {
//         {  1,   2,   3,   4}, 
//         { 11,  12,  13,  14}, 
//         {-21, -22, -23, -24},
//         {105, 274,  -1,   0},
//         {  1, -24, 127,   4}, 
//         {  1,  24, 256, -40}, 
//         {  1,   2, -10,   4}, 
//         {  1,   2,   0,  18}, 
//     };
//     // 4. Make a list of scores
//     std::vector<VReturn_t> cScores;

//     // 5. Evaluate the suitability of every candidate
//     for (const auto candidate : intCandidates) {
//         VReturn_t t1Score = V1(candidate[0]);
//         std::cout << "Trait 1 score: " << t1Score << std::endl;
//         VReturn_t t2Score = V2(candidate[1]);
//         std::cout << "Trait 2 score: " << t2Score << std::endl;
//         VReturn_t t3Score = V3(candidate[2]);
//         std::cout << "Trait 3 score: " << t3Score << std::endl;
//         VReturn_t t4Score = V4(candidate[3]);
//         std::cout << "Trait 4 score: " << t4Score << std::endl;

//         VReturn_t totalScore = t1Score + t2Score + t3Score + t4Score;
//         cScores.push_back(totalScore);
//         std::cout << "Candidate evaluated with score: " <<= totalScore;
//         std::cout << std::endl;
//     }
}