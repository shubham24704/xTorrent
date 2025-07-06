#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "bencode.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " decode <encoded_value>" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "decode") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " decode <encoded_value>" << std::endl;
            return 1;
        }

        std::string encoded_value = argv[2];
        try {
            json decoded = decode_bencoded_value(encoded_value);
            std::cout << decoded.dump() << std::endl;
        } catch (const std::exception& ex) {
            std::cerr << "Decoding error: " << ex.what() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
