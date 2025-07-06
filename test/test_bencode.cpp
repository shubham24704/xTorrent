#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "../src/bencode.hpp"

using json = nlohmann::json;

// Your decoder function (from bencode.cpp)
json decode_bencoded_value(const std::string& encoded_value);

struct TestCase {
    std::string name;
    std::string input;
    json expected;
};

void run_test(const TestCase& tc) {
    try {
        json actual = decode_bencoded_value(tc.input);
        if (actual == tc.expected) {
            std::cout << "✅ Passed: " << tc.name << "\n";
        } else {
            std::cout << "❌ Failed: " << tc.name << "\n";
            std::cout << "   Input    : " << tc.input << "\n";
            std::cout << "   Expected : " << tc.expected.dump() << "\n";
            std::cout << "   Got      : " << actual.dump() << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "❌ Error in " << tc.name << ": " << e.what() << "\n";
    }
}

int main() {
    std::vector<TestCase> tests = {
        {"Integer",        "i42e",              42},
        {"Negative Int",   "i-17e",            -17},
        {"String",         "4:spam",           "spam"},
        {"Empty List",     "le",               json::array()},
        {"List of Ints",   "li1ei2ei3ee",      json::array({1, 2, 3})},
        {"List of Mixed",  "li42e3:fooe",      json::array({42, "foo"})},
        {"Empty Dict",     "de",               json::object()},
        {"Simple Dict",    "d3:foo3:bare",     json({{"foo", "bar"}})},
        {"Multi Dict",     "d3:foo3:bar3:bazi5ee", json({{"foo", "bar"}, {"baz", 5}})},
        {"Nested Dict",    "d4:dictd3:key5:valueee", json({{"dict", {{"key", "value"}}}})},
        {"Nested List",    "d4:listli10ei20ei30eee", json({{"list", {10, 20, 30}}})}
    };

    for (const auto& tc : tests) {
        run_test(tc);
    }

    return 0;
}
