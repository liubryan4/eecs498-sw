#ifndef CACHE_CPP
#define CACHE_CPP

#include "util.cpp"
using namespace std;

struct cache_storage {
    bool valid;
    int32_t block[4];
}
cache_storage cs[max_unique_words];

void reset_cache() {
    for (uint32_t i = 0 ; i < max_unique_words ; ++i) {
        cs[i].valid = false;
    }
}

//what if select_read_out does not find anything to read in?
void read_cache(uint32_t * addr, bool * read_in_valid, int32_t * data_out) {
    bool read_valid = false;
    int8_t read_loc = 0;
    uint32_t select_read_addr;
    // what is the point of constant overwrite? Why not just select
    // and return the start of the block?
    for (int i = 3 ; i >= 0 ; --i) {
        if (read_in_valid[i] && cs[addr[i]].valid) {
            read_valid = true;
            read_loc = i;
            select_read_addr = read_in_addr[i];
        }
    }

    bool invalid_read = false;
    for (int i = 0 ; i < 4 ; ++i) {
        if (read_in_valid[i]) {
            invalid_read[i] = !cs[read_in_addr[i]].valid;
        }
    }

    data_out = &cs[select_read_addr].block;
}

void write_cache(uint32_t addr, int32_t * data_in) {
    cs[addr].valid = true;
    for (int32_t i = 0 ; i < 4 ; ++i) {
        cs[addr].block[i] = data_in[i];
    }
}

#endif
