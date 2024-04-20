#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>


#include "huffman.hpp"
#include "bitarr.hpp"
#include "defs.hpp"

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
    

    if (!strcmp(argv[1], "--decode")) {
        
    } else if (!strcmp(argv[1], "--encode")) {
        const std::vector<BYTE> buffer(std::istreambuf_iterator<char>(fin), {});
        const auto ans = Huffman::encode(buffer);
        std::ofstream fout(std::string(argv[2]) + ".hc", std::ios::binary);
        if (!fout) {
            cerr << "error" << endl;
            return 1;
        }
        fout << ans.first << ans.second;
    }//*/
    return 0;
}