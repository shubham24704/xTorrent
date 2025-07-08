#include "torrent_parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::vector<std::string> extractPieces(const std::string& raw) {
    std::vector<std::string> hashes;
    for (size_t i = 0; i + 20 <= raw.size(); i += 20) {
        std::string hash = raw.substr(i, 20);
        std::ostringstream hex;
        for (unsigned char c : hash)
            hex << std::hex << std::setw(2) << std::setfill('0') << (int)c;
        hashes.push_back(hex.str());
    }
    return hashes;
}

TorrentFile parseTorrentFile(const std::string& filepath) {
    std::string content = readFile(filepath);
    size_t index = 0;
    json data = decode_bencoded_value(content, index);

    TorrentFile tf;
    tf.announce = data["announce"];
    auto info = data["info"];

    tf.name = info["name"];
    tf.piece_length = info["piece length"];

    // 👇 Add debug print before accessing 'length'
    std::cout << "Length field raw: " << info["length"] << std::endl;

    // 🔒 Only set length if it's a single-file torrent
    if (info.contains("length")) {
        try {
            tf.length = info["length"].get<int64_t>();
            std::cout << "Length field raw: " << tf.length << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Invalid length value: " << e.what() << std::endl;
            tf.length = 0;
        }
    } else {
        std::cout << "Length key not found.\n";
        tf.length = 0;
    }

    tf.pieces = extractPieces(info["pieces"]);

    return tf;
}
