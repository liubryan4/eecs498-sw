#ifndef EMBEDDED_BUFFER_CPP
#define EMBEDDED_BUFFER_CPP

#include "util.cpp"
#include <fstream>
using namespace std;

int32_t embedded_buffer[max_unique_words][embedding_size];

void read_embeddings(uint32_t addr, uint32_t * data_out) {
    memcpy(data_out, &embedded_buffer[addr], emb_line_size);
}

void write_embeddings(string fname) {
    ifstream file;
    file.open(fname);
    int32_t val;
    for (uint32_t i = 0 ; i < max_unique_words ; ++i) {
        for (uint32_t j = 0 ; j < embedding_size ; ++j) {
            file >> val;
            embedded_buffer[i][j] = val;
        }
    }
}

#endif
