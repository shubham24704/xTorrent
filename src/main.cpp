#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

#include "lib/nlohmann/json.hpp"

using json = nlohmann::json;

json decode_bencoded_value(const std::string& encoded_value, size_t &index);

json decode_bencoded_integer(const std::string& encoded_value, size_t &index){
    index++;
    size_t start = index;
    while(encoded_value[index]!='e') index++;
    size_t length = index - start;
    index++;
    return json(std::stoll(encoded_value.substr(start,length)));
}

json decode_bencoded_string(const std::string& encoded_value, size_t &index){
    std::string number = "";
    while(encoded_value[index] != ':'){
        number += encoded_value[index];
        index++;
    }
    index++;
    size_t length = std::stoll(number);
    std:: string result = "";
    while(length--){
        result += encoded_value[index];
        index++;
    }
    return json(result);
}

json decode_bencoded_list(const std::string& encoded_value, size_t &index){
    index++;
    json result = json::array();
    while(encoded_value[index] != 'e'){
        result.push_back(decode_bencoded_value(encoded_value,index));
    }
    index++;
    return json(result);
}

json decode_bencoded_value(const std::string& encoded_value, size_t &index){
    if(std::isdigit(encoded_value[index])){
        return decode_bencoded_string(encoded_value,index);
    }
    else if(encoded_value[index] == 'i'){
        return decode_bencoded_integer(encoded_value,index);
    }
    else if(encoded_value[index] == 'l'){
        return decode_bencoded_list(encoded_value,index);
    }
    else{
        throw std::runtime_error("Incorrect encoded value: " + encoded_value);
    }
}

json decode_bencoded_value(const std::string& encoded_value) {
    size_t index = 0;
    json result = decode_bencoded_value(encoded_value,index);
    if(index!=encoded_value.size()){
        throw std::runtime_error("Input string has extra characters");
    }
    return result;
}

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
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
        // You can use print statements as follows for debugging, they'll be visible when running tests.
        std::cerr << "Logs from your program will appear here!" << std::endl;

        std::string encoded_value = argv[2];
        json decoded_value = decode_bencoded_value(encoded_value);
        std::cout << decoded_value.dump() << std::endl;
    } else {
        std::cerr << "unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
