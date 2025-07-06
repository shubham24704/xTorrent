#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json decode_bencoded_value(const std::string& encoded_value, size_t& index);
json decode_bencoded_value(const std::string& encoded_value);
