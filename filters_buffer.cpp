#ifndef FILTERS_BUFFER_CPP
#define FILTERS_BUFFER_CPP

#include "util.cpp"
using namespace std;

int32_t filter_storage[max_filters][filter_height][filter_width];

void read_filter(uint32_t id, uint32_t * data_out) {
    for (uint32_t i = 0 ; i < filter_height ; ++i) {
        memcpy(data_out + i*filter_line_size,
                &filter_storage[id] + i*filer_line_size,
                stride);
    }
}

void write_filters(string fname) {
    ifstream file;
    file.open(fname);
    int32_t val;
    for (uint32_t i = 0 ; i < max_filters ; ++i) {
        for (uint32_t j = 0 ; j < filter_height ; ++j) {
            for (uint32_t k = 0 ; k < filter_width ; ++k) {
                file >> val;
                filter_storage[i][j][k] = val;
            }
        }
    }
}

#endif
