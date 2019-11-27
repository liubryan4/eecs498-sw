#ifndef EMBEDDED_BUFFER_CPP
#define EMBEDDED_BUFFER_CPP

#include <iostream>
#include <vector>
#include "util.cpp"
#include <fstream>
using namespace std;

vector<vector<int32_t> > embedded_buffer;

void inline read_embeddings(uint32_t addr, vector<int32_t> & data_out) {
    data_out = embedded_buffer[addr];
}

void inline write_embeddings(string fname) {
    ifstream file;
    file.open(fname);
    file >> max_unique_words >> embedding_size;
    cout << max_unique_words << ' ' << embedding_size << endl;
    embedded_buffer.resize(max_unique_words);
    int32_t val;
    for (uint32_t i = 0 ; i < max_unique_words ; ++i) {
        embedded_buffer[i].resize(embedding_size);
        for (uint32_t j = 0 ; j < embedding_size ; ++j) {
            file >> val;
            embedded_buffer[i][j] = val;
        }
    }
}

#endif
