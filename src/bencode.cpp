#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include "bencode.hpp"

using json = nlohmann::json;

json decode_bencoded_value(const std::string& encoded_value, size_t &index);

json decode_bencoded_integer(const std::string& encoded_value, size_t &index){
    index++; // skip 'i'

    bool is_negative = false;
    if(encoded_value[index]=='-'){
        is_negative = true;
        index++; // skip '-'
    }

    size_t start = index;

    while(index<encoded_value.size() && encoded_value[index]!='e') index++;
    size_t length = index - start;

    index++; // skip 'e'

    long long result = stoll(encoded_value.substr(start,length));
    if(is_negative) result *= -1;

    return json(result);
}

json decode_bencoded_string(const std::string& encoded_value, size_t &index){
    std::string number = "";
    while(encoded_value[index] != ':'){
        number += encoded_value[index];
        index++;
    }
    index++; // skip ':'
    size_t length = std::stoll(number);
    std:: string result = "";
    while(length--){
        result += encoded_value[index];
        index++;
    }
    return json(result);
}

json decode_bencoded_list(const std::string& encoded_value, size_t &index){
    index++; // skip 'l'
    json result = json::array();
    while(encoded_value[index] != 'e'){
        result.push_back(decode_bencoded_value(encoded_value,index));
    }
    index++; // skip 'e'
    return json(result);
}

json decode_bencoded_dictionary(const std::string& encoded_value, size_t& index) {
    index++; // skip 'd'
    std::map<std::string, json> dictMap;

    while (index < encoded_value.size() && encoded_value[index] != 'e') {
        std::string key = decode_bencoded_string(encoded_value, index);
        json value = decode_bencoded_value(encoded_value, index);
        dictMap[key] = value;
    }

    if (index >= encoded_value.size() || encoded_value[index] != 'e') {
        throw std::runtime_error("Expected 'e' at end of dictionary");
    }
    index++; // skip 'e'

    return dictMap;
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
    else if(encoded_value[index] == 'd'){
        return decode_bencoded_dictionary(encoded_value,index);
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