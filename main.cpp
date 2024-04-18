#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

#include "huffman.hpp"
#include "bitarr.hpp"

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Wrong  usage!" << endl;
        return 1;
    }

    std::ifstream fin;
    fin.exceptions(std::fstream::failbit | std::fstream::badbit);
    try  {
        fin.open(argv[2], std::ios::binary);
    } catch(std::fstream::failure &f) {
        cerr << f.what() << endl;
        return 1;
    }
    fin.seekg(0, std::ios::end);
    size_t fileSize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    std::string buffer(fileSize, '\0');
    fin.read(&buffer[0], fileSize);
    buffer.pop_back();//del \n
    //cerr << buffer << endl;

    if (!strcmp(argv[1], "--decode")) {
        
    } else if (!strcmp(argv[1], "--encode")) {
        auto ans = Huffman::encode(buffer);
        cerr << ans.first.toString() << endl;
    }//*/
    return 0;
}