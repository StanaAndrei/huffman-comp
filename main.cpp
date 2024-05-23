#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <utility>

#include "huffman.hpp"
#include "bitarr.hpp"
#include "defs.hpp"
#include "optbintree.hpp"
#include "fileutils.hpp"

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Wrong  usage!" << endl;
        return 1;
    }

    std::fstream fin;
    FileUtils::openFile(fin, argv[2], FileUtils::READ_BIN_OPEN);
    
    std::fstream fout;
    if (!strcmp(argv[1], "--decode")) {
        std::string fname(argv[2]);
        std::string ending(FILE_SUF);
        if (fname.length() >= ending.length() && (0 == fname.compare (fname.length() - ending.length(), ending.length(), ending)));
        else {
            cerr << "Wrong file type!" << endl;
            return 1;
        }
        std::pair<OptBinTree, BitArr> pair;
        fin >> pair.first >> pair.second;
        auto ans = Huffman::decode(pair);
        fname.erase(fname.length() - strlen(FILE_SUF));
        FileUtils::openFile(fout, fname.c_str(), FileUtils::WRITE_BIN_OPEN);
        fout.write(reinterpret_cast<char*>(&ans[0]), ans.size());
    } else if (!strcmp(argv[1], "--encode")) {
        const std::vector<BYTE> buffer(std::istreambuf_iterator<char>(fin), {});
        if (buffer.size() < MIN_SZ) {
            cerr << "It makes no sense to encode this(file too small)!" << endl;
            return 0;
        }
        const auto ans = Huffman::encode(buffer);
        FileUtils::openFile(fout, (std::string(argv[2]) + FILE_SUF).c_str(), FileUtils::WRITE_BIN_OPEN);
        fout << ans.first << ans.second;
    }
    fin.close();
    fout.close();
    return 0;
}