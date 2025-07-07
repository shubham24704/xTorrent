#pragma once
#include <string>
#include <vector>
#include <map>
#include "bencode.hpp"
#include "nlohmann/json.hpp"

struct TorrentFile {
    std::string announce;
    std::string name;
    int piece_length;
    int length; // for single file torrents
    std::vector<std::string> pieces; // hex-encoded SHA1 hashes
};

TorrentFile parseTorrentFile(const std::string& filepath);
