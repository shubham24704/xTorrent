#include "../src/torrent_parser.hpp"
#include <iostream>

int main() {
    std::cout << "===== Started parsing =====" << std::endl;

    std::string path = "../test_data/sample1.torrent";

    TorrentFile tf = parseTorrentFile(path);

    std::cout << "Announce URL: " << tf.announce << "\n";
    std::cout << "File Name: " << tf.name << "\n";
    std::cout << "Piece Length: " << tf.piece_length << "\n";
    std::cout << "Length: " << tf.length << "\n";
    std::cout << "Number of Pieces: " << tf.pieces.size() << "\n";

    for (int i = 0; i < tf.pieces.size(); ++i) {
        std::cout << "Piece " << i << ": " << tf.pieces[i] << "\n";
    }

    std::cout << "===== Done =====" << std::endl;

    return 0;
}
